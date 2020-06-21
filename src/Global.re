[%%raw {|
  var Online = require('./Online.bs');
|}];

type action =
  | NewGame
  | Shuffle
  //| DealerChange (string)
  | Flip (Shuffle.compassPoint)
  // | HideAllCards
  // | ShowAllCards
  // | Deal 
  | Discard
  | Sync
  | LoginSync
  | Test
  | AssignPlayer(Shuffle.pointOfCompassAndPlayer)
  | BidAdd(option(int))
  | BidUpdate(Chicago.bid)
;

// this is the game state that we will share amongst all users who are registered at the server
// it is a single record which will be passed to and broadcast from the server
type state = {
  activePointOfCompass: option(string),
  bids: Chicago.bids,
  chicagoScoreSheet: array(Chicago.chicagoScoreSheetRecord),
  dealer: option(string),
  dealIndex: int,
  handVisible: Shuffle.handVisible,
  isBiddingCycle: bool,
  lastAction: string,
  pack: Shuffle.pack,
  pointOfCompassAndPlayers: array(Shuffle.pointOfCompassAndPlayer),
  randomInt: int,
};

let initialState: state = {
    activePointOfCompass: None,
    bids: [||],
    chicagoScoreSheet: Chicago.initialChicagoScoreSheet,
    dealer: None,
    dealIndex: -1,
    handVisible: Shuffle.initialHandVisible,
    isBiddingCycle: false,
    lastAction: "None(fromClient)",
    pack: Shuffle.initialPack,
    pointOfCompassAndPlayers: [||],
    randomInt: -111,
};

