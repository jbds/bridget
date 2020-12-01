let execute = (state: TopLevel.state) => {
  // bug fix - we must also store this re-deal!
  let () = [%raw
    "setTimeout(function(){Online.doMessage('StoreDeal');}, 750)"
  ];
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
};
