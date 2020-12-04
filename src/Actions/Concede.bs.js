'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");

function doConcede(state) {
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
  var remainingCardsNS = Belt_Array.keep(myAdjustedPackValue, (function (x) {
          if (x.lifecycle === /* Hand */1) {
            if (x.shuffleIndex >= 0 && x.shuffleIndex <= 12) {
              return true;
            } else if (x.shuffleIndex >= 26) {
              return x.shuffleIndex <= 38;
            } else {
              return false;
            }
          } else {
            return false;
          }
        }));
  var valueCardsArrayNS = Belt_Array.map(remainingCardsNS, (function (x) {
          return x.noTrumpValue;
        }));
  var totalValueCardsNS = Belt_Array.reduce(valueCardsArrayNS, 0, (function (a, b) {
          return a + b | 0;
        }));
  console.log(totalValueCardsNS);
  var remainingCardsEW = Belt_Array.keep(myAdjustedPackValue, (function (x) {
          if (x.lifecycle === /* Hand */1) {
            if (x.shuffleIndex >= 13 && x.shuffleIndex <= 25) {
              return true;
            } else if (x.shuffleIndex >= 39) {
              return x.shuffleIndex <= 51;
            } else {
              return false;
            }
          } else {
            return false;
          }
        }));
  var valueCardsArrayEW = Belt_Array.map(remainingCardsEW, (function (x) {
          return x.noTrumpValue;
        }));
  var totalValueCardsEW = Belt_Array.reduce(valueCardsArrayEW, 0, (function (a, b) {
          return a + b | 0;
        }));
  console.log(totalValueCardsEW);
  var winningPartnershipAsString = totalValueCardsNS > totalValueCardsEW ? "NS" : "EW";
  console.log(winningPartnershipAsString);
  var qtyTricksToGiveWinningPartnership = function (param) {
    var lifecycleHandCardsArray = Belt_Array.keep(state.pack, (function (x) {
            return x.lifecycle === /* Hand */1;
          }));
    return lifecycleHandCardsArray.length / 4 | 0;
  };
  console.log("qtyTricksToGiveWinningPartnership");
  console.log(qtyTricksToGiveWinningPartnership(undefined));
  return state;
}

function execute(state) {
  var bln = (window.confirm('Are you sure you want to assign the remaining tricks to the winning partnership?'));
  if (bln) {
    console.log("do concede action");
    return doConcede(state);
  } else {
    console.log("abort concede action");
    return state;
  }
}

exports.doConcede = doConcede;
exports.execute = execute;
/* Shuffle-ReasonReactExamples Not a pure module */
