[%%raw {|
  var Online = require('./Online.bs');
|}];

type action =
  | NewGame
  | Shuffle
  | Flip (Shuffle.compassPoint)
  | Discard
  | Sync
  | LoginSync
  | Test
  | AssignPlayer(Shuffle.pointOfCompassAndPlayer)
  | BidAdd(option(int))
  | BidUpdate(option(string))
  | BidAddSpecial(option(string))
;

// this is the game state that we will share amongst all users who are registered at the server
// it is a single record which will be passed to and broadcast from the server
type state = {
  activePointOfCompass: option(string),
  bids: Chicago.bids,
  chicagoScoreSheet: list(Chicago.chicagoScoreSheetRecord),
  dealer: option(string),
  dealIndex: int,
  declarer: option(string),
  handVisible: Shuffle.handVisible,
  isBiddingCycle: bool,
  isBiddingHideDenominationButtons: bool,
  isRebootVisible: bool,
  lastAction: string,
  pack: Shuffle.pack,
  pointOfCompassAndPlayers: array(Shuffle.pointOfCompassAndPlayer),
  randomInt: int,
};

// this is used by the reducer at app startup, before being overwritten
// by later actions
// Note the only thing we set here is the starting active poc and dealer
let initialState: state = {
    activePointOfCompass: None, // Some(Shuffle.initialPoc), - do this at server!
    bids: [],
    chicagoScoreSheet: Chicago.initialChicagoScoreSheet,
    dealer: None, // Some(Shuffle.initialPoc), - do this at server!
    dealIndex: -1,
    declarer: None,
    handVisible: Shuffle.initialHandVisible,
    isBiddingCycle: false,
    isBiddingHideDenominationButtons: true,
    isRebootVisible: false,
    lastAction: "None (initialState from Client)",
    pack: [||], // Shuffle.initialPack,
    pointOfCompassAndPlayers: [||],
    randomInt: 1,
};

