let doConcede = (state: TopLevel.state) => {
  // value adjust for trumps - copied from EndTrick
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

  let remainingCardsNS =
    Belt.Array.keep(myAdjustedPackValue, x => {
      x.lifecycle === Hand
      && (
        x.shuffleIndex >= 0
        && x.shuffleIndex <= 12
        || x.shuffleIndex >= 26
        && x.shuffleIndex <= 38
      )
    });
  //Js.log(remainingCardsNS);
  let valueCardsArrayNS =
    Belt.Array.map(remainingCardsNS, x => x.noTrumpValue);
  //Js.log(valueCardsArrayNS);
  let totalValueCardsNS =
    Belt.Array.reduce(valueCardsArrayNS, 0, (a, b) => a + b);
  Js.log(totalValueCardsNS);
  let remainingCardsEW =
    Belt.Array.keep(myAdjustedPackValue, x => {
      x.lifecycle === Hand
      && (
        x.shuffleIndex >= 13
        && x.shuffleIndex <= 25
        || x.shuffleIndex >= 39
        && x.shuffleIndex <= 51
      )
    });
  let valueCardsArrayEW =
    Belt.Array.map(remainingCardsEW, x => x.noTrumpValue);
  let totalValueCardsEW =
    Belt.Array.reduce(valueCardsArrayEW, 0, (a, b) => a + b);
  Js.log(totalValueCardsEW);
  let winningPartnershipAsString =
    totalValueCardsNS > totalValueCardsEW ? "NS" : "EW";
  Js.log(winningPartnershipAsString);
  state;
};

let execute = (state: TopLevel.state) => {
  let lifecycleHandCardsArray =
    Belt.Array.keep(state.pack, x => {x.lifecycle === Hand});
  Js.log("lifecycleHandCardsArray length");
  Js.log(Belt.Array.length(lifecycleHandCardsArray));
  let isDivFour = Belt.Array.length(lifecycleHandCardsArray) mod 4 == 0;
  Js.log("isDivFour");
  Js.log(isDivFour);

  let bln: bool = [%raw
    "window.confirm('Are you sure you want to assign the remaining tricks to the winning partnership?')"
  ];
  let returnedState =
    bln
      ? {
        Js.log("do concede action");
        doConcede(state);
      }
      : {
        Js.log("abort concede action");
        state;
      };
  returnedState;
};
