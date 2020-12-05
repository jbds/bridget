'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

function getWinningDiscardPoc(state) {
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
  var myFourCardsAsList = Belt_List.fromArray(myFourCards);
  var myFourCardsAsListSorted = Belt_List.sort(myFourCardsAsList, (function (a, b) {
          return b.noTrumpValue - a.noTrumpValue | 0;
        }));
  var optionWinningCard = Belt_List.head(myFourCardsAsListSorted);
  var winningCardShuffleIndex = optionWinningCard !== undefined ? optionWinningCard.shuffleIndex : -1;
  if (winningCardShuffleIndex === -1) {
    return "Error";
  } else if (winningCardShuffleIndex < 13) {
    return "North";
  } else if (winningCardShuffleIndex < 26) {
    return "East";
  } else if (winningCardShuffleIndex < 39) {
    return "South";
  } else {
    return "West";
  }
}

function updateScoreTable(qtyTrickIncrementNS, qtyTrickIncrementEW, state) {
  return state;
}

exports.getWinningDiscardPoc = getWinningDiscardPoc;
exports.updateScoreTable = updateScoreTable;
/* Shuffle-ReasonReactExamples Not a pure module */
