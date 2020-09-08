let execute = (state: TopLevel.state) => {
  // only triggered on imminent 4 discards - see P5Event.js line 207
  // make sure doMessage is called in sidebar component
  let () = [%raw "window.isLastActionSync = false"];
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
  Js.log("myFourCards:");
  Js.log(myFourCards);
  let myFourCardsAsList = Belt.List.fromArray(myFourCards);
  // just sort the list with Belt!
  let myFourCardsAsListSorted =
    Belt.List.sort(myFourCardsAsList, (a, b) => {
      b.noTrumpValue - a.noTrumpValue
    });
  let optionWinningCard = Belt.List.head(myFourCardsAsListSorted);
  //Js.log("optionWinningCard");
  //Js.log(optionWinningCard);
  let winningCardFileName =
    switch (optionWinningCard) {
    | None => ""
    | Some(x) => x.fileName
    };
  Js.log("winningCard:");
  Js.log(winningCardFileName);
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
  let totalTricksNorthSouthIncrement =
    winningDiscardPoc === "North" || winningDiscardPoc === "South" ? 1 : 0;

  let totalTricksWestEastIncrement =
    winningDiscardPoc === "West" || winningDiscardPoc === "East" ? 1 : 0;

  Js.log("totalTricksNorthSouthIncrement:");
  Js.log(totalTricksNorthSouthIncrement);
  Js.log("totalTricksWestEastIncrement:");
  Js.log(totalTricksWestEastIncrement);
  // prepare for the score sheet update - we only want to update the head of the list
  let chicagoScoreSheetHead = Belt.List.headExn(state.chicagoScoreSheet);
  let chicagoScoreSheetTail: Chicago.chicagoScoreSheet =
    Belt.List.tailExn(state.chicagoScoreSheet);
  let myChicagoScoreSheetRecord = {
    ...chicagoScoreSheetHead,
    totalTricksNorthSouth:
      switch (chicagoScoreSheetHead.totalTricksNorthSouth) {
      | None => None
      | Some(n) => Some(n + totalTricksNorthSouthIncrement)
      },
    totalTricksWestEast:
      switch (chicagoScoreSheetHead.totalTricksWestEast) {
      | None => None
      | Some(n) => Some(n + totalTricksWestEastIncrement)
      },
  };
  // now we must check for end of round/deal using discardIndex
  let myChicagoScoreSheetRecordWithOptionalScore =
    if (state.discardIndex === 51) {
      let myScoreLookupDenomination: Chicago.denomination =
        if (scoreSheetRecord.contractSuit === Some("Clubs")
            || scoreSheetRecord.contractSuit === Some("Diamonds")) {
          Minor;
        } else if (scoreSheetRecord.contractSuit === Some("Hearts")
                   || scoreSheetRecord.contractSuit === Some("Spades")) {
          Major;
        } else if (scoreSheetRecord.contractSuit === Some("NoTrumps")) {
          NoTrumps;
        } else {
          NoTrumps; // should be unreachable code
        };
      let isVulnerable =
        if (scoreSheetRecord.vulnerable === "None") {
          false;
        } else if ((
                     scoreSheetRecord.vulnerable === "N"
                     || scoreSheetRecord.vulnerable === "S"
                   )
                   && (
                     scoreSheetRecord.contractDeclarer === Some("North")
                     || scoreSheetRecord.contractDeclarer === Some("South")
                   )) {
          true;
        } else if ((
                     scoreSheetRecord.vulnerable === "W"
                     || scoreSheetRecord.vulnerable === "E"
                   )
                   && (
                     scoreSheetRecord.contractDeclarer === Some("West")
                     || scoreSheetRecord.contractDeclarer === Some("East")
                   )) {
          true;
        } else if (scoreSheetRecord.vulnerable === "All") {
          true;
        } else {
          false; // catchall should never happen
        };
      let scoreLookup =
        Chicago.getScore(
          ~level=Shuffle.optionIntAsInt(scoreSheetRecord.contractLevel),
          ~denomination=myScoreLookupDenomination,
          ~tricksTotal=
            scoreSheetRecord.contractDeclarer === Some("North")
            || scoreSheetRecord.contractDeclarer === Some("South")
              ? switch (chicagoScoreSheetHead.totalTricksNorthSouth) {
                | None => (-1)
                | Some(n) => n + totalTricksNorthSouthIncrement
                }
              : (
                switch (chicagoScoreSheetHead.totalTricksWestEast) {
                | None => (-1)
                | Some(n) => n + totalTricksWestEastIncrement
                }
              ),
          ~isVulnerable,
          ~isDoubled=scoreSheetRecord.isDoubled, //false, // TO DO
          ~isRedoubled=scoreSheetRecord.isRedoubled //false // TO DO
        );
      // some redundancy here, possibility of a bug
      // state.declarer and contract.declarer SHOULD always be the same
      // put -ve scores to opposition
      scoreLookup >= 0
        ? {
          ...myChicagoScoreSheetRecord,
          scoreNorthSouth:
            state.declarer === Some("North")
            || state.declarer === Some("South")
              ? Some(scoreLookup) : None,
          scoreWestEast:
            state.declarer === Some("West")
            || state.declarer === Some("East")
              ? Some(scoreLookup) : None,
        }
        : {
          ...myChicagoScoreSheetRecord,
          scoreNorthSouth:
            state.declarer === Some("West")
            || state.declarer === Some("East")
              ? Some(- scoreLookup) : None,
          scoreWestEast:
            state.declarer === Some("North")
            || state.declarer === Some("South")
              ? Some(- scoreLookup) : None,
        };
    } else {
      myChicagoScoreSheetRecord;
    };
  //Js.log("discardIndex:");
  //Js.log(state.discardIndex);
  // move all (should be 4 always) discarded cards into lifecycle Trick
  let myPack =
    Array.map(
      (card: Shuffle.card) => {
        card.lifecycle === Discard
          ? {...card, lifecycle: Trick}
          : {
            card;
          }
      },
      state.pack,
    );
  // only clear discard pile every 4 discards
  // actually this action is now only called once every 4 discards
  // so we do not need that constraint
  // conditional end-of-round update to poc signified by discardIndex = 51
  let endOfDealNextPoc = Shuffle.getNextPointOfCompass(state.dealer);
  // conditional end-of-round subtotal occurs on discardIndex = 51 and Vuln = "All"
  // helpers to get subtotals
  let optionLast4ScoreSheetRecordsMinusLatest =
    chicagoScoreSheetTail->Belt.List.take(3);
  let last4ScoreSheetRecordsMinusLatest =
    switch (optionLast4ScoreSheetRecordsMinusLatest) {
    | None => [] //should never happen
    | Some(arr) => arr
    };
  let last4ScoreSheetRecords = [
    myChicagoScoreSheetRecordWithOptionalScore,
    ...last4ScoreSheetRecordsMinusLatest,
  ];
  Js.log("last4ScoreSheetRecords");
  Js.log(last4ScoreSheetRecords);
  // could not get this to work!
  //let scoreNorthSouth = last4ScoreSheetRecords -> Belt.List.reduce(Some(0), (scoreNorthSouth) => Some(0) + scoreNorthSouth);
  // so use alternative std library
  let scoreNorthSouth =
    List.fold_left(
      (acc, x: Chicago.chicagoScoreSheetRecord) => {
        acc
        + (
          switch (x.scoreNorthSouth) {
          | None => 0
          | Some(n) => n
          }
        )
      },
      0,
      last4ScoreSheetRecords,
    );
  // Js.log("scoreNorthSouth");
  // Js.log(scoreNorthSouth);
  let scoreWestEast =
    List.fold_left(
      (acc, x: Chicago.chicagoScoreSheetRecord) => {
        acc
        + (
          switch (x.scoreWestEast) {
          | None => 0
          | Some(n) => n
          }
        )
      },
      0,
      last4ScoreSheetRecords,
    );
  // Js.log("scoreWestEast");
  // Js.log(scoreWestEast);
  let chicagoScoreSheetRecordSubTotal: Chicago.chicagoScoreSheetRecord = {
    vulnerable: "",
    contractLevel: None,
    contractSuit: None,
    contractDeclarer: None,
    isDoubled: false,
    isRedoubled: false,
    totalTricksNorthSouth: None,
    scoreNorthSouth: Some(scoreNorthSouth),
    totalTricksWestEast: None,
    scoreWestEast: Some(scoreWestEast),
  };
  {
    ...state,
    activePointOfCompass:
      state.discardIndex !== 51
        ? Some(winningDiscardPoc) : Some(endOfDealNextPoc),
    chicagoScoreSheet:
      state.discardIndex !== 51 || scoreSheetRecord.vulnerable !== "All"
        ? [
          myChicagoScoreSheetRecordWithOptionalScore,
          ...chicagoScoreSheetTail,
        ]
        : [
          chicagoScoreSheetRecordSubTotal,
          myChicagoScoreSheetRecordWithOptionalScore,
          ...chicagoScoreSheetTail,
        ],
    dealer: state.discardIndex !== 51 ? state.dealer : Some(endOfDealNextPoc),
    declarer: state.discardIndex !== 51 ? state.declarer : None,
    isReviewDealVisible: state.discardIndex !== 51 ? false : true,
    //pack: (state.discardIndex mod 4 ) === 3 ? myPack : state.pack,
    pack: myPack,
    lastAction: "End of Trick",
    randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
  };
};
