let doConcede = (state: TopLevel.state) => {
  // make sure doMessage is called in sidebar component
  let () = [%raw "window.isLastActionSync = false"];
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
  //Js.log(totalValueCardsNS);
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
  // use arrbitrarily North and East (could be equally South and West)
  let winningPocAsString =
    totalValueCardsNS > totalValueCardsEW ? "North" : "East";
  let qtyTricksToGiveWinningPartnership = () => {
    let lifecycleHandCardsArray =
      Belt.Array.keep(state.pack, x => {x.lifecycle === Hand});
    Belt.Array.length(lifecycleHandCardsArray) / 4;
  };
  // move the selected cards from Hand direct to Trick (skipping the Discard phase)
  let myPack =
    Array.map(
      (card: Shuffle.card) => {
        card.lifecycle === Hand
          ? {...card, lifecycle: Trick}
          : {
            card;
          }
      },
      state.pack,
    );
  let modifiedState = {
    ...state,
    discardIndex: state.discardIndex + qtyTricksToGiveWinningPartnership() * 4,
    pack: myPack,
  };
  //this returns the computed new state
  EndTrick.getNextStateFromTricksWonAndWinningPartnership(
    modifiedState,
    qtyTricksToGiveWinningPartnership(),
    winningPocAsString,
  );
};

let execute = (state: TopLevel.state) => {
  let bln: bool = [%raw
    "window.confirm('Are you sure you want to concede the remaining tricks?')"
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
