'use strict';

var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");

var Online = require('../Online.bs');
;

function execute(state) {
  ((window.isLastActionSync = false));
  ((setTimeout(function(){Online.doMessage('StoreDeal');}, 750)));
  return {
          activePointOfCompass: state.dealer,
          bids: /* [] */0,
          chicagoScoreSheet: state.chicagoScoreSheet,
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