let reducer = (state: state, action) => {
    switch action {
      | NewGame => {
        // aka Reboot
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // force everything same as when server starts up,
        // except leave logged in players and their pointsOfCompass - NO!
        // make this button a full reboot - clear players too
        {
          //...state,
          activePointOfCompass: None,
          bids: [],
          chicagoScoreSheet: [], //Chicago.initialChicagoScoreSheet,
          dealer: None,
          dealIndex: -1,
          declarer: None,
          handVisible: Shuffle.initialHandVisible,
          isBiddingCycle: false,
          isBiddingHideDenominationButtons: true,
          isRebootVisible: true,
          lastAction: "Reboot (clears scores & logins)",
          pack: [||],
          pointOfCompassAndPlayers: [||],
          randomInt: 2, 
        }
      }
      | Shuffle => {
        // aka "New Deal" aka "My Deal"
        //Js.log("Action-Shuffle");
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // dealer becomes activePointOfCompass too, because he starts the bidding
        // do change of dealer at end of deal ie 52 cards out TO D)
        //let poc = Some(Shuffle.getNextPointOfCompass(state.dealer));
        {
          ...state, 
          //activePointOfCompass: poc,
          bids: [],
          //dealer: poc,
          dealIndex: state.dealIndex + 1,
          declarer: None,
          isBiddingCycle: true,
          isBiddingHideDenominationButtons: true,
          lastAction: "Shuffle",
          pack: Shuffle.getShuffledPack(), 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
        }
      }
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
          bids: [],
          chicagoScoreSheet: [],
          dealer: None,
          dealIndex: -1,
          declarer: None,
          handVisible: {north: false, east: false, south: false, west: false},
          isBiddingCycle: false,
          isBiddingHideDenominationButtons: true,
          isRebootVisible: false,
          lastAction: "Logout or Server Down",
          pack: [||],
          pointOfCompassAndPlayers: [||],
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
        }
      }
      | LoginSync => {
        // Client state is now ENTIRELY REPLACED with server gameState
        // this is same as Sync above, and we do also want to suppress doMessage
        let () = [%raw "window.isLastActionSync = true"];
        // we must make sure that state is updated by every gameState field
        let cSS: list(Chicago.chicagoScoreSheetRecord) = [%bs.raw "window.gameState.chicagoScoreSheet"];
        let dealer: option(string) = [%bs.raw "window.gameState.dealer"];
        let declarer: option(string) = [%bs.raw "window.gameState.declarer"];
        let hV: Shuffle.handVisible = [%bs.raw "window.gameState.handVisible"];
        let  pOCAP: array(Shuffle.pointOfCompassAndPlayer) = [%bs.raw "window.gameState.pointOfCompassAndPlayers"]; 
        // lastAction is an exception, we always want to hard code this below
        let pack: Shuffle.pack = [%bs.raw "window.gameState.pack"];
        // randomInt ia another exception
        let dealIndex: int = [%bs.raw "window.gameState.dealIndex"];
        let isBiddingCycle: bool = [%bs.raw "window.gameState.isBiddingCycle"];
        let poc: option(string) = [%bs.raw "window.gameState.activePointOfCompass"];
        let bids: Chicago.bids = [%bs.raw "window.gameState.bids"];
        let isBiddingHideDenominationButtons: bool = [%bs.raw "window.gameState.isBiddingHideDenominationButtons"];
        let isRebootVisible: bool = [%bs.raw "window.gameState.isRebootVisible"];
        // no need for ...state here as we are replacing all fields with the server gameState fields
        {
          activePointOfCompass: poc,
          bids: bids,
          chicagoScoreSheet: cSS,
          dealer: dealer,
          dealIndex: dealIndex,
          declarer: declarer,
          handVisible: hV,
          isBiddingCycle: isBiddingCycle,
          isBiddingHideDenominationButtons: isBiddingHideDenominationButtons,
          isRebootVisible: isRebootVisible,
          lastAction: "LoginSync",
          pack: pack,
          pointOfCompassAndPlayers: pOCAP,
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
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
      | BidAdd(contractLevel) => {
        Js.log("Action - BidAdd")
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        //Js.log(state.bids);
        {
          ...state, 
          bids: [
            {
              contractLevel: contractLevel,
              contractSuit: Some(""),
              contractPointOfCompass: state.activePointOfCompass,
              isDoubled: false,
              isRedoubled: false,
              isPass: false
            },
            ...state.bids
          ],
          isBiddingHideDenominationButtons: false,
          lastAction: "BidAdd", 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
        }
      }
      | BidUpdate(contractSuit) => {
        Js.log("Action - BidUpdate")
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // we can do an immutable update
        let bids = state.bids;
        let head = List.hd(bids);
        //Js.log(head);
        let newHead = {
          ...head,
          contractSuit: contractSuit
        };
        //Js.log(newHead);
        let tail = List.tl(bids);
        let bidsUpdated = [newHead, ...tail];
        //Js.log(bidsUpdated);
        // move on to next poc!
        let poc = Some(Shuffle.getNextPointOfCompass(state.activePointOfCompass));        
        {
          ...state, 
          activePointOfCompass: poc,
          bids: bidsUpdated,
          isBiddingHideDenominationButtons: true,
          lastAction: "BidUpdate", 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
        }
      }
      | BidAddSpecial(special) => {
        Js.log("Action - BidAddSpecial")
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // move on to next poc!
        let poc = Some(Shuffle.getNextPointOfCompass(state.activePointOfCompass));   
        //Js.log(poc);   
        switch (special) {
          | Some("Pass") => {
            // check for end of bidding cycle
            let bidsLength = List.length(state.bids);
            Js.log(bidsLength);
            if (bidsLength >= 3) {
              let hd1 = List.hd(state.bids);
              let tl = List.tl(state.bids);
              let hd2 = List.hd(tl);
              if (hd1.isPass === true && hd2.isPass === true) {
                // helper function to get vulnerability
                let vulnerable = switch(state.dealIndex mod 4)  {
                  | 0 => "None"
                  | 1 => Shuffle.pocAsString(state.dealer)
                  | 2 => Shuffle.pocAsString(state.dealer)
                  | 3 => "All"
                  | _ => "Error"
                };
                // we need to add a row to the Chicago score sheet, so assemble here
                let bidRecordOfInterest1 = List.hd(List.tl(tl));
                //Js.log(bidRecordOfInterest1);
                let contractLevel = bidRecordOfInterest1.contractLevel;
                let contractSuit = bidRecordOfInterest1.contractSuit;
                let totalTricks = 0;
                let scoreNorthSouth = None;
                let scoreWestEast = None;
                let contractDeclarer = Some("Test"); // to do
                let chicagoScoreSheetRecord: Chicago.chicagoScoreSheetRecord = {
                  vulnerable: vulnerable,
                  contractLevel: contractLevel,
                  contractSuit: contractSuit,
                  contractDeclarer: contractDeclarer,
                  totalTricks: totalTricks,
                  scoreNorthSouth: scoreNorthSouth,
                  scoreWestEast: scoreWestEast
                };
                // return end of bidding
                {
                  ...state,
                  chicagoScoreSheet: [chicagoScoreSheetRecord ,...state.chicagoScoreSheet],
                  isBiddingCycle: false,
                  lastAction: "BidAddSpecial-3Passes",
                  randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
                }
              } else {
                {
                  ...state, 
                  activePointOfCompass: poc,
                  bids: [
                    {
                      contractLevel: None,
                      contractSuit: None,
                      contractPointOfCompass: state.activePointOfCompass,
                      isDoubled: false,
                      isRedoubled: false,
                      isPass: true
                    },
                    ...state.bids
                  ],
                  lastAction: "BidAddSpecial", 
                  randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
                }
              }
            } else {
              {
                ...state, 
                activePointOfCompass: poc,
                bids: [
                  {
                    contractLevel: None,
                    contractSuit: None,
                    contractPointOfCompass: state.activePointOfCompass,
                    isDoubled: false,
                    isRedoubled: false,
                    isPass: true
                  },
                  ...state.bids
                ],
                lastAction: "BidAddSpecial", 
                randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
              }
            }
          }
          | Some("X") => {
            ...state, 
            activePointOfCompass: poc,
            bids: [
              {
                contractLevel: None,
                contractSuit: None,
                contractPointOfCompass: state.activePointOfCompass,
                isDoubled: true,
                isRedoubled: false,
                isPass: false
              },
              ...state.bids
            ],
            lastAction: "BidAddSpecial", 
            randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
          }
          | Some("XX") => {
            ...state, 
            activePointOfCompass: poc,
            bids: [
              {
                contractLevel: None,
                contractSuit: None,
                contractPointOfCompass: state.activePointOfCompass,
                isDoubled: false,
                isRedoubled: true,
                isPass: false
              },
              ...state.bids
            ],
            lastAction: "BidAddSpecial", 
            randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
          }
          | _ => {
            // should never occur, and no change in state
            state
          }
        }
      }
    }
};
