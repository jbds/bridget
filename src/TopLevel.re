// avoid circular dependencies by making this file the 'top'
type state = {
  activePointOfCompass: option(string),
  bids: Chicago.bids,
  chicagoScoreSheet: list(Chicago.chicagoScoreSheetRecord),
  dealer: option(string),
  dealIndex: int,
  declarer: option(string),
  discardIndex: int,
  discardSuit: option(Shuffle.suit),
  handVisible: Shuffle.handVisible,
  isBiddingCycle: bool,
  isBiddingHideDenominationButtons: bool,
  isDummyVisible: bool,
  isRebootVisible: bool,
  isReviewDealVisible: bool,
  lastAction: string,
  pack: Shuffle.pack,
  pointOfCompassAndPlayers: array(Shuffle.pointOfCompassAndPlayer),
  randomInt: int,
};

