'use strict';

var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");

function execute(state) {
  ((setTimeout(function(){Online.doMessage('StoreDeal');}, 750)));
  var newrecord = Caml_obj.caml_obj_dup(state);
  newrecord.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
  newrecord.pack = Shuffle$ReasonReactExamples.getShuffledPack(undefined);
  newrecord.lastAction = "4 Passes - so fresh cards dealt";
  newrecord.isDummyVisible = false;
  newrecord.isBiddingHideDenominationButtons = true;
  newrecord.isBiddingCycle = true;
  newrecord.discardIndex = -1;
  newrecord.declarer = undefined;
  newrecord.bids = /* [] */0;
  newrecord.activePointOfCompass = state.dealer;
  return newrecord;
}

exports.execute = execute;
/* Shuffle-ReasonReactExamples Not a pure module */
