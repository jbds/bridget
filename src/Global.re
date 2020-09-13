%raw
{|
  var Online = require('./Online.bs');
|};

type action =
  //| NewGame
  | Shuffle
  //| Flip (Shuffle.compassPoint)
  | Discard
  | Sync
  | LoginSync
  | Test
  | AssignPlayer(Shuffle.pointOfCompassAndPlayer)
  | BidAdd(option(int))
  | BidUpdate(option(string))
  | BidAddSpecial(option(string))
  | EndTrick;

// type state is degined in TopLevel.re to avoid a circular dependency error

// this is used by the reducer at app startup, before being overwritten
// by later actions
// Note the only thing we set here is the starting active poc and dealer
let initialState: TopLevel.state = {
  activePointOfCompass: None, // Some(Shuffle.initialPoc), - do this at server!
  bids: [],
  chicagoScoreSheet: Chicago.initialChicagoScoreSheet,
  dealer: None, // Some(Shuffle.initialPoc), - do this at server!
  dealIndex: (-1),
  declarer: None,
  discardIndex: (-1),
  discardSuit: None,
  discardPointOfCompass: None,
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
  transition: {
    northDiscardY: 0.0,
    eastDiscardX: 0.0,
    southDiscardY: 0.0,
    westDiscardX: 0.0,
  },
};

