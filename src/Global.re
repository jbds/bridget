[%%raw {|
  var Online = require('./Online.bs');
|}];

type action =
  //| NewGame
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
  | EndTrick
;

// this is the game state that we will share amongst all users who are registered at the server
// it is a single record which will be passed to and broadcast from the server
// type state = {
//   activePointOfCompass: option(string),
//   bids: Chicago.bids,
//   chicagoScoreSheet: list(Chicago.chicagoScoreSheetRecord),
//   dealer: option(string),
//   dealIndex: int,
//   declarer: option(string),
//   discardIndex: int,
//   discardSuit: option(Shuffle.suit),
//   handVisible: Shuffle.handVisible,
//   isBiddingCycle: bool,
//   isBiddingHideDenominationButtons: bool,
//   isDummyVisible: bool,
//   isRebootVisible: bool,
//   isReviewDealVisible: bool,
//   lastAction: string,
//   pack: Shuffle.pack,
//   pointOfCompassAndPlayers: array(Shuffle.pointOfCompassAndPlayer),
//   randomInt: int,
// };

// this is used by the reducer at app startup, before being overwritten
// by later actions
// Note the only thing we set here is the starting active poc and dealer
let initialState: TopLevel.state = {
    activePointOfCompass: None, // Some(Shuffle.initialPoc), - do this at server!
    bids: [],
    chicagoScoreSheet: Chicago.initialChicagoScoreSheet,
    dealer: None, // Some(Shuffle.initialPoc), - do this at server!
    dealIndex: -1,
    declarer: None,
    discardIndex: -1,
    discardSuit: None,
    handVisible: Shuffle.initialHandVisible,
    isBiddingCycle: false,
    isBiddingHideDenominationButtons: true,
    isDummyVisible: false,
    isRebootVisible: false,
    isReviewDealVisible: false,
    lastAction: "None (initialState from Client)",
    pack: [||], // Shuffle.initialPack,
    pointOfCompassAndPlayers: [||],
    randomInt: 1,
};

