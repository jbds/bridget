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
;

// this is the game state that we will share amongst all users who are registered at the server
// it is a single record which will be passed to and broadcast from the server
type state = {
  chicagoScoreSheet: array(Chicago.chicagoScoreSheetRecord),
  dealer: option(Shuffle.compassPoint),
  handVisible: Shuffle.handVisible,
  lastAction: string,
  pack: Shuffle.pack,
  pointOfCompassAndPlayers: array(Shuffle.pointOfCompassAndPlayer),
  randomInt: int,
};

let initialState: state = {
    chicagoScoreSheet: Chicago.initialChicagoScoreSheet,
    dealer: None,
    handVisible: Shuffle.initialHandVisible,
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
          chicagoScoreSheet: [||],
          dealer: None,
          handVisible: Shuffle.initialHandVisible,
          lastAction: "NewGame",
          pack: [||],
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
        }
      }
      | Shuffle => {
        //Js.log("Action-Shuffle");
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        {
          ...state, 
          pack: Shuffle.getShuffledPack(), 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
          dealer: Some(Shuffle.getNextDealerLocation(state.dealer)),
          lastAction: "Shuffle"
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
        //Js.log("Action - Sync");
        // replace existing state with gameState
        // Below line does NOT work! Must use the spread operator with state
        //let myNewState: state = [%bs.raw {| window.gameState |}];   //state;
        // make sure doMessage is NOT called in sidebar component
        let () = [%raw "window.isLastActionSync = true"];
        {
          ...state, 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
          lastAction: "LogoutOrServerDownSync"
        }
      }
      | LoginSync => {
        // this is same as Sync above, and we do also want to suppress doMessage
        let () = [%raw "window.isLastActionSync = true"];
        // we must make sure that state is updated by every gameState field
        let cSS: array(Chicago.chicagoScoreSheetRecord) = [%bs.raw "window.gameState.chicagoScoreSheet"];
        let dealer: option(Shuffle.compassPoint) = [%bs.raw "window.gameState.dealer"];
        let hV: Shuffle.handVisible = [%bs.raw "window.gameState.handVisible"];
        let  pOCAP: array(Shuffle.pointOfCompassAndPlayer) = [%bs.raw "window.gameState.pointOfCompassAndPlayers"]; 
        // lastAction is an exception, we always want to hard code this below
        let pack: Shuffle.pack = [%bs.raw "window.gameState.pack"];
        // randomInt ia another exception
        // no need for ...state here as we are replacing all fields!
        {
          chicagoScoreSheet: cSS,
          dealer: dealer,
          handVisible: hV,
          lastAction: "LoginSync",
          pack: pack,
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
          pointOfCompassAndPlayers: pOCAP
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
        //Js.log("action AssignPlayer " ++ pOfCAndP.player ++ " to " ++ pOfCAndP.pointOfCompass);
        //let myNewArray = state.pointOfCompassAndPlayers;
        //{...state, pointOfCompassAndPlayers: myNewArray}
        let myArray1 = Array.map(
          (pointOfCompassAndPlayer: Shuffle.pointOfCompassAndPlayer) => {
            pointOfCompassAndPlayer.pointOfCompass == pOfCAndP.pointOfCompass
            ?
            {...pointOfCompassAndPlayer, pointOfCompass: ""}
            :
            {pointOfCompassAndPlayer}
          },
          state.pointOfCompassAndPlayers
        );
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
    }
};