let reducer = (state: state, action) => {
    switch action {
      | NewGame => {
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // force everything same as when server starts up,
        // except leave logged in players and their pointsOfCompass
        {
          ...state,
          activePointOfCompass: None,
          chicagoScoreSheet: [||],
          dealer: None,
          dealIndex: -1,
          handVisible: Shuffle.initialHandVisible,
          isBiddingCycle: false,
          lastAction: "NewGame",
          pack: [||],
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
        }
      }
      | Shuffle => {
        // aka "New Deal"
        //Js.log("Action-Shuffle");
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // dealer becomes activePointOfCompass too, because he starts the bidding
        let poc = Some(Shuffle.getNextPointOfCompass(state.dealer));
        {
          ...state, 
          activePointOfCompass: poc,
          dealer: poc,
          dealIndex: state.dealIndex + 1,
          isBiddingCycle: true,
          lastAction: "Shuffle",
          pack: Shuffle.getShuffledPack(), 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
        }
      }
      // this is part of Start Game
      // because to start game you have to assign the Dealer and then do a Shuffle
      // | DealerChange (shortLoc) => {
      //   switch (shortLoc) {
      //     | "N" => {...state, dealer: Some(North)}
      //     | "E" => {...state, dealer: Some(East)}
      //     | "S" => {...state, dealer: Some(South)}
      //     | "W" => {...state, dealer: Some(West)}
      //     | _ => {...state, dealer: None}
      //   }
      // }
      | Flip (compassPoint) => {
        //Js.log("Action-Flip");
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        switch (compassPoint) {
          | North => {...state, handVisible: {...state.handVisible, north: !state.handVisible.north}, lastAction: "Flip", randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()}
          | East => {...state, handVisible: {...state.handVisible, east: !state.handVisible.east}, lastAction: "Flip", randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k() }
          | South => {...state, handVisible: {...state.handVisible, south: !state.handVisible.south}, lastAction: "Flip", randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k() }
          | West => {...state, handVisible: {...state.handVisible, west: !state.handVisible.west}, lastAction: "Flip", randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k() }
        }
      }
      | Discard => {
        //Js.log("Action-Discard");
        // make sure doMessage IS called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // attempt to set state to gameState failed, must update state correctly
        let discardFileName: string = [%raw "window.discardFileName"];
        let myPack = Array.map(
          (card: Shuffle.card) => {
            card.fileName === discardFileName
            ?
            {...card, lifecycle: Discard}
            :
            {card}
          },
          state.pack
        );
        {
          ...state, 
          pack: myPack, 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
          lastAction: "Discard"  
        }
      }
      | Sync => {
        // aka Logout or perhaps Server Down
        //Js.log("Action - Sync");
        // replace existing state with gameState
        // Below line does NOT work! Must use the spread operator with state
        //let myNewState: state = [%bs.raw {| window.gameState |}];   //state;
        // make sure doMessage is NOT called in sidebar component
        let () = [%raw "window.isLastActionSync = true"];
        // no need for ...state here as we are replacing all fields with the server gameState fields
        {
          activePointOfCompass: None,
          bids: [||],
          chicagoScoreSheet: [||],
          dealer: None,
          handVisible: {north: false, east: false, south: false, west: false},
          lastAction: "LogoutOrServerDownSync",
          pack: [||],
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
          pointOfCompassAndPlayers: [||],
          dealIndex: -1,
          isBiddingCycle: false
        }
      }
      | LoginSync => {
        // Client state is now ENTIRELY REPLACED with server gameState
        // this is same as Sync above, and we do also want to suppress doMessage
        let () = [%raw "window.isLastActionSync = true"];
        // we must make sure that state is updated by every gameState field
        let cSS: array(Chicago.chicagoScoreSheetRecord) = [%bs.raw "window.gameState.chicagoScoreSheet"];
        let dealer: option(string) = [%bs.raw "window.gameState.dealer"];
        let hV: Shuffle.handVisible = [%bs.raw "window.gameState.handVisible"];
        let  pOCAP: array(Shuffle.pointOfCompassAndPlayer) = [%bs.raw "window.gameState.pointOfCompassAndPlayers"]; 
        // lastAction is an exception, we always want to hard code this below
        let pack: Shuffle.pack = [%bs.raw "window.gameState.pack"];
        // randomInt ia another exception
        let dealIndex: int = [%bs.raw "window.gameState.dealIndex"];
        let isBiddingCycle: bool = [%bs.raw "window.gameState.isBiddingCycle"];
        let poc: option(string) = [%bs.raw "window.gameState.activePointOfCompass"];
        let bids: Chicago.bids = [%bs.raw "window.gameState.bids"];
        // no need for ...state here as we are replacing all fields with the server gameState fields
        {
          activePointOfCompass: poc,
          bids: bids,
          chicagoScoreSheet: cSS,
          dealer: dealer,
          handVisible: hV,
          lastAction: "LoginSync",
          pack: pack,
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
          pointOfCompassAndPlayers: pOCAP,
          dealIndex: dealIndex,
          isBiddingCycle: isBiddingCycle
        }
      }
      | Test => {
        //Js.log("Action-Test");
        // make sure doMessage is NOT called in sidebar component
        let () = [%raw "window.isLastActionSync = true"];
        Js.log("benign action: 'Test'");
        {
          ...state, lastAction: "Test", randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
        }
      }
      | AssignPlayer(pOfCAndP) => {
        //Js.log("Action-AssignPlayer");
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        Js.log("action AssignPlayer " ++ pOfCAndP.player ++ " to " ++ pOfCAndP.pointOfCompass);
        //let myNewArray = state.pointOfCompassAndPlayers;
        //{...state, pointOfCompassAndPlayers: myNewArray}
        // unassign any existing requested pointOfCompass
        // unless it is an Observer...
        let myArray1 = Array.map(
          (pointOfCompassAndPlayer: Shuffle.pointOfCompassAndPlayer) => {
            pointOfCompassAndPlayer.pointOfCompass == pOfCAndP.pointOfCompass && pointOfCompassAndPlayer.pointOfCompass != "Observer"
            ?
            {...pointOfCompassAndPlayer, pointOfCompass: ""}
            :
            {pointOfCompassAndPlayer}
          },
          state.pointOfCompassAndPlayers
        );
        // assign the requested pointOfCompass to correct player
        let myArray2 = Array.map(
          (pointOfCompassAndPlayer: Shuffle.pointOfCompassAndPlayer) => {
            pointOfCompassAndPlayer.player == pOfCAndP.player
            ?
            {...pointOfCompassAndPlayer, pointOfCompass: pOfCAndP.pointOfCompass}
            :
            {pointOfCompassAndPlayer}
          },
          myArray1
        );
        {
          ...state, 
          pointOfCompassAndPlayers: myArray2, 
          lastAction: "AssignPlayer",
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
        }
      }
      | BidAdd(bid) => {
        Js.log("Action - BidAdd")
        // make sure doMessage is NOT called in sidebar component
        let () = [%raw "window.isLastActionSync = true"];
        {
          ...state, lastAction: "BidAdd", randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
        }
      }
      | BidUpdate(bid) => {
        Js.log("Action - BidUpdate")
        // make sure doMessage is NOT called in sidebar component
        let () = [%raw "window.isLastActionSync = true"];
        {
          ...state, lastAction: "BidUpdate", randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
        }
      }
    }
};
