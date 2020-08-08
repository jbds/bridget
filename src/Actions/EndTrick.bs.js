'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Chicago$ReasonReactExamples = require("../Chicago.bs.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");

function execute(state) {
  ((window.isLastActionSync = false));
  var scoreSheetRecord = List.hd(state.chicagoScoreSheet);
  var contractSuit = scoreSheetRecord.contractSuit;
  var myAdjustedPackValue = $$Array.map((function (card) {
          if (Shuffle$ReasonReactExamples.getSuitAsOptionString(card.suit) === contractSuit) {
            return {
                    noTrumpValue: card.noTrumpValue + 52 | 0,
                    handOrder: card.handOrder,
                    shuffleIndex: card.shuffleIndex,
                    rank: card.rank,
                    suit: card.suit,
                    fileName: card.fileName,
                    lifecycle: card.lifecycle
                  };
          } else {
            return card;
          }
        }), state.pack);
  var myFourCards = Belt_Array.keep(myAdjustedPackValue, (function (x) {
          if (x.lifecycle === /* Discard */2) {
            if (x.suit === state.discardSuit) {
              return true;
            } else {
              return Shuffle$ReasonReactExamples.getSuitAsOptionString(x.suit) === contractSuit;
            }
          } else {
            return false;
          }
        }));
  console.log("myFourCards:");
  console.log(myFourCards);
  var myFourCardsAsList = Belt_List.fromArray(myFourCards);
  var myFourCardsAsListSorted = Belt_List.sort(myFourCardsAsList, (function (a, b) {
          return b.noTrumpValue - a.noTrumpValue | 0;
        }));
  var optionWinningCard = Belt_List.head(myFourCardsAsListSorted);
  var winningCardFileName = optionWinningCard !== undefined ? optionWinningCard.fileName : "";
  console.log("winningCard:");
  console.log(winningCardFileName);
  var winningCardShuffleIndex = optionWinningCard !== undefined ? optionWinningCard.shuffleIndex : -1;
  var winningDiscardPoc = winningCardShuffleIndex === -1 ? "Error" : (
      winningCardShuffleIndex < 13 ? "North" : (
          winningCardShuffleIndex < 26 ? "East" : (
              winningCardShuffleIndex < 39 ? "South" : "West"
            )
        )
    );
  var totalTricksNorthSouthIncrement = winningDiscardPoc === "North" || winningDiscardPoc === "South" ? 1 : 0;
  var totalTricksWestEastIncrement = winningDiscardPoc === "West" || winningDiscardPoc === "East" ? 1 : 0;
  console.log("totalTricksNorthSouthIncrement:");
  console.log(totalTricksNorthSouthIncrement);
  console.log("totalTricksWestEastIncrement:");
  console.log(totalTricksWestEastIncrement);
  var chicagoScoreSheetHead = Belt_List.headExn(state.chicagoScoreSheet);
  var chicagoScoreSheetTail = Belt_List.tailExn(state.chicagoScoreSheet);
  var n = chicagoScoreSheetHead.totalTricksNorthSouth;
  var n$1 = chicagoScoreSheetHead.totalTricksWestEast;
  var myChicagoScoreSheetRecord_vulnerable = chicagoScoreSheetHead.vulnerable;
  var myChicagoScoreSheetRecord_contractLevel = chicagoScoreSheetHead.contractLevel;
  var myChicagoScoreSheetRecord_contractSuit = chicagoScoreSheetHead.contractSuit;
  var myChicagoScoreSheetRecord_contractDeclarer = chicagoScoreSheetHead.contractDeclarer;
  var myChicagoScoreSheetRecord_isDoubled = chicagoScoreSheetHead.isDoubled;
  var myChicagoScoreSheetRecord_isRedoubled = chicagoScoreSheetHead.isRedoubled;
  var myChicagoScoreSheetRecord_totalTricksNorthSouth = n !== undefined ? n + totalTricksNorthSouthIncrement | 0 : undefined;
  var myChicagoScoreSheetRecord_scoreNorthSouth = chicagoScoreSheetHead.scoreNorthSouth;
  var myChicagoScoreSheetRecord_totalTricksWestEast = n$1 !== undefined ? n$1 + totalTricksWestEastIncrement | 0 : undefined;
  var myChicagoScoreSheetRecord_scoreWestEast = chicagoScoreSheetHead.scoreWestEast;
  var myChicagoScoreSheetRecord = {
    vulnerable: myChicagoScoreSheetRecord_vulnerable,
    contractLevel: myChicagoScoreSheetRecord_contractLevel,
    contractSuit: myChicagoScoreSheetRecord_contractSuit,
    contractDeclarer: myChicagoScoreSheetRecord_contractDeclarer,
    isDoubled: myChicagoScoreSheetRecord_isDoubled,
    isRedoubled: myChicagoScoreSheetRecord_isRedoubled,
    totalTricksNorthSouth: myChicagoScoreSheetRecord_totalTricksNorthSouth,
    scoreNorthSouth: myChicagoScoreSheetRecord_scoreNorthSouth,
    totalTricksWestEast: myChicagoScoreSheetRecord_totalTricksWestEast,
    scoreWestEast: myChicagoScoreSheetRecord_scoreWestEast
  };
  var myChicagoScoreSheetRecordWithOptionalScore;
  if (state.discardIndex === 51) {
    var myScoreLookupDenomination = scoreSheetRecord.contractSuit === "Clubs" || scoreSheetRecord.contractSuit === "Diamonds" ? /* Minor */0 : (
        scoreSheetRecord.contractSuit === "Hearts" || scoreSheetRecord.contractSuit === "Spades" ? /* Major */1 : (scoreSheetRecord.contractSuit === "NoTrumps", /* NoTrumps */2)
      );
    var isVulnerable = scoreSheetRecord.vulnerable === "None" ? false : (
        (scoreSheetRecord.vulnerable === "N" || scoreSheetRecord.vulnerable === "S") && (scoreSheetRecord.contractDeclarer === "North" || scoreSheetRecord.contractDeclarer === "South") || (scoreSheetRecord.vulnerable === "W" || scoreSheetRecord.vulnerable === "E") && (scoreSheetRecord.contractDeclarer === "West" || scoreSheetRecord.contractDeclarer === "East") ? true : scoreSheetRecord.vulnerable === "All"
      );
    var tmp;
    if (scoreSheetRecord.contractDeclarer === "North" || scoreSheetRecord.contractDeclarer === "South") {
      var n$2 = chicagoScoreSheetHead.totalTricksNorthSouth;
      tmp = n$2 !== undefined ? n$2 + totalTricksNorthSouthIncrement | 0 : -1;
    } else {
      var n$3 = chicagoScoreSheetHead.totalTricksWestEast;
      tmp = n$3 !== undefined ? n$3 + totalTricksWestEastIncrement | 0 : -1;
    }
    var scoreLookup = Chicago$ReasonReactExamples.getScore(Shuffle$ReasonReactExamples.optionIntAsInt(scoreSheetRecord.contractLevel), myScoreLookupDenomination, tmp, isVulnerable, scoreSheetRecord.isDoubled, scoreSheetRecord.isRedoubled);
    myChicagoScoreSheetRecordWithOptionalScore = {
      vulnerable: myChicagoScoreSheetRecord_vulnerable,
      contractLevel: myChicagoScoreSheetRecord_contractLevel,
      contractSuit: myChicagoScoreSheetRecord_contractSuit,
      contractDeclarer: myChicagoScoreSheetRecord_contractDeclarer,
      isDoubled: myChicagoScoreSheetRecord_isDoubled,
      isRedoubled: myChicagoScoreSheetRecord_isRedoubled,
      totalTricksNorthSouth: myChicagoScoreSheetRecord_totalTricksNorthSouth,
      scoreNorthSouth: state.declarer === "North" || state.declarer === "South" ? scoreLookup : undefined,
      totalTricksWestEast: myChicagoScoreSheetRecord_totalTricksWestEast,
      scoreWestEast: state.declarer === "West" || state.declarer === "East" ? scoreLookup : undefined
    };
  } else {
    myChicagoScoreSheetRecordWithOptionalScore = myChicagoScoreSheetRecord;
  }
  var myPack = $$Array.map((function (card) {
          if (card.lifecycle === /* Discard */2) {
            return {
                    noTrumpValue: card.noTrumpValue,
                    handOrder: card.handOrder,
                    shuffleIndex: card.shuffleIndex,
                    rank: card.rank,
                    suit: card.suit,
                    fileName: card.fileName,
                    lifecycle: /* Trick */3
                  };
          } else {
            return card;
          }
        }), state.pack);
  var endOfDealNextPoc = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.dealer);
  var optionLast4ScoreSheetRecordsMinusLatest = Belt_List.take(chicagoScoreSheetTail, 3);
  var last4ScoreSheetRecordsMinusLatest = optionLast4ScoreSheetRecordsMinusLatest !== undefined ? optionLast4ScoreSheetRecordsMinusLatest : /* [] */0;
  var last4ScoreSheetRecords = /* :: */[
    myChicagoScoreSheetRecordWithOptionalScore,
    last4ScoreSheetRecordsMinusLatest
  ];
  console.log("last4ScoreSheetRecords");
  console.log(last4ScoreSheetRecords);
  var scoreNorthSouth = List.fold_left((function (acc, x) {
          var n = x.scoreNorthSouth;
          return acc + (
                  n !== undefined ? n : 0
                ) | 0;
        }), 0, last4ScoreSheetRecords);
  var scoreWestEast = List.fold_left((function (acc, x) {
          var n = x.scoreWestEast;
          return acc + (
                  n !== undefined ? n : 0
                ) | 0;
        }), 0, last4ScoreSheetRecords);
  var chicagoScoreSheetRecordSubTotal_scoreNorthSouth = scoreNorthSouth;
  var chicagoScoreSheetRecordSubTotal_scoreWestEast = scoreWestEast;
  var chicagoScoreSheetRecordSubTotal = {
    vulnerable: "",
    contractLevel: undefined,
    contractSuit: undefined,
    contractDeclarer: undefined,
    isDoubled: false,
    isRedoubled: false,
    totalTricksNorthSouth: undefined,
    scoreNorthSouth: chicagoScoreSheetRecordSubTotal_scoreNorthSouth,
    totalTricksWestEast: undefined,
    scoreWestEast: chicagoScoreSheetRecordSubTotal_scoreWestEast
  };
  return {
          activePointOfCompass: state.discardIndex !== 51 ? winningDiscardPoc : endOfDealNextPoc,
          bids: state.bids,
          chicagoScoreSheet: state.discardIndex !== 51 || scoreSheetRecord.vulnerable !== "All" ? /* :: */[
              myChicagoScoreSheetRecordWithOptionalScore,
              chicagoScoreSheetTail
            ] : /* :: */[
              chicagoScoreSheetRecordSubTotal,
              /* :: */[
                myChicagoScoreSheetRecordWithOptionalScore,
                chicagoScoreSheetTail
              ]
            ],
          dealer: state.discardIndex !== 51 ? state.dealer : endOfDealNextPoc,
          dealIndex: state.dealIndex,
          declarer: state.discardIndex !== 51 ? state.declarer : undefined,
          discardIndex: state.discardIndex,
          discardSuit: state.discardSuit,
          handVisible: state.handVisible,
          isBiddingCycle: state.isBiddingCycle,
          isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
          isDummyVisible: state.isDummyVisible,
          isRebootVisible: state.isRebootVisible,
          isReviewDealVisible: state.discardIndex === 51,
          lastAction: "End of Trick",
          pack: myPack,
          pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
          randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
        };
}

exports.execute = execute;
/* Shuffle-ReasonReactExamples Not a pure module */
