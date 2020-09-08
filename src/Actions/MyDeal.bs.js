'use strict';

var List = require("bs-platform/lib/js/list.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");

var Online = require('../Online.bs');
;

function execute(state) {
  ((window.isLastActionSync = false));
  ((setTimeout(function(){Online.doMessage('StoreDeal');}, 750)));
  var match = List.length(state.chicagoScoreSheet) % 5;
  var vulnerable;
  if (match > 2 || match < 0) {
    vulnerable = match !== 3 ? "Error" : "All";
  } else if (match !== 0) {
    var match$1 = state.dealer;
    if (match$1 !== undefined) {
      switch (match$1) {
        case "East" :
            vulnerable = "EW";
            break;
        case "North" :
            vulnerable = "NS";
            break;
        case "South" :
            vulnerable = "SN";
            break;
        case "West" :
            vulnerable = "WE";
            break;
        default:
          vulnerable = "Err";
      }
    } else {
      vulnerable = "Err";
    }
  } else {
    vulnerable = "None";
  }
  var chicagoScoreSheetRecord = {
    vulnerable: vulnerable,
    contractLevel: undefined,
    contractSuit: undefined,
    contractDeclarer: undefined,
    isDoubled: false,
    isRedoubled: false,
    totalTricksNorthSouth: undefined,
    scoreNorthSouth: undefined,
    totalTricksWestEast: undefined,
    scoreWestEast: undefined
  };
  return {
          activePointOfCompass: state.dealer,
          bids: /* [] */0,
          chicagoScoreSheet: /* :: */[
            chicagoScoreSheetRecord,
            state.chicagoScoreSheet
          ],
          dealer: state.dealer,
          dealIndex: state.dealIndex,
          declarer: undefined,
          discardIndex: -1,
          discardSuit: state.discardSuit,
          handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
          isBiddingCycle: true,
          isBiddingHideDenominationButtons: true,
          isDummyVisible: false,
          isRebootVisible: state.isRebootVisible,
          isReviewDealVisible: false,
          lastAction: "Deal",
          pack: Shuffle$ReasonReactExamples.getShuffledPack(undefined),
          pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
          randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
        };
}

exports.execute = execute;
/*  Not a pure module */
