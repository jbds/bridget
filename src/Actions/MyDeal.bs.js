'use strict';

var List = require("bs-platform/lib/js/list.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");

var Online = require('../Online.bs');
;

function executeWithShuffle(state) {
  ((window.isLastActionSync = false));
  ((setTimeout(function(){Online.doMessage('StoreDeal');}, 750)));
  var chicagoScoreSheetAdjusted;
  if (List.length(state.chicagoScoreSheet) > 0) {
    var chicagoScoreSheetHead = List.hd(state.chicagoScoreSheet);
    chicagoScoreSheetAdjusted = Caml_obj.caml_equal(chicagoScoreSheetHead.scoreNorthSouth, 0) || Caml_obj.caml_equal(chicagoScoreSheetHead.scoreWestEast, 0) ? List.tl(state.chicagoScoreSheet) : state.chicagoScoreSheet;
  } else {
    chicagoScoreSheetAdjusted = state.chicagoScoreSheet;
  }
  var match = List.length(chicagoScoreSheetAdjusted) % 5;
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
  var newrecord = Caml_obj.caml_obj_dup(state);
  newrecord.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
  newrecord.pack = Shuffle$ReasonReactExamples.getShuffledPack(undefined);
  newrecord.lastAction = "Deal";
  newrecord.isReviewDealVisible = false;
  newrecord.isDummyVisible = false;
  newrecord.isBiddingHideDenominationButtons = true;
  newrecord.isBiddingCycle = true;
  newrecord.handVisible = Shuffle$ReasonReactExamples.initialHandVisible;
  newrecord.discardIndex = -1;
  newrecord.declarer = undefined;
  newrecord.chicagoScoreSheet = /* :: */[
    chicagoScoreSheetRecord,
    chicagoScoreSheetAdjusted
  ];
  newrecord.bids = /* [] */0;
  newrecord.activePointOfCompass = state.dealer;
  return newrecord;
}

function executeWithoutShuffle(state) {
  ((window.isLastActionSync = false));
  var chicagoScoreSheetRecord_vulnerable = List.hd(state.chicagoScoreSheet).vulnerable === "" ? List.hd(List.tl(state.chicagoScoreSheet)).vulnerable : List.hd(state.chicagoScoreSheet).vulnerable;
  var chicagoScoreSheetRecord_scoreNorthSouth = 0;
  var chicagoScoreSheetRecord_scoreWestEast = 0;
  var chicagoScoreSheetRecord = {
    vulnerable: chicagoScoreSheetRecord_vulnerable,
    contractLevel: undefined,
    contractSuit: undefined,
    contractDeclarer: undefined,
    isDoubled: false,
    isRedoubled: false,
    totalTricksNorthSouth: undefined,
    scoreNorthSouth: chicagoScoreSheetRecord_scoreNorthSouth,
    totalTricksWestEast: undefined,
    scoreWestEast: chicagoScoreSheetRecord_scoreWestEast
  };
  var lastDealer = Shuffle$ReasonReactExamples.getLastActivePointOfCompass(state.dealer);
  var newrecord = Caml_obj.caml_obj_dup(state);
  newrecord.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
  newrecord.lastAction = "Replay";
  newrecord.isReviewDealVisible = false;
  newrecord.isDummyVisible = false;
  newrecord.isBiddingHideDenominationButtons = true;
  newrecord.isBiddingCycle = true;
  newrecord.handVisible = Shuffle$ReasonReactExamples.initialHandVisible;
  newrecord.discardIndex = -1;
  newrecord.declarer = undefined;
  newrecord.chicagoScoreSheet = /* :: */[
    chicagoScoreSheetRecord,
    state.chicagoScoreSheet
  ];
  newrecord.bids = /* [] */0;
  newrecord.activePointOfCompass = lastDealer;
  return newrecord;
}

function execute(state, isMyDeal) {
  if (isMyDeal === true) {
    return executeWithShuffle(state);
  } else {
    return executeWithoutShuffle(state);
  }
}

exports.executeWithShuffle = executeWithShuffle;
exports.executeWithoutShuffle = executeWithoutShuffle;
exports.execute = execute;
/*  Not a pure module */