let reducer = (state: TopLevel.state, action) => {
  switch action {
    // superseded by Reboot as ws message sent direct to server
    // | NewGame => {
    //   // aka Reboot
    //   // make sure doMessage is called in sidebar component
    //   let () = [%raw "window.isLastActionSync = false"];
    //   // force everything same as when server starts up,
    //   // except leave logged in players and their pointsOfCompass - NO!
    //   // make this button a full reboot - clear players too
    //   {
    //     //...state,
    //     activePointOfCompass: None,
    //     bids: [],
    //     chicagoScoreSheet: [], //Chicago.initialChicagoScoreSheet,
    //     dealer: None,
    //     dealIndex: -1,
    //     declarer: None,
    //     discardIndex: -1,
    //     discardSuit: None,
    //     handVisible: Shuffle.initialHandVisible,
    //     isBiddingCycle: false,
    //     isBiddingHideDenominationButtons: true,
    //     isDummyVisible: false,
    //     isRebootVisible: true,
    //     lastAction: "Reboot (clears scores & logins)",
    //     pack: [||],
    //     pointOfCompassAndPlayers: [||],
    //     randomInt: 2, 
    //   }
    // }
    | Shuffle => {
        MyDeal.execute(state);
      // // aka "New Deal" aka "My Deal"
      // //Js.log("Action-Shuffle");
      // // make sure doMessage is called in sidebar component
      // let () = [%raw "window.isLastActionSync = false"];
      // // prepare another message alerting server to store the pack as dealt
      // //let () = [%raw "setTimeout(function(){alert('StoreDeal');}, 750)"];
      // let () = [%raw "setTimeout(function(){Online.doMessage('StoreDeal');}, 750)"];
      // // dealer becomes activePointOfCompass too, because he starts the bidding
      // // do change of dealer at end of deal ie 52 cards out 
      // // also set BiddingCycle to true here
      // // not sure dealIndex is needed?
      // // force activePointOfCompass to be dealer
      // // hide Dummy hand
      // // set handVisible all to false in case previous deal has been Reviewed
      // {
      //   ...state, 
      //   activePointOfCompass: state.dealer,
      //   bids: [],
      //   //dealer: poc,
      //   //dealIndex: state.dealIndex + 1,
      //   declarer: None,
      //   discardIndex: -1,
      //   handVisible: Shuffle.initialHandVisible,
      //   isBiddingCycle: true,
      //   isBiddingHideDenominationButtons: true,
      //   isDummyVisible: false,
      //   isReviewDealVisible: false,
      //   lastAction: "Deal",
      //   pack: Shuffle.getShuffledPack(), 
      //   randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
      // }
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
      // make sure doMessage IS called in sidebar component
      let () = [%raw "window.isLastActionSync = false"];
      // attempt to set state to gameState failed, must update state correctly
      let discardFileName: string = [%raw "window.discardFileName"];
      let cardWrappedInArray = Belt.Array.keep(state.pack, x => x.fileName === discardFileName);
      let cardShuffleIndex = cardWrappedInArray[0].shuffleIndex;
      // we need to capture the discard suit for use on first discard only
      let cardDiscardSuit = cardWrappedInArray[0].suit;
      // the discard suit of the first card for each trick is put into state
      //Js.log("cardDiscardSuit:");
      //Js.log(cardDiscardSuit);
      // discardPoc here and pocFollowingDeclarer after are used to decide
      // whether to make the Dummy hand visible
      let discardPoc = 
        if (cardShuffleIndex < 13) {
          "North"
        } else if (cardShuffleIndex < 26) {
          "East"
        } else if (cardShuffleIndex < 39) {
          "South"
        } else {
          "West"
        };
      //Js.log("discardPoc:");
      //Js.log(discardPoc);
      // we need to know which poc folows declarer
      let pocFollowingDeclarer =
        if (state.declarer == Some("North")) {
          "East"
        } else if (state.declarer == Some("East")) {
          "South"
        } else if (state.declarer == Some("South")) {
          "West"
        } else if (state.declarer == Some("West")) {
          "North"
        } else {
          ""
        };
      //Js.log("pocFollowingDeclarer:")
      //Js.log(pocFollowingDeclarer);
      // move the selected card into the discard pile
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
      // move on to next poc!
      let poc = Some(Shuffle.getNextPointOfCompass(state.activePointOfCompass));        
      {
        ...state, 
        activePointOfCompass: poc,
        discardIndex: state.discardIndex + 1,
        discardSuit: ((state.discardIndex + 1) mod 4) === 0 ? Some(cardDiscardSuit) : state.discardSuit,
        isDummyVisible: 
          discardPoc === pocFollowingDeclarer ? true : state.isDummyVisible,
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
        discardIndex: -1,
        discardSuit: None,
        handVisible: {north: false, east: false, south: false, west: false},
        isBiddingCycle: false,
        isBiddingHideDenominationButtons: true,
        isDummyVisible: false,
        isRebootVisible: false,
        isReviewDealVisible: false,
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
      let isReviewDealVisible: bool = [%bs.raw "window.gameState.isReviewDealVisible"];
      let isDummyVisible: bool = [%bs.raw "window.gameState.isDummyVisible"];
      let discardIndex: int = [%bs.raw "window.gameState.discardIndex"];
      let discardSuit: option(Shuffle.suit) = [%bs.raw "window.gameState.discardSuit"];
      let lastAction: string = [%bs.raw "window.gameState.lastAction"];
      // no need for ...state here as we are replacing all fields with the server gameState fields
      {
        activePointOfCompass: poc,
        bids: bids,
        chicagoScoreSheet: cSS,
        dealer: dealer,
        dealIndex: dealIndex,
        declarer: declarer,
        discardIndex: discardIndex,
        discardSuit: discardSuit,
        handVisible: hV,
        isBiddingCycle: isBiddingCycle,
        isBiddingHideDenominationButtons: isBiddingHideDenominationButtons,
        isDummyVisible: isDummyVisible,
        isRebootVisible: isRebootVisible,
        isReviewDealVisible: isReviewDealVisible,
        lastAction: lastAction,
        pack: pack,
        pointOfCompassAndPlayers: pOCAP,
        randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(), 
      }
    }
    | Test => {
      // make sure doMessage is NOT called in sidebar component
      let () = [%raw "window.isLastActionSync = true"];
      //Js.log("benign action: 'Test'");
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
      //Js.log("Action - BidAdd")
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
      //Js.log("Action - BidUpdate")
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
      //Js.log("Action - BidAddSpecial")
      // make sure doMessage is called in sidebar component
      let () = [%raw "window.isLastActionSync = false"];
      // move on to next poc
      let poc = Some(Shuffle.getNextPointOfCompass(state.activePointOfCompass));   
      //Js.log(poc);   
      switch (special) {
        | Some("Pass") => {
          // check for end of bidding cycle
          let bidsLength = List.length(state.bids);
          Js.log("bidsLength:");
          Js.log(bidsLength);
          Js.log("state.bids keep by isPass===false:");
          Js.log(Belt.List.keep(state.bids, x => x.isPass === false) === []);
          // special case 4 passes at start, beware bidslength will only be 3!
          if (bidsLength === 3 && Belt.List.keep(state.bids, x => x.isPass === false) === []) {
            Js.log("detected 4 passes");
            // do same as new deal aka Shuffle
            // make sure doMessage is called in sidebar component
            let () = [%raw "window.isLastActionSync = false"];
            {
              ...state, 
              activePointOfCompass: state.dealer,
              bids: [],
              //dealer: poc,
              //dealIndex: state.dealIndex + 1,
              declarer: None,
              discardIndex: -1,
              isBiddingCycle: true,
              isBiddingHideDenominationButtons: true,
              isDummyVisible: false,
              lastAction: "4 Passes - so New Deal",
              pack: Shuffle.getShuffledPack(), 
              randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
            }
          } else if (bidsLength >= 3) {
            let hd1 = List.hd(state.bids);
            let tl = List.tl(state.bids);
            let hd2 = List.hd(tl);
            if (hd1.isPass === true && hd2.isPass === true) {
              // get vulnerability based on number of scores so far
              let vulnerable = switch(List.length(state.chicagoScoreSheet) mod 4)  {
                | 0 => "None"
                | 1 => String.sub(Shuffle.pocAsString(state.dealer), 0, 1)
                | 2 => String.sub(Shuffle.pocAsString(state.dealer), 0, 1)
                | 3 => "All"
                | _ => "Error"
              };
              // helper func
              let partnerPocByPoc = (poc) => {
                switch (poc) {
                  | Some("North") => Some("South")
                  | Some("South") => Some("North")
                  | Some("West") => Some("East")
                  | Some("East") => Some("West")
                  | _ => Some("Error")
                }
              };
              // we need to add a row to the Chicago score sheet, so assemble here
              // filter out all Pass records
              let bidsListFiltered = Belt.List.keep(state.bids, x => x.isPass === false);
              let bidRecordOfInterest1 = List.hd(bidsListFiltered);
              let tailOfInterest = List.tl(bidsListFiltered);
              //Js.log("bidRecordOfinterest1:");
              //Js.log(bidRecordOfInterest1);
              let bidRecordOfInterest2 = 
                (bidRecordOfInterest1.contractLevel === None) 
                && 
                (
                  (bidRecordOfInterest1.isDoubled === true)
                  ||
                  (bidRecordOfInterest1.isRedoubled === true)
                )
                ?
                List.hd(tailOfInterest)
                :
                bidRecordOfInterest1
              ;
              let contractLevel = bidRecordOfInterest2.contractLevel;
              let contractSuit = bidRecordOfInterest2.contractSuit;
              let contractPoc = bidRecordOfInterest2.contractPointOfCompass;
              let isDoubled = (bidRecordOfInterest1.contractLevel === None) && (bidRecordOfInterest1.isDoubled === true);
              let isRedoubled = (bidRecordOfInterest1.contractLevel === None) && (bidRecordOfInterest1.isRedoubled === true);
              let totalTricksNorthSouth = 0;
              let scoreNorthSouth = None;
              let totalTricksWestEast = 0;
              let scoreWestEast = None;
              let bidsFilteredBySuitAnd2Poc = Belt.List.keep(state.bids, x => {
                x.contractSuit == contractSuit && (
                  x.contractPointOfCompass == contractPoc
                  ||
                  x.contractPointOfCompass == partnerPocByPoc(contractPoc)
                )
              });
              //Js.log("bidsFilteredBySuitAnd2Poc:");
              //Js.log(bidsFilteredBySuitAnd2Poc);
              let bidsFilteredBySuitAnd2PocReversed = Belt.List.reverse(bidsFilteredBySuitAnd2Poc);
              let hd3 = List.hd(bidsFilteredBySuitAnd2PocReversed);
              let contractDeclarer = hd3.contractPointOfCompass
              let chicagoScoreSheetRecord: Chicago.chicagoScoreSheetRecord = {
                vulnerable: vulnerable,
                contractLevel: contractLevel,
                contractSuit: contractSuit,
                contractDeclarer: contractDeclarer,
                isDoubled: isDoubled, 
                isRedoubled: isRedoubled, 
                totalTricksNorthSouth: totalTricksNorthSouth,
                scoreNorthSouth: scoreNorthSouth,
                totalTricksWestEast: totalTricksWestEast,
                scoreWestEast: scoreWestEast
              };
              // return end of bidding, but avoid new row if 4 passes by checking contractLevel
              {
                ...state,
                activePointOfCompass: Shuffle.getNextActivePointOfCompass(contractDeclarer),
                chicagoScoreSheet: 
                  contractLevel != None 
                  ?
                  [chicagoScoreSheetRecord ,...state.chicagoScoreSheet]
                  :
                  state.chicagoScoreSheet,
                declarer: contractDeclarer,
                isBiddingCycle: false,
                lastAction: 
                  contractLevel != None
                  ?
                  "BidAddSpecial- 3 Passes"
                  :
                  "BidAddSpecial- 4 Passes",
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
              contractPointOfCompass: None,
              isDoubled: true,
              isRedoubled: false,
              isPass: false
            },
            ...state.bids
          ],
          lastAction: "BidAddSpecial - X", 
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
          lastAction: "BidAddSpecial - XX", 
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
        }
        | _ => {
          // should never occur, and no change in state
          state
        }
      }
    }
    | EndTrick => {
      // only triggered on imminent 4 discards - see P5Event.js line 207
      // make sure doMessage is called in sidebar component
      let () = [%raw "window.isLastActionSync = false"];
      // check contract suit
      let scoreSheetRecord = List.hd(state.chicagoScoreSheet);
      let contractSuit = scoreSheetRecord.contractSuit;
      // get adjusted value of the cards
      let myAdjustedPackValue = Array.map(
        (card: Shuffle.card) => {
          Shuffle.getSuitAsOptionString(card.suit) === contractSuit
          ?
          {...card, noTrumpValue: card.noTrumpValue + 52}
          :
          {card}
        },
        state.pack
      );
      //Js.log("myAdjustedPackValue:");
      //Js.log(myAdjustedPackValue);
      // filter by lifecycle and also lead discard suit / trump suit
      let myFourCards = Belt.Array.keep(myAdjustedPackValue, x => {
        x.lifecycle === Discard
        &&
        (
          Some(x.suit) === state.discardSuit
          ||
          Shuffle.getSuitAsOptionString(x.suit) === contractSuit
        )
      });
      Js.log("myFourCards:");
      Js.log(myFourCards);
      let myFourCardsAsList = Belt.List.fromArray(myFourCards);
      // just sort the list with Belt!
      let myFourCardsAsListSorted = Belt.List.sort(myFourCardsAsList, (a, b) => {b.noTrumpValue - a.noTrumpValue})
      let optionWinningCard = Belt.List.head(myFourCardsAsListSorted);
      //Js.log("optionWinningCard");
      //Js.log(optionWinningCard);
      let winningCardFileName =
        switch (optionWinningCard) {
          | None => ""
          | Some(x) => x.fileName
        }
      Js.log("winningCard:");
      Js.log(winningCardFileName);
      // let winningCardValue =
      //   switch (optionWinningCard) {
      //     | None => -1
      //     | Some(x) => x.noTrumpValue
      //   }
      // Js.log("winningCardValue:");
      // Js.log(winningCardValue);
      let winningCardShuffleIndex =
        switch (optionWinningCard) {
          | None => -1
          | Some(x) => x.shuffleIndex
        }
      // Js.log("winningCardShuffleIndex:");
      // Js.log(winningCardShuffleIndex);
      let winningDiscardPoc = 
        if (winningCardShuffleIndex === -1) {
          "Error"
        } else if (winningCardShuffleIndex < 13) {
          "North"
        } else if (winningCardShuffleIndex < 26) {
          "East"
        } else if (winningCardShuffleIndex < 39) {
          "South"
        } else {
          "West"
        };
      //Js.log("winningDiscardPoc:");
      //Js.log(winningDiscardPoc);
      // let isPocDeclarerOrDummy = (poc, declarer) => {
      //   switch (poc) {
      //     | "North" | "South" => declarer === "North" || declarer === "South" ? true : false
      //     | "East" | "West" => declarer === "East" || declarer === "West" ? true : false
      //     | _ => false
      //   }
      // };
      // let declarerTrickIncrement = 
      //   isPocDeclarerOrDummy(winningDiscardPoc, Shuffle.pocAsString(scoreSheetRecord.contractDeclarer))
      //   ?
      //   1
      //   :
      //   0
      // ;
      //Js.log("declarerTrickIncrement:");
      //Js.log(declarerTrickIncrement);
      //let totalTricksNorthSouthIncrement = 0;
      //let totalTricksWestEastIncrement = 0;
      let totalTricksNorthSouthIncrement =
        // (
        //   scoreSheetRecord.contractDeclarer === Some("North")
        //   ||
        //   scoreSheetRecord.contractDeclarer === Some("South")
        // )
        // &&
        (
          winningDiscardPoc === "North"
          ||
          winningDiscardPoc === "South"
        )
        ?
        1
        :
        0
      ;
      let totalTricksWestEastIncrement =
        // (
        //   scoreSheetRecord.contractDeclarer === Some("West")
        //   ||
        //   scoreSheetRecord.contractDeclarer === Some("East")
        // )
        // &&
        (
          winningDiscardPoc === "West"
          ||
          winningDiscardPoc === "East"
        )
        ?
        1
        :
        0
      ;
      //Js.log("totalTricksNorthSouthIncrement:");
      //Js.log(totalTricksNorthSouthIncrement);
      //Js.log("totalTricksWestEastIncrement:");
      //Js.log(totalTricksWestEastIncrement);
      // prepare for the score sheet update - we only want to update the head of the list
      let chicagoScoreSheetHead = Belt.List.headExn(state.chicagoScoreSheet);
      let chicagoScoreSheetTail: Chicago.chicagoScoreSheet = Belt.List.tailExn(state.chicagoScoreSheet);
      let myChicagoScoreSheetRecord = 
        {
          ...chicagoScoreSheetHead, 
          totalTricksNorthSouth: chicagoScoreSheetHead.totalTricksNorthSouth + totalTricksNorthSouthIncrement,
          totalTricksWestEast: chicagoScoreSheetHead.totalTricksWestEast + totalTricksWestEastIncrement
        }
      // now we must check for end of round/deal by looking for countOfCardsWithLifecycleTrick = 48
      //let countOfCardsWithLifecycleTrick = Belt.Array.length(Belt.Array.keep(state.pack, x => x.lifecycle === Discard));
      // use discardIndex as this is really a cards clicked counter and more robust
      let myChicagoScoreSheetRecordWithOptionalScore =
        if (
          state.discardIndex === 51 
          ) {
          let myScoreLookupDenomination: Chicago.denomination =
            if (scoreSheetRecord.contractSuit === Some("Clubs") || scoreSheetRecord.contractSuit === Some("Diamonds")) {
              Minor
            } else if (scoreSheetRecord.contractSuit === Some("Hearts") || scoreSheetRecord.contractSuit === Some("Spades")) {
              Major
            } else if (scoreSheetRecord.contractSuit === Some("NoTrumps")) {
              NoTrumps
            } else {
              NoTrumps // should be unreachable code
            };
          let isVulnerable =
            if (scoreSheetRecord.vulnerable === "None") {
              false
            } else if (
                (scoreSheetRecord.vulnerable === "N" || scoreSheetRecord.vulnerable === "S")
                &&
                (scoreSheetRecord.contractDeclarer === Some("North") || scoreSheetRecord.contractDeclarer === Some("South"))
              ) {
              true
            } else if (
                (scoreSheetRecord.vulnerable === "W" || scoreSheetRecord.vulnerable === "E")
                &&
                (scoreSheetRecord.contractDeclarer === Some("West") || scoreSheetRecord.contractDeclarer === Some("East"))
              ) {
              true
            } else if (scoreSheetRecord.vulnerable === "All") {
              true
            } else {
              false   // catchall should never happen
            };
          let scoreLookup = Chicago.getScore(
            ~level = Shuffle.optionIntAsInt(scoreSheetRecord.contractLevel),
            ~denomination = myScoreLookupDenomination,
            ~tricksTotal = 
              (scoreSheetRecord.contractDeclarer === Some("North"))
              || 
              (scoreSheetRecord.contractDeclarer === Some("South"))
              ?
              chicagoScoreSheetHead.totalTricksNorthSouth + totalTricksNorthSouthIncrement
              :
              chicagoScoreSheetHead.totalTricksWestEast + totalTricksWestEastIncrement,
            ~isVulnerable = isVulnerable,
            ~isDoubled = false, // TO DO
            ~isRedoubled = false // TO DO
          );
          // some redundancy here, possibility of a bug
          // state.declarer and contract.declarer SHOULD always be the same
          {
            ...myChicagoScoreSheetRecord, 
            scoreNorthSouth: (state.declarer === Some("North")) || (state.declarer === Some("South")) ? Some(scoreLookup) : None,
            scoreWestEast: (state.declarer === Some("West")) || (state.declarer === Some("East")) ? Some(scoreLookup) : None
          }
        } else {
          myChicagoScoreSheetRecord
        };
      //Js.log("discardIndex:");
      //Js.log(state.discardIndex);
      // move all (should be 4 always) discarded cards into lifecycle Trick
      let myPack = Array.map(
        (card: Shuffle.card) => {
          card.lifecycle === Discard
          ?
          {...card, lifecycle: Trick}
          :
          {card}
        },
        state.pack
      );
      // only clear discard pile every 4 discards
      // actually this action is now only called once every 4 discards
      // so we do not need that constraint
      // conditional end-of-round update to poc signified by discardIndex = 51
      let endOfDealNextPoc = Shuffle.getNextPointOfCompass(state.dealer);
      {
        ...state, 
        activePointOfCompass: state.discardIndex !== 51 ? Some(winningDiscardPoc) : Some(endOfDealNextPoc),
        chicagoScoreSheet: [myChicagoScoreSheetRecordWithOptionalScore, ...chicagoScoreSheetTail],
        dealer: state.discardIndex !== 51 ? state.dealer : Some(endOfDealNextPoc),
        declarer: state.discardIndex !== 51 ? state.declarer : None,
        isReviewDealVisible: state.discardIndex !== 51 ? false : true,
        //pack: (state.discardIndex mod 4 ) === 3 ? myPack : state.pack,
        pack: myPack,
        lastAction: "End of Trick",
        randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k()
      }
    }
  }
};
