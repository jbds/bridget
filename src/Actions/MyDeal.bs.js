'use strict';

var List = require("bs-platform/lib/js/list.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
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
    /* :: */[
      chicagoScoreSheetRecord,
      /* :: */[
        chicagoScoreSheetRecord,
        /* :: */[
          chicagoScoreSheetRecord,
          /* :: */[
            chicagoScoreSheetRecord,
            /* :: */[
              chicagoScoreSheetRecord,
              /* :: */[
                chicagoScoreSheetRecord,
                /* :: */[
                  chicagoScoreSheetRecord,
                  /* :: */[
                    chicagoScoreSheetRecord,
                    /* :: */[
                      chicagoScoreSheetRecord,
                      /* :: */[
                        chicagoScoreSheetRecord,
                        /* :: */[
                          chicagoScoreSheetRecord,
                          /* :: */[
                            chicagoScoreSheetRecord,
                            /* :: */[
                              chicagoScoreSheetRecord,
                              /* :: */[
                                chicagoScoreSheetRecord,
                                /* :: */[
                                  chicagoScoreSheetRecord,
                                  /* :: */[
                                    chicagoScoreSheetRecord,
                                    /* :: */[
                                      chicagoScoreSheetRecord,
                                      /* :: */[
                                        chicagoScoreSheetRecord,
                                        /* :: */[
                                          chicagoScoreSheetRecord,
                                          /* :: */[
                                            chicagoScoreSheetRecord,
                                            /* :: */[
                                              chicagoScoreSheetRecord,
                                              /* :: */[
                                                chicagoScoreSheetRecord,
                                                /* :: */[
                                                  chicagoScoreSheetRecord,
                                                  state.chicagoScoreSheet
                                                ]
                                              ]
                                            ]
                                          ]
                                        ]
                                      ]
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ]
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]
  ];
  newrecord.bids = /* [] */0;
  newrecord.activePointOfCompass = state.dealer;
  return newrecord;
}

exports.execute = execute;
/*  Not a pure module */
