%raw
{|
  var Online = require('./Online.bs');
|};

type action =
  //| NewGame
  | Shuffle(bool)
  //| Flip (Shuffle.compassPoint)
  | Discard
  | PostDiscard
  | Sync
  | LoginSync
  | Test
  | AssignPlayer(Shuffle.pointOfCompassAndPlayer)
  | BidAdd(option(int))
  | BidUpdate(option(string))
  | BidAddSpecial(option(string))
  | PostBid
  | EndOneTrick
  | Concede
  | Post4Passes;

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
  discardPocForTransition: None,
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
    northStartY: 0.0,
    eastStartX: 0.0,
    southStartY: 0.0,
    westStartX: 0.0,
    northEndY: 0.0,
    eastEndX: 0.0,
    southEndY: 0.0,
    westEndX: 0.0,
    northStartX: 0.0,
    eastStartY: 0.0,
    southStartX: 0.0,
    westStartY: 0.0,
    northStartXInv: 0.0,
    eastStartYInv: 0.0,
    southStartXInv: 0.0,
    westStartYInv: 0.0,
    northStartYInv: 0.0,
    eastStartXInv: 0.0,
    southStartYInv: 0.0,
    westStartXInv: 0.0,
    northEndX: 0.0,
    eastEndY: 0.0,
    southEndX: 0.0,
    westEndY: 0.0,
  },
};

