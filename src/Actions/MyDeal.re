// Online used in execute below
%raw
{|
  var Online = require('../Online.bs');
|};

let executeWithShuffle = (state: TopLevel.state) => {
  // aka btn "My Deal"
  //Js.log("Action-Shuffle");
  // make sure doMessage is called in sidebar component
  let () = [%raw "window.isLastActionSync = false"];
  // prepare another message alerting server to store the pack as dealt
  //let () = [%raw "setTimeout(function(){alert('StoreDeal');}, 750)"];
  let () = [%raw
    "setTimeout(function(){Online.doMessage('StoreDeal');}, 750)"
  ];
  // do change of dealer at end of deal ie 52 cards out
  // also set BiddingCycle to true here
  // force activePointOfCompass to be dealer
  // hide Dummy hand
  // set handVisible all to false in case previous deal has been Reviewed
  // ref Gill - show chicagoScoreSheetRecord at deal time so vulnerability is known
  // show partner as well as declarer
  let vulnerable =
    switch (List.length(state.chicagoScoreSheet) mod 5) {
    | 0 => "None"
    | 1
    | 2 =>
      switch (state.dealer) {
      | Some("North") => "NS"
      | Some("South") => "SN"
      | Some("East") => "EW"
      | Some("West") => "WE"
      | _ => "Err"
      }
    | 3 => "All"
    | _ => "Error"
    };
  let chicagoScoreSheetRecord: Chicago.chicagoScoreSheetRecord = {
    vulnerable,
    contractLevel: None,
    contractSuit: None,
    contractDeclarer: None,
    isDoubled: false,
    isRedoubled: false,
    totalTricksNorthSouth: None, //Some(0),
    scoreNorthSouth: None,
    totalTricksWestEast: None, //Some(0),
    scoreWestEast: None,
  };
  {
    ...state,
    activePointOfCompass: state.dealer,
    bids: [],
    chicagoScoreSheet: [chicagoScoreSheetRecord, ...state.chicagoScoreSheet],
    declarer: None,
    discardIndex: (-1),
    handVisible: Shuffle.initialHandVisible,
    isBiddingCycle: true,
    isBiddingHideDenominationButtons: true,
    isDummyVisible: false,
    isReviewDealVisible: false,
    lastAction: "Deal",
    pack: Shuffle.getShuffledPack(),
    randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
  };
};

let executeWithoutShuffle = (state: TopLevel.state) => {
  // aka btn Replay
  //Js.log("Action-Shuffle triggered from Replay");
  // make sure doMessage is called in sidebar component
  let () = [%raw "window.isLastActionSync = false"];
  // prepare another message alerting server to store the pack
  // benign?
  let () = [%raw
    "setTimeout(function(){Online.doMessage('StoreDeal');}, 750)"
  ];
  // do NOT change vulnerability for a Replay, use previous value
  // should never fail as btn Replay is hidden on first round
  // identify Replay by setting scoreXX to Some(0) rather than None (bodge)
  // then on any MyDeal we can check the head record, and if one of the scoreXX is still zero
  // then delete the entire row
  let chicagoScoreSheetHead = List.hd(state.chicagoScoreSheet);
  let chicagoScoreSheetRecord: Chicago.chicagoScoreSheetRecord = {
    vulnerable: chicagoScoreSheetHead.vulnerable,
    contractLevel: None,
    contractSuit: None,
    contractDeclarer: None,
    isDoubled: false,
    isRedoubled: false,
    totalTricksNorthSouth: None,
    scoreNorthSouth: Some(0),
    totalTricksWestEast: None,
    scoreWestEast: Some(0),
  };
  // we need to move the dealer back one position!
  let lastDealer = Shuffle.getLastActivePointOfCompass(state.dealer);
  {
    ...state,
    activePointOfCompass: lastDealer,
    bids: [],
    chicagoScoreSheet: [chicagoScoreSheetRecord, ...state.chicagoScoreSheet],
    declarer: None,
    discardIndex: (-1),
    handVisible: Shuffle.initialHandVisible,
    isBiddingCycle: true,
    isBiddingHideDenominationButtons: true,
    isDummyVisible: false,
    isReviewDealVisible: false,
    lastAction: "Replay",
    randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
  };
};

let execute = (state: TopLevel.state, isMyDeal: bool) =>
  if (isMyDeal == true) {
    executeWithShuffle(state);
  } else {
    executeWithoutShuffle(state);
  };