let reducer = (state: TopLevel.state, action) => {
  switch (action) {
  // superseded by Restart as ws message sent direct to server
  // | NewGame => {
  //   // aka Reboot aka Restart
  // }
  | Shuffle => MyDeal.execute(state)
  // | Flip (compassPoint) => {
  //  became redundant
  // }
  | Discard =>
    // make sure doMessage IS called in sidebar component
    let () = [%raw "window.isLastActionSync = false"];
    // attempt to set state to gameState failed, must update state correctly
    let discardFileName: string = [%raw "window.discardFileName"];
    let cardWrappedInArray =
      Belt.Array.keep(state.pack, x => x.fileName === discardFileName);
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
        "North";
      } else if (cardShuffleIndex < 26) {
        "East";
      } else if (cardShuffleIndex < 39) {
        "South";
      } else {
        "West";
      };
    //Js.log("discardPoc:");
    //Js.log(discardPoc);
    // we need to know which poc folows declarer
    let pocFollowingDeclarer =
      if (state.declarer == Some("North")) {
        "East";
      } else if (state.declarer == Some("East")) {
        "South";
      } else if (state.declarer == Some("South")) {
        "West";
      } else if (state.declarer == Some("West")) {
        "North";
      } else {
        "";
      };
    //Js.log("pocFollowingDeclarer:")
    //Js.log(pocFollowingDeclarer);
    // move the selected card into the discard pile
    let myPack =
      Array.map(
        (card: Shuffle.card) => {
          card.fileName === discardFileName
            ? {...card, lifecycle: Discard}
            : {
              card;
            }
        },
        state.pack,
      );
    // transition
    let baizeHeight: int = [%raw "window.innerHeight"];
    let halfBaizeHeight = float_of_int(baizeHeight) /. 2.0;
    //Js.log("halfBaizeHeight");
    //Js.log(halfBaizeHeight);
    let tR = {
      switch (discardPoc) {
      | "North" => {...state.transition, northDiscardY: -. halfBaizeHeight}
      | "East" => {...state.transition, eastDiscardX: halfBaizeHeight}
      | "South" => {...state.transition, southDiscardY: halfBaizeHeight}
      | "West" => {...state.transition, westDiscardX: -. halfBaizeHeight}
      | _ => state.transition
      };
    };
    // move on to next poc!
    let poc =
      Some(Shuffle.getNextPointOfCompass(state.activePointOfCompass));
    // have we got 4 in the discard pile?
    let myDiscardArray = Belt.Array.keep(myPack, x => x.lifecycle === Discard);
    Js.log("QtyDiscards");
    Js.log(Array.length(myDiscardArray));
    {
      ...state,
      activePointOfCompass: poc,
      discardIndex: state.discardIndex + 1,
      discardPointOfCompass:
        (state.discardIndex + 1) mod 4 === 0
          ? Some(discardPoc) : state.discardPointOfCompass,
      discardSuit:
        (state.discardIndex + 1) mod 4 === 0
          ? Some(cardDiscardSuit) : state.discardSuit,
      isDummyVisible:
        discardPoc === pocFollowingDeclarer ? true : state.isDummyVisible,
      pack: myPack,
      randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
      lastAction: "Discard",
      transition: tR,
    };
  | Sync =>
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
      dealIndex: (-1),
      declarer: None,
      discardIndex: (-1),
      discardPointOfCompass: None,
      discardSuit: None,
      handVisible: {
        north: false,
        east: false,
        south: false,
        west: false,
      },
      isBiddingCycle: false,
      isBiddingHideDenominationButtons: true,
      isDummyVisible: false,
      isRebootVisible: false,
      isReviewDealVisible: false,
      lastAction: "Logout or Server Down",
      pack: [||],
      pointOfCompassAndPlayers: [||],
      randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
      transition: {
        northDiscardY: 0.0,
        eastDiscardX: 0.0,
        southDiscardY: 0.0,
        westDiscardX: 0.0,
      },
    };
  | LoginSync =>
    // Client state is now ENTIRELY REPLACED with server gameState
    // this is same as Sync above, and we do also want to suppress doMessage
    let () = [%raw "window.isLastActionSync = true"];
    // we must make sure that state is updated by every gameState field
    let cSS: list(Chicago.chicagoScoreSheetRecord) = [%bs.raw
      "window.gameState.chicagoScoreSheet"
    ];
    let dealer: option(string) = [%bs.raw "window.gameState.dealer"];
    let declarer: option(string) = [%bs.raw "window.gameState.declarer"];
    let hV: Shuffle.handVisible = [%bs.raw "window.gameState.handVisible"];
    let tR: Shuffle.transition = [%bs.raw "window.gameState.transition"];
    let pOCAP: array(Shuffle.pointOfCompassAndPlayer) = [%bs.raw
      "window.gameState.pointOfCompassAndPlayers"
    ];
    // lastAction is an exception, we always want to hard code this below
    let pack: Shuffle.pack = [%bs.raw "window.gameState.pack"];
    // randomInt ia another exception
    let dealIndex: int = [%bs.raw "window.gameState.dealIndex"];
    let isBiddingCycle: bool = [%bs.raw "window.gameState.isBiddingCycle"];
    let poc: option(string) = [%bs.raw
      "window.gameState.activePointOfCompass"
    ];
    let bids: Chicago.bids = [%bs.raw "window.gameState.bids"];
    let isBiddingHideDenominationButtons: bool = [%bs.raw
      "window.gameState.isBiddingHideDenominationButtons"
    ];
    let isRebootVisible: bool = [%bs.raw "window.gameState.isRebootVisible"];
    let isReviewDealVisible: bool = [%bs.raw
      "window.gameState.isReviewDealVisible"
    ];
    let isDummyVisible: bool = [%bs.raw "window.gameState.isDummyVisible"];
    let discardIndex: int = [%bs.raw "window.gameState.discardIndex"];
    let discardSuit: option(Shuffle.suit) = [%bs.raw
      "window.gameState.discardSuit"
    ];
    let lastAction: string = [%bs.raw "window.gameState.lastAction"];
    let discardPointOfCompass: option(string) = [%bs.raw
      "window.gameState.discardPointOfCompass"
    ];
    // no need for ...state here as we are replacing all fields with the server gameState fields
    {
      activePointOfCompass: poc,
      bids,
      chicagoScoreSheet: cSS,
      dealer,
      dealIndex,
      declarer,
      discardIndex,
      discardPointOfCompass,
      discardSuit,
      handVisible: hV,
      isBiddingCycle,
      isBiddingHideDenominationButtons,
      isDummyVisible,
      isRebootVisible,
      isReviewDealVisible,
      lastAction,
      pack,
      pointOfCompassAndPlayers: pOCAP,
      randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
      transition: tR,
    };
  | Test =>
    // make sure doMessage is NOT called in sidebar component
    let () = [%raw "window.isLastActionSync = true"];
    //Js.log("benign action: 'Test'");
    {
      ...state,
      lastAction: "Test",
      randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
    };
  | AssignPlayer(pOfCAndP) =>
    //Js.log("Action-AssignPlayer");
    // make sure doMessage is called in sidebar component
    let () = [%raw "window.isLastActionSync = false"];
    //Js.log("action AssignPlayer " ++ pOfCAndP.player ++ " to " ++ pOfCAndP.pointOfCompass);
    //let myNewArray = state.pointOfCompassAndPlayers;
    //{...state, pointOfCompassAndPlayers: myNewArray}
    // unassign any existing requested pointOfCompass
    // unless it is an Observer...
    let myArray1 =
      Array.map(
        (pointOfCompassAndPlayer: Shuffle.pointOfCompassAndPlayer) => {
          pointOfCompassAndPlayer.pointOfCompass == pOfCAndP.pointOfCompass
          && pointOfCompassAndPlayer.pointOfCompass != "Observer"
            ? {...pointOfCompassAndPlayer, pointOfCompass: ""}
            : {
              pointOfCompassAndPlayer;
            }
        },
        state.pointOfCompassAndPlayers,
      );
    // assign the requested pointOfCompass to correct player
    let myArray2 =
      Array.map(
        (pointOfCompassAndPlayer: Shuffle.pointOfCompassAndPlayer) => {
          pointOfCompassAndPlayer.player == pOfCAndP.player
            ? {
              ...pointOfCompassAndPlayer,
              pointOfCompass: pOfCAndP.pointOfCompass,
            }
            : {
              pointOfCompassAndPlayer;
            }
        },
        myArray1,
      );
    {
      ...state,
      pointOfCompassAndPlayers: myArray2,
      lastAction: "AssignPlayer",
      randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
    };
  | BidAdd(contractLevel) =>
    //Js.log("Action - BidAdd")
    // make sure doMessage is called in sidebar component
    let () = [%raw "window.isLastActionSync = false"];
    //Js.log(state.bids);
    {
      ...state,
      bids: [
        {
          contractLevel,
          contractSuit: Some(""),
          contractPointOfCompass: state.activePointOfCompass,
          isDoubled: false,
          isRedoubled: false,
          isPass: false,
        },
        ...state.bids,
      ],
      isBiddingHideDenominationButtons: false,
      lastAction: "BidAdd",
      randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
    };
  | BidUpdate(contractSuit) =>
    //Js.log("Action - BidUpdate")
    // make sure doMessage is called in sidebar component
    let () = [%raw "window.isLastActionSync = false"];
    // we can do an immutable update
    let bids = state.bids;
    let head = List.hd(bids);
    //Js.log(head);
    let newHead = {...head, contractSuit};
    //Js.log(newHead);
    let tail = List.tl(bids);
    let bidsUpdated = [newHead, ...tail];
    //Js.log(bidsUpdated);
    // move on to next poc!
    let poc =
      Some(Shuffle.getNextPointOfCompass(state.activePointOfCompass));
    {
      ...state,
      activePointOfCompass: poc,
      bids: bidsUpdated,
      isBiddingHideDenominationButtons: true,
      lastAction: "BidUpdate",
      randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
    };
  | BidAddSpecial(special) =>
    //Js.log("Action - BidAddSpecial")
    // make sure doMessage is called in sidebar component
    let () = [%raw "window.isLastActionSync = false"];
    // move on to next poc
    let poc =
      Some(Shuffle.getNextPointOfCompass(state.activePointOfCompass));
    //Js.log(poc);
    switch (special) {
    | Some("Pass") =>
      // check for end of bidding cycle
      let bidsLength = List.length(state.bids);
      Js.log("bidsLength:");
      Js.log(bidsLength);
      Js.log("state.bids keep by isPass===false:");
      Js.log(Belt.List.keep(state.bids, x => x.isPass === false) === []);
      // special case 4 passes at start, beware bidslength will only be 3!
      if (bidsLength === 3
          && Belt.List.keep(state.bids, x => x.isPass === false) === []) {
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
          discardIndex: (-1),
          isBiddingCycle: true,
          isBiddingHideDenominationButtons: true,
          isDummyVisible: false,
          lastAction: "4 Passes - so fresh cards dealt",
          pack: Shuffle.getShuffledPack(),
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
        };
      } else if (bidsLength >= 3) {
        let hd1 = List.hd(state.bids);
        let tl = List.tl(state.bids);
        let hd2 = List.hd(tl);
        if (hd1.isPass === true && hd2.isPass === true) {
          // get vulnerability based on number of scores so far
          // was mod 4 until subtotal row to account for
          // now mod 5
          // show partner as well as declarer
          // vulnerability is now set at deal time
          // let vulnerable =
          //   switch (List.length(state.chicagoScoreSheet) mod 5) {
          //   | 0 => "None"
          //   | 1
          //   | 2 =>
          //     switch (state.dealer) {
          //     | Some("North") => "NS"
          //     | Some("South") => "SN"
          //     | Some("East") => "EW"
          //     | Some("West") => "WE"
          //     | _ => "Err"
          //     }
          //   | 3 => "All"
          //   | _ => "Error"
          //   };
          // helper func
          let partnerPocByPoc = poc => {
            switch (poc) {
            | Some("North") => Some("South")
            | Some("South") => Some("North")
            | Some("West") => Some("East")
            | Some("East") => Some("West")
            | _ => Some("Error")
            };
          };
          // we need to add a row to the Chicago score sheet, so assemble here
          // filter out all Pass records
          let bidsListFiltered =
            Belt.List.keep(state.bids, x => x.isPass === false);
          let bidRecordOfInterest1 = List.hd(bidsListFiltered);
          let tailOfInterest = List.tl(bidsListFiltered);
          //Js.log("bidRecordOfinterest1:");
          //Js.log(bidRecordOfInterest1);
          let bidRecordOfInterest2 =
            bidRecordOfInterest1.contractLevel === None
            && (
              bidRecordOfInterest1.isDoubled === true
              || bidRecordOfInterest1.isRedoubled === true
            )
              ? List.hd(tailOfInterest) : bidRecordOfInterest1;

          let contractLevel = bidRecordOfInterest2.contractLevel;
          let contractSuit = bidRecordOfInterest2.contractSuit;
          let contractPoc = bidRecordOfInterest2.contractPointOfCompass;
          let isDoubled =
            bidRecordOfInterest1.contractLevel === None
            && bidRecordOfInterest1.isDoubled === true;
          let isRedoubled =
            bidRecordOfInterest1.contractLevel === None
            && bidRecordOfInterest1.isRedoubled === true;
          let totalTricksNorthSouth = Some(0);
          let scoreNorthSouth = None;
          let totalTricksWestEast = Some(0);
          let scoreWestEast = None;
          let bidsFilteredBySuitAnd2Poc =
            Belt.List.keep(state.bids, x => {
              x.contractSuit == contractSuit
              && (
                x.contractPointOfCompass == contractPoc
                || x.contractPointOfCompass == partnerPocByPoc(contractPoc)
              )
            });
          //Js.log("bidsFilteredBySuitAnd2Poc:");
          //Js.log(bidsFilteredBySuitAnd2Poc);
          let bidsFilteredBySuitAnd2PocReversed =
            Belt.List.reverse(bidsFilteredBySuitAnd2Poc);
          let hd3 = List.hd(bidsFilteredBySuitAnd2PocReversed);
          let contractDeclarer = hd3.contractPointOfCompass;
          // fetch existing record from scoresheet
          // prepare for the score sheet update - we only want to update the head of the list
          let chicagoScoreSheetHead =
            Belt.List.headExn(state.chicagoScoreSheet);
          let chicagoScoreSheetTail: Chicago.chicagoScoreSheet =
            Belt.List.tailExn(state.chicagoScoreSheet);
          let myChicagoScoreSheetRecord = {
            ...chicagoScoreSheetHead,
            contractLevel,
            contractSuit,
            contractDeclarer,
            isDoubled,
            isRedoubled,
            totalTricksNorthSouth,
            scoreNorthSouth,
            totalTricksWestEast,
            scoreWestEast,
          };
          // replaced with the above
          // let chicagoScoreSheetRecord: Chicago.chicagoScoreSheetRecord = {
          //   vulnerable,
          //   contractLevel,
          //   contractSuit,
          //   contractDeclarer,
          //   isDoubled,
          //   isRedoubled,
          //   totalTricksNorthSouth,
          //   scoreNorthSouth,
          //   totalTricksWestEast,
          //   scoreWestEast,
          // };
          // return end of bidding, but avoid new row if 4 passes by checking contractLevel
          {
            ...state,
            activePointOfCompass:
              Shuffle.getNextActivePointOfCompass(contractDeclarer),
            // chicagoScoreSheet:
            //   contractLevel != None
            //     ? [chicagoScoreSheetRecord, ...state.chicagoScoreSheet]
            //     : state.chicagoScoreSheet,
            // if no contract level, then lose the row created at deal time
            chicagoScoreSheet:
              contractLevel != None
                ? [myChicagoScoreSheetRecord, ...chicagoScoreSheetTail]
                : chicagoScoreSheetTail,
            declarer: contractDeclarer,
            isBiddingCycle: false,
            lastAction:
              contractLevel != None
                ? "BidAddSpecial- 3 Passes" : "BidAddSpecial- 4 Passes",
            randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
          };
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
                isPass: true,
              },
              ...state.bids,
            ],
            lastAction: "BidAddSpecial",
            randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
          };
        };
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
              isPass: true,
            },
            ...state.bids,
          ],
          lastAction: "BidAddSpecial",
          randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
        };
      };
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
            isPass: false,
          },
          ...state.bids,
        ],
        lastAction: "BidAddSpecial - X",
        randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
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
            isPass: false,
          },
          ...state.bids,
        ],
        lastAction: "BidAddSpecial - XX",
        randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
      }
    | _ =>
      // should never occur, and no change in state
      state
    };
  | EndTrick => EndTrick.execute(state)
  };
};