let reducer = (state: TopLevel.state, action) => {
  switch (action) {
  // superseded by Restart as ws message sent direct to server
  // | NewGame => {
  //   // aka Reboot aka Restart
  // }
  | Shuffle(isMyDeal) => MyDeal.execute(state, isMyDeal)
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
    // NB we CANNOT store window.innerHeight as part of state,
    // because it may vary between both different devices and between states!
    // All refs here to start and end locations are therefore normalised to
    // between 0.0 and 1.0 in both the X and Y directions
    // transition end calcs
    let m: float = [%raw "window.m"];
    let cardHeightToCanvasHeightRatio: float = [%raw
      "window.cardHeightToCanvasHeightRatio"
    ];
    let cardAspectRatio: float = [%raw "window.cardAspectRatio"];
    let cardWidthNormalized =
      m *. cardHeightToCanvasHeightRatio /. cardAspectRatio;
    let cardHeightNormalized = m *. cardHeightToCanvasHeightRatio;
    let cardWidthOffsetFraction: float = [%raw
      "window.cardWidthOffsetFraction"
    ];
    let cardHeightOffsetFraction: float = [%raw
      "window.cardHeightOffsetFraction"
    ];
    let northEndY = -. cardHeightNormalized *. cardHeightOffsetFraction;
    let eastEndX = cardWidthNormalized *. cardWidthOffsetFraction;
    let southEndY = cardHeightNormalized *. cardHeightOffsetFraction;
    let westEndX = -. cardWidthNormalized *. cardWidthOffsetFraction;
    //Js.log("cardWidthNormalized");
    //Js.log(cardWidthNormalized);
    let discardStartPositionIndex: float = [%raw
      "window.discardStartPositionIndex"
    ];
    Js.log("discardStartPositionIndex");
    Js.log(discardStartPositionIndex);
    // let tR = {
    //   switch (discardPoc) {
    //   | "North" => {
    //       ...state.transition,
    //       northStartY: (-0.5),
    //       northEndY,
    //       northStartX: discardStartPositionIndex,
    //       northStartXInv: -. discardStartPositionIndex,
    //       northEndX: 0.0,
    //     }
    //   | "East" => {
    //       ...state.transition,
    //       eastStartX: 0.5,
    //       eastEndX,
    //       eastStartY: discardStartPositionIndex,
    //       eastStartYInv: -. discardStartPositionIndex,
    //       eastEndY: 0.0,
    //     }
    //   | "South" => {
    //       ...state.transition,
    //       southStartY: 0.5,
    //       southEndY,
    //       southStartX: discardStartPositionIndex,
    //       southStartXInv: -. discardStartPositionIndex,
    //       southEndX: 0.0,
    //     }
    //   | "West" => {
    //       ...state.transition,
    //       westStartX: (-0.5),
    //       westEndX,
    //       westStartY: discardStartPositionIndex,
    //       westStartYInv: -. discardStartPositionIndex,
    //       westEndY: 0.0,
    //     }
    //   | _ => state.transition
    //   };
    // };
    let tR = {
      switch (discardPoc) {
      | "North" => {
          ...state.transition,
          northStartY: (-0.5),
          northEndY,
          northStartX: 0.0,
          northStartXInv: 0.0,
          northEndX: 0.0,
        }
      | "East" => {
          ...state.transition,
          eastStartX: 0.5,
          eastEndX,
          eastStartY: 0.0,
          eastStartYInv: 0.0,
          eastEndY: 0.0,
        }
      | "South" => {
          ...state.transition,
          southStartY: 0.5,
          southEndY,
          southStartX: 0.0,
          southStartXInv: 0.0,
          southEndX: 0.0,
        }
      | "West" => {
          ...state.transition,
          westStartX: (-0.5),
          westEndX,
          westStartY: 0.0,
          westStartYInv: 0.0,
          westEndY: 0.0,
        }
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
    let _myID: int =
      Array.length(myDiscardArray) === 4
        ? [%raw
          "setTimeout(function(){document.getElementById('btnPostDiscard').click();}, 2250)"
        ]
        : 0;
    {
      ...state,
      //activePointOfCompass: poc,
      activePointOfCompass: Array.length(myDiscardArray) === 4 ? None : poc,
      discardIndex: state.discardIndex + 1,
      discardPointOfCompass:
        (state.discardIndex + 1) mod 4 === 0
          ? Some(discardPoc) : state.discardPointOfCompass,
      discardPocForTransition: Some(discardPoc),
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
  | PostDiscard =>
    // only triggered after 4 discards detected, so there will be 4 cards to transition
    // transition is opposite way to a discard,
    // starts at discard poc and ends at winning poc
    // NB we CANNOT store window.innerHeight as part of state,
    // because it may vary between both different devices and between states!
    // All refs here to start and end locations are therefore normalised to
    // between 0.0 and 1.0 in both the X and Y directions
    // transition start calcs
    let m: float = [%raw "window.m"];
    let cardHeightToCanvasHeightRatio: float = [%raw
      "window.cardHeightToCanvasHeightRatio"
    ];
    let cardAspectRatio: float = [%raw "window.cardAspectRatio"];
    let cardWidthNormalized =
      m *. cardHeightToCanvasHeightRatio /. cardAspectRatio;
    let cardHeightNormalized = m *. cardHeightToCanvasHeightRatio;
    let cardWidthOffsetFraction: float = [%raw
      "window.cardWidthOffsetFraction"
    ];
    let cardHeightOffsetFraction: float = [%raw
      "window.cardHeightOffsetFraction"
    ];
    let northStartY = -. cardHeightNormalized *. cardHeightOffsetFraction;
    let eastStartX = cardWidthNormalized *. cardWidthOffsetFraction;
    let southStartY = cardHeightNormalized *. cardHeightOffsetFraction;
    let westStartX = -. cardWidthNormalized *. cardWidthOffsetFraction;

    let winningDiscardPoc = TopLevel.getWinningDiscardPoc(state);
    let winningDiscardOffset = 0.5;
    let commonEndPositionY = {
      switch (winningDiscardPoc) {
      | "North" => -. winningDiscardOffset -. cardHeightNormalized *. 0.5
      | "East" => 0.0
      | "South" => winningDiscardOffset +. cardHeightNormalized *. 0.5
      | "West" => 0.0
      | _ => 0.0
      };
    };
    let commonEndPositionX = {
      switch (winningDiscardPoc) {
      | "North" => 0.0
      | "East" => winningDiscardOffset +. cardWidthNormalized *. 0.5
      | "South" => 0.0
      | "West" => -. winningDiscardOffset -. cardWidthNormalized *. 0.5
      | _ => 0.0
      };
    };

    let northEndY = commonEndPositionY;
    let eastEndY = commonEndPositionY;
    let southEndY = commonEndPositionY;
    let westEndY = commonEndPositionY;

    let northEndX = commonEndPositionX;
    let eastEndX = commonEndPositionX;
    let westEndX = commonEndPositionX;
    let southEndX = commonEndPositionX;

    // test
    let northStartX = 0.0;
    let eastStartY = 0.0;
    let southStartX = 0.0;
    let westStartY = 0.0;
    // added later
    let northStartXInv = 0.0;
    let eastStartYInv = 0.0;
    let southStartXInv = 0.0;
    let westStartYInv = 0.0;
    let northStartYInv = 0.0;
    let eastStartXInv = 0.0;
    let southStartYInv = 0.0;
    let westStartXInv = 0.0;
    let tR: Shuffle.transition = {
      northStartY,
      northEndY,
      eastStartX,
      eastEndX,
      southStartY,
      southEndY,
      westStartX,
      westEndX,
      northStartX,
      northEndX,
      eastStartY,
      eastEndY,
      southStartX,
      southEndX,
      westStartY,
      westEndY,
      northStartXInv,
      eastStartYInv,
      southStartXInv,
      westStartYInv,
      northStartYInv,
      eastStartXInv,
      southStartYInv,
      westStartXInv,
    };
    let _myID: int = [%raw
      "setTimeout(function(){document.getElementById('btnEndTrick').click();}, 375)"
    ];
    {...state, transition: tR, lastAction: "PostDiscard"};
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
      discardPocForTransition: None,
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
        northStartY: 0.0,
        eastStartX: 0.0,
        southStartY: 0.0,
        westStartX: 0.0,
        northEndY: 0.0,
        eastEndX: 0.0,
        southEndY: 0.0,
        westEndX: 0.0,
        northStartX: 0.0,
        eastStartY: 0.0,
        southStartX: 0.0,
        westStartY: 0.0,
        northStartXInv: 0.0,
        eastStartYInv: 0.0,
        southStartXInv: 0.0,
        westStartYInv: 0.0,
        northStartYInv: 0.0,
        eastStartXInv: 0.0,
        southStartYInv: 0.0,
        westStartXInv: 0.0,
        northEndX: 0.0,
        eastEndY: 0.0,
        southEndX: 0.0,
        westEndY: 0.0,
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
    let discardPocForTransition: option(string) = [%bs.raw
      "window.gameState.discardPocForTransition"
    ];
    // use reason code, not js
    //let pOCAPlength = Belt.Array.length(pOCAP);
    // Js.log("pOCAP length");
    // Js.log(pOCAPlength);
    let myName = [%bs.raw "userState.player"];
    let filteredPocAP = Belt.Array.keep(pOCAP, x => x.player === myName);
    // Js.log("pOCAP array");
    // Js.log(filteredPocAP);
    // this may blow up on user logout? - yes it does
    let () =
      Belt.Array.length(filteredPocAP) != 0
        ? {
          let myPOC = filteredPocAP[0].pointOfCompass;
          // Js.log("myPoc");
          // Js.log(myPOC);
          // use myPoc value to set 6PM
          let () =
            switch (myPOC) {
            | "Observer" =>
              %bs.raw
              "window.userState.tableRotationDegrees = 0"
            | "South" =>
              %bs.raw
              "window.userState.tableRotationDegrees = 0"
            | "East" =>
              %bs.raw
              "window.userState.tableRotationDegrees = 90"
            | "North" =>
              %bs.raw
              "window.userState.tableRotationDegrees = 180"
            | "West" =>
              %bs.raw
              "window.userState.tableRotationDegrees = 270"
            | _ => Js.log("Poc not assigned")
            };
          ();
        }
        : {
          ();
        };
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
      discardPocForTransition,
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
    Js.log(
      "action AssignPlayer "
      ++ pOfCAndP.player
      ++ " to "
      ++ pOfCAndP.pointOfCompass,
    );
    let thisPlayer = [%raw "window.userState.player"];
    Js.log("current player: " ++ thisPlayer);
    // rotate the user to be seated at 6PM but only if it is this user
    pOfCAndP.player == thisPlayer
      ? switch (pOfCAndP.pointOfCompass) {
        | "South" =>
          %raw
          "window.userState.tableRotationDegrees = 0"
        | "East" =>
          %raw
          "window.userState.tableRotationDegrees = 90"
        | "North" =>
          %raw
          "window.userState.tableRotationDegrees = 180"
        | "West" =>
          %raw
          "window.userState.tableRotationDegrees = 270"
        | _ => Js.log("Unexpected pOfCAndP.pointOfCompass")
        }
      : ();
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
        // trigger a later PostBid action
        let _myID: int = [%raw
          "setTimeout(function(){document.getElementById('btnPost4Passes').click();}, 2500)"
        ];
        // don't change anything just yet except for adding the PASS into the bid table
        {
          ...state,
          // unexpectedly, we need to actually add the last PASS to the bid table so it is visible to players
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
          lastAction: "4 Passes",
        };
      } else if (bidsLength >= 3) {
        let hd1 = List.hd(state.bids);
        let tl = List.tl(state.bids);
        let hd2 = List.hd(tl);
        if (hd1.isPass === true && hd2.isPass === true) {
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
          // removed so we can see Some(0) set by Replay
          //let scoreNorthSouth = None;
          let totalTricksWestEast = Some(0);
          //let scoreWestEast = None;
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
            totalTricksWestEast,
          };
          // also need to adjust the card handOrder to match the contractSuit if any
          let myPack =
            Array.map(
              (card: Shuffle.card) => {
                switch (contractSuit) {
                | Some("NoTrumps") =>
                  card.handOrder <= 12
                    ? {...card, handOrder: card.handOrder + 300}
                    : {
                      card;
                    }
                | Some("Hearts") =>
                  card.handOrder <= 438 && card.handOrder >= 426
                    ? {...card, handOrder: card.handOrder + 300}
                    : {
                      card;
                    }
                | Some("Diamonds") =>
                  card.handOrder <= 12
                    ? {...card, handOrder: card.handOrder + 700}
                    : {
                      card;
                    }
                | Some("Clubs") =>
                  card.handOrder <= 225 && card.handOrder >= 213
                    ? {...card, handOrder: card.handOrder + 600}
                    : {
                      card;
                    }
                | _ => card
                }
              },
              state.pack,
            );
          // Hearts and Clubs contractSuits only need further adjustment to hand order
          let myPack2 =
            Array.map(
              (card: Shuffle.card) => {
                switch (contractSuit) {
                | Some("Hearts") =>
                  card.handOrder <= 12
                    ? {...card, handOrder: card.handOrder + 300}
                    : {
                      card;
                    }
                | Some("Clubs") =>
                  card.handOrder <= 438 && card.handOrder >= 426
                    ? {...card, handOrder: card.handOrder + 300}
                    : {
                      card;
                    }
                | _ => card
                }
              },
              myPack,
            );
          // trigger a later PostBid action
          let _myID: int = [%raw
            "setTimeout(function(){document.getElementById('btnPostBid').click();}, 2500)"
          ];
          // return end of bidding, but avoid new row if 4 passes by checking contractLevel
          {
            ...state,
            // activePointOfCompass:
            //   Shuffle.getNextActivePointOfCompass(contractDeclarer),
            // cannot have active poc just yet, wait until PostBid action
            activePointOfCompass: None,
            // if no contract level, then lose the row created at deal time
            chicagoScoreSheet:
              contractLevel != None
                ? [myChicagoScoreSheetRecord, ...chicagoScoreSheetTail]
                : chicagoScoreSheetTail,
            declarer: contractDeclarer,
            // we now delay the hiding of the bid table until PostBid action
            //isBiddingCycle: false,
            // unexpectedly, we need to actually add the last PASS to the bid table so it is visible to players
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
            lastAction:
              contractLevel != None
                ? "BidAddSpecial- 3 Passes" : "BidAddSpecial- 4 Passes",
            randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
            pack: myPack2,
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
  | PostBid => {
      ...state,
      activePointOfCompass:
        Shuffle.getNextActivePointOfCompass(state.declarer),
      isBiddingCycle: false,
      lastAction: "Post Bid after 3 passes",
    }
  | EndOneTrick => EndTrick.execute(state)
  | Concede => Concede.execute(state)
  | Post4Passes => Post4Passes.execute(state)
  };
};
