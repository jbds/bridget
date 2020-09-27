// avoid circular dependencies by making this file the 'top'
type state = {
  activePointOfCompass: option(string),
  bids: Chicago.bids,
  chicagoScoreSheet: list(Chicago.chicagoScoreSheetRecord),
  dealer: option(string),
  dealIndex: int,
  declarer: option(string),
  discardIndex: int,
  discardPointOfCompass: option(string),
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
  transition: Shuffle.transition,
};

// put utilities in here too?
// we are using the Shuffle module as a general utility module here, nothing to do with Shuffle!
let getWinningDiscardPoc = (state: state) => {
  // based on same code in EndTrick.re
  // check contract suit
  let scoreSheetRecord = List.hd(state.chicagoScoreSheet);
  let contractSuit = scoreSheetRecord.contractSuit;
  // get adjusted value of the cards
  let myAdjustedPackValue =
    Array.map(
      (card: Shuffle.card) => {
        Shuffle.getSuitAsOptionString(card.suit) === contractSuit
          ? {...card, noTrumpValue: card.noTrumpValue + 52}
          : {
            card;
          }
      },
      state.pack,
    );
  //Js.log("myAdjustedPackValue:");
  //Js.log(myAdjustedPackValue);
  // filter by lifecycle and also lead discard suit / trump suit
  let myFourCards =
    Belt.Array.keep(myAdjustedPackValue, x => {
      x.lifecycle === Discard
      && (
        Some(x.suit) === state.discardSuit
        || Shuffle.getSuitAsOptionString(x.suit) === contractSuit
      )
    });
  //Js.log("myFourCards:");
  //Js.log(myFourCards);
  let myFourCardsAsList = Belt.List.fromArray(myFourCards);
  // just sort the list with Belt!
  let myFourCardsAsListSorted =
    Belt.List.sort(myFourCardsAsList, (a, b) => {
      b.noTrumpValue - a.noTrumpValue
    });
  let optionWinningCard = Belt.List.head(myFourCardsAsListSorted);
  //Js.log("optionWinningCard");
  //Js.log(optionWinningCard);
  // let winningCardFileName =
  //   switch (optionWinningCard) {
  //   | None => ""
  //   | Some(x) => x.fileName
  //   };
  // Js.log("winningCard:");
  // Js.log(winningCardFileName);
  let winningCardShuffleIndex =
    switch (optionWinningCard) {
    | None => (-1)
    | Some(x) => x.shuffleIndex
    };
  // Js.log("winningCardShuffleIndex:");
  // Js.log(winningCardShuffleIndex);
  let winningDiscardPoc =
    if (winningCardShuffleIndex === (-1)) {
      "Error";
    } else if (winningCardShuffleIndex < 13) {
      "North";
    } else if (winningCardShuffleIndex < 26) {
      "East";
    } else if (winningCardShuffleIndex < 39) {
      "South";
    } else {
      "West";
    };
  //Js.log("winningDiscardPoc:");
  //Js.log(winningDiscardPoc);
  winningDiscardPoc;
};
