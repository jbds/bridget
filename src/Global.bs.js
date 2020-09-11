'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var MyDeal$ReasonReactExamples = require("./Actions/MyDeal.bs.js");
var Chicago$ReasonReactExamples = require("./Chicago.bs.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");
var EndTrick$ReasonReactExamples = require("./Actions/EndTrick.bs.js");

var Online = require('./Online.bs');
;

var initialState_pack = [];

var initialState_pointOfCompassAndPlayers = [];

var initialState = {
  activePointOfCompass: undefined,
  bids: /* [] */0,
  chicagoScoreSheet: Chicago$ReasonReactExamples.initialChicagoScoreSheet,
  dealer: undefined,
  dealIndex: -1,
  declarer: undefined,
  discardIndex: -1,
  discardSuit: undefined,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  isBiddingCycle: false,
  isBiddingHideDenominationButtons: true,
  isDummyVisible: false,
  isRebootVisible: false,
  isReviewDealVisible: false,
  lastAction: "None (initialState from Client)",
  pack: initialState_pack,
  pointOfCompassAndPlayers: initialState_pointOfCompassAndPlayers,
  randomInt: 1
};

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* Shuffle */0 :
          return MyDeal$ReasonReactExamples.execute(state);
      case /* Discard */1 :
          ((window.isLastActionSync = false));
          var discardFileName = window.discardFileName;
          var cardWrappedInArray = Belt_Array.keep(state.pack, (function (x) {
                  return x.fileName === discardFileName;
                }));
          var cardShuffleIndex = Caml_array.caml_array_get(cardWrappedInArray, 0).shuffleIndex;
          var cardDiscardSuit = Caml_array.caml_array_get(cardWrappedInArray, 0).suit;
          var discardPoc = cardShuffleIndex < 13 ? "North" : (
              cardShuffleIndex < 26 ? "East" : (
                  cardShuffleIndex < 39 ? "South" : "West"
                )
            );
          var pocFollowingDeclarer = Caml_obj.caml_equal(state.declarer, "North") ? "East" : (
              Caml_obj.caml_equal(state.declarer, "East") ? "South" : (
                  Caml_obj.caml_equal(state.declarer, "South") ? "West" : (
                      Caml_obj.caml_equal(state.declarer, "West") ? "North" : ""
                    )
                )
            );
          var myPack = $$Array.map((function (card) {
                  if (card.fileName === discardFileName) {
                    return {
                            noTrumpValue: card.noTrumpValue,
                            handOrder: card.handOrder,
                            shuffleIndex: card.shuffleIndex,
                            rank: card.rank,
                            suit: card.suit,
                            fileName: card.fileName,
                            lifecycle: /* Discard */2
                          };
                  } else {
                    return card;
                  }
                }), state.pack);
          var poc = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.activePointOfCompass);
          return {
                  activePointOfCompass: poc,
                  bids: state.bids,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  discardIndex: state.discardIndex + 1 | 0,
                  discardSuit: (state.discardIndex + 1 | 0) % 4 === 0 ? cardDiscardSuit : state.discardSuit,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                  isDummyVisible: discardPoc === pocFollowingDeclarer ? true : state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
                  isReviewDealVisible: state.isReviewDealVisible,
                  lastAction: "Discard",
                  pack: myPack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Sync */2 :
          ((window.isLastActionSync = true));
          return {
                  activePointOfCompass: undefined,
                  bids: /* [] */0,
                  chicagoScoreSheet: /* [] */0,
                  dealer: undefined,
                  dealIndex: -1,
                  declarer: undefined,
                  discardIndex: -1,
                  discardSuit: undefined,
                  handVisible: {
                    north: false,
                    east: false,
                    south: false,
                    west: false
                  },
                  isBiddingCycle: false,
                  isBiddingHideDenominationButtons: true,
                  isDummyVisible: false,
                  isRebootVisible: false,
                  isReviewDealVisible: false,
                  lastAction: "Logout or Server Down",
                  pack: [],
                  pointOfCompassAndPlayers: [],
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* LoginSync */3 :
          ((window.isLastActionSync = true));
          var cSS = window.gameState.chicagoScoreSheet;
          var dealer = window.gameState.dealer;
          var declarer = window.gameState.declarer;
          var hV = window.gameState.handVisible;
          var pOCAP = window.gameState.pointOfCompassAndPlayers;
          var pack = window.gameState.pack;
          var dealIndex = window.gameState.dealIndex;
          var isBiddingCycle = window.gameState.isBiddingCycle;
          var poc$1 = window.gameState.activePointOfCompass;
          var bids = window.gameState.bids;
          var isBiddingHideDenominationButtons = window.gameState.isBiddingHideDenominationButtons;
          var isRebootVisible = window.gameState.isRebootVisible;
          var isReviewDealVisible = window.gameState.isReviewDealVisible;
          var isDummyVisible = window.gameState.isDummyVisible;
          var discardIndex = window.gameState.discardIndex;
          var discardSuit = window.gameState.discardSuit;
          var lastAction = window.gameState.lastAction;
          return {
                  activePointOfCompass: poc$1,
                  bids: bids,
                  chicagoScoreSheet: cSS,
                  dealer: dealer,
                  dealIndex: dealIndex,
                  declarer: declarer,
                  discardIndex: discardIndex,
                  discardSuit: discardSuit,
                  handVisible: hV,
                  isBiddingCycle: isBiddingCycle,
                  isBiddingHideDenominationButtons: isBiddingHideDenominationButtons,
                  isDummyVisible: isDummyVisible,
                  isRebootVisible: isRebootVisible,
                  isReviewDealVisible: isReviewDealVisible,
                  lastAction: lastAction,
                  pack: pack,
                  pointOfCompassAndPlayers: pOCAP,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Test */4 :
          ((window.isLastActionSync = true));
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  bids: state.bids,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  discardIndex: state.discardIndex,
                  discardSuit: state.discardSuit,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
                  isReviewDealVisible: state.isReviewDealVisible,
                  lastAction: "Test",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* EndTrick */5 :
          return EndTrick$ReasonReactExamples.execute(state);
      
    }
  } else {
    switch (action.tag | 0) {
      case /* AssignPlayer */0 :
          var pOfCAndP = action[0];
          ((window.isLastActionSync = false));
          var myArray1 = $$Array.map((function (pointOfCompassAndPlayer) {
                  if (pointOfCompassAndPlayer.pointOfCompass === pOfCAndP.pointOfCompass && pointOfCompassAndPlayer.pointOfCompass !== "Observer") {
                    return {
                            pointOfCompass: "",
                            player: pointOfCompassAndPlayer.player
                          };
                  } else {
                    return pointOfCompassAndPlayer;
                  }
                }), state.pointOfCompassAndPlayers);
          var myArray2 = $$Array.map((function (pointOfCompassAndPlayer) {
                  if (pointOfCompassAndPlayer.player === pOfCAndP.player) {
                    return {
                            pointOfCompass: pOfCAndP.pointOfCompass,
                            player: pointOfCompassAndPlayer.player
                          };
                  } else {
                    return pointOfCompassAndPlayer;
                  }
                }), myArray1);
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  bids: state.bids,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  discardIndex: state.discardIndex,
                  discardSuit: state.discardSuit,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
                  isReviewDealVisible: state.isReviewDealVisible,
                  lastAction: "AssignPlayer",
                  pack: state.pack,
                  pointOfCompassAndPlayers: myArray2,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* BidAdd */1 :
          ((window.isLastActionSync = false));
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  bids: /* :: */[
                    {
                      contractLevel: action[0],
                      contractSuit: "",
                      contractPointOfCompass: state.activePointOfCompass,
                      isDoubled: false,
                      isRedoubled: false,
                      isPass: false
                    },
                    state.bids
                  ],
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  discardIndex: state.discardIndex,
                  discardSuit: state.discardSuit,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: false,
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
                  isReviewDealVisible: state.isReviewDealVisible,
                  lastAction: "BidAdd",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* BidUpdate */2 :
          ((window.isLastActionSync = false));
          var bids$1 = state.bids;
          var head = List.hd(bids$1);
          var newHead_contractLevel = head.contractLevel;
          var newHead_contractSuit = action[0];
          var newHead_contractPointOfCompass = head.contractPointOfCompass;
          var newHead_isDoubled = head.isDoubled;
          var newHead_isRedoubled = head.isRedoubled;
          var newHead_isPass = head.isPass;
          var newHead = {
            contractLevel: newHead_contractLevel,
            contractSuit: newHead_contractSuit,
            contractPointOfCompass: newHead_contractPointOfCompass,
            isDoubled: newHead_isDoubled,
            isRedoubled: newHead_isRedoubled,
            isPass: newHead_isPass
          };
          var tail = List.tl(bids$1);
          var bidsUpdated = /* :: */[
            newHead,
            tail
          ];
          var poc$2 = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.activePointOfCompass);
          return {
                  activePointOfCompass: poc$2,
                  bids: bidsUpdated,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  discardIndex: state.discardIndex,
                  discardSuit: state.discardSuit,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: true,
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
                  isReviewDealVisible: state.isReviewDealVisible,
                  lastAction: "BidUpdate",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* BidAddSpecial */3 :
          var special = action[0];
          ((window.isLastActionSync = false));
          var poc$3 = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.activePointOfCompass);
          if (special === undefined) {
            return state;
          }
          switch (special) {
            case "Pass" :
                var bidsLength = List.length(state.bids);
                console.log("bidsLength:");
                console.log(bidsLength);
                console.log("state.bids keep by isPass===false:");
                console.log(Belt_List.keep(state.bids, (function (x) {
                            return x.isPass === false;
                          })) === /* [] */0);
                if (bidsLength === 3 && Belt_List.keep(state.bids, (function (x) {
                          return x.isPass === false;
                        })) === /* [] */0) {
                  console.log("detected 4 passes");
                  ((window.isLastActionSync = false));
                  return {
                          activePointOfCompass: state.dealer,
                          bids: /* [] */0,
                          chicagoScoreSheet: state.chicagoScoreSheet,
                          dealer: state.dealer,
                          dealIndex: state.dealIndex,
                          declarer: undefined,
                          discardIndex: -1,
                          discardSuit: state.discardSuit,
                          handVisible: state.handVisible,
                          isBiddingCycle: true,
                          isBiddingHideDenominationButtons: true,
                          isDummyVisible: false,
                          isRebootVisible: state.isRebootVisible,
                          isReviewDealVisible: state.isReviewDealVisible,
                          lastAction: "4 Passes - so fresh cards dealt",
                          pack: Shuffle$ReasonReactExamples.getShuffledPack(undefined),
                          pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                          randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                        };
                }
                if (bidsLength < 3) {
                  return {
                          activePointOfCompass: poc$3,
                          bids: /* :: */[
                            {
                              contractLevel: undefined,
                              contractSuit: undefined,
                              contractPointOfCompass: state.activePointOfCompass,
                              isDoubled: false,
                              isRedoubled: false,
                              isPass: true
                            },
                            state.bids
                          ],
                          chicagoScoreSheet: state.chicagoScoreSheet,
                          dealer: state.dealer,
                          dealIndex: state.dealIndex,
                          declarer: state.declarer,
                          discardIndex: state.discardIndex,
                          discardSuit: state.discardSuit,
                          handVisible: state.handVisible,
                          isBiddingCycle: state.isBiddingCycle,
                          isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                          isDummyVisible: state.isDummyVisible,
                          isRebootVisible: state.isRebootVisible,
                          isReviewDealVisible: state.isReviewDealVisible,
                          lastAction: "BidAddSpecial",
                          pack: state.pack,
                          pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                          randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                        };
                }
                var hd1 = List.hd(state.bids);
                var tl = List.tl(state.bids);
                var hd2 = List.hd(tl);
                if (!(hd1.isPass === true && hd2.isPass === true)) {
                  return {
                          activePointOfCompass: poc$3,
                          bids: /* :: */[
                            {
                              contractLevel: undefined,
                              contractSuit: undefined,
                              contractPointOfCompass: state.activePointOfCompass,
                              isDoubled: false,
                              isRedoubled: false,
                              isPass: true
                            },
                            state.bids
                          ],
                          chicagoScoreSheet: state.chicagoScoreSheet,
                          dealer: state.dealer,
                          dealIndex: state.dealIndex,
                          declarer: state.declarer,
                          discardIndex: state.discardIndex,
                          discardSuit: state.discardSuit,
                          handVisible: state.handVisible,
                          isBiddingCycle: state.isBiddingCycle,
                          isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                          isDummyVisible: state.isDummyVisible,
                          isRebootVisible: state.isRebootVisible,
                          isReviewDealVisible: state.isReviewDealVisible,
                          lastAction: "BidAddSpecial",
                          pack: state.pack,
                          pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                          randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                        };
                }
                var partnerPocByPoc = function (poc) {
                  if (poc === undefined) {
                    return "Error";
                  }
                  switch (poc) {
                    case "East" :
                        return "West";
                    case "North" :
                        return "South";
                    case "South" :
                        return "North";
                    case "West" :
                        return "East";
                    default:
                      return "Error";
                  }
                };
                var bidsListFiltered = Belt_List.keep(state.bids, (function (x) {
                        return x.isPass === false;
                      }));
                var bidRecordOfInterest1 = List.hd(bidsListFiltered);
                var tailOfInterest = List.tl(bidsListFiltered);
                var bidRecordOfInterest2 = bidRecordOfInterest1.contractLevel === undefined && (bidRecordOfInterest1.isDoubled === true || bidRecordOfInterest1.isRedoubled === true) ? List.hd(tailOfInterest) : bidRecordOfInterest1;
                var contractLevel = bidRecordOfInterest2.contractLevel;
                var contractSuit = bidRecordOfInterest2.contractSuit;
                var contractPoc = bidRecordOfInterest2.contractPointOfCompass;
                var isDoubled = bidRecordOfInterest1.contractLevel === undefined && bidRecordOfInterest1.isDoubled === true;
                var isRedoubled = bidRecordOfInterest1.contractLevel === undefined && bidRecordOfInterest1.isRedoubled === true;
                var bidsFilteredBySuitAnd2Poc = Belt_List.keep(state.bids, (function (x) {
                        if (Caml_obj.caml_equal(x.contractSuit, contractSuit)) {
                          if (Caml_obj.caml_equal(x.contractPointOfCompass, contractPoc)) {
                            return true;
                          } else {
                            return Caml_obj.caml_equal(x.contractPointOfCompass, partnerPocByPoc(contractPoc));
                          }
                        } else {
                          return false;
                        }
                      }));
                var bidsFilteredBySuitAnd2PocReversed = Belt_List.reverse(bidsFilteredBySuitAnd2Poc);
                var hd3 = List.hd(bidsFilteredBySuitAnd2PocReversed);
                var contractDeclarer = hd3.contractPointOfCompass;
                var chicagoScoreSheetHead = Belt_List.headExn(state.chicagoScoreSheet);
                var chicagoScoreSheetTail = Belt_List.tailExn(state.chicagoScoreSheet);
                var myChicagoScoreSheetRecord_vulnerable = chicagoScoreSheetHead.vulnerable;
                var myChicagoScoreSheetRecord_totalTricksNorthSouth = 0;
                var myChicagoScoreSheetRecord_totalTricksWestEast = 0;
                var myChicagoScoreSheetRecord = {
                  vulnerable: myChicagoScoreSheetRecord_vulnerable,
                  contractLevel: contractLevel,
                  contractSuit: contractSuit,
                  contractDeclarer: contractDeclarer,
                  isDoubled: isDoubled,
                  isRedoubled: isRedoubled,
                  totalTricksNorthSouth: myChicagoScoreSheetRecord_totalTricksNorthSouth,
                  scoreNorthSouth: undefined,
                  totalTricksWestEast: myChicagoScoreSheetRecord_totalTricksWestEast,
                  scoreWestEast: undefined
                };
                return {
                        activePointOfCompass: Shuffle$ReasonReactExamples.getNextActivePointOfCompass(contractDeclarer),
                        bids: state.bids,
                        chicagoScoreSheet: contractLevel !== undefined ? /* :: */[
                            myChicagoScoreSheetRecord,
                            chicagoScoreSheetTail
                          ] : chicagoScoreSheetTail,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: contractDeclarer,
                        discardIndex: state.discardIndex,
                        discardSuit: state.discardSuit,
                        handVisible: state.handVisible,
                        isBiddingCycle: false,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        isReviewDealVisible: state.isReviewDealVisible,
                        lastAction: contractLevel !== undefined ? "BidAddSpecial- 3 Passes" : "BidAddSpecial- 4 Passes",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            case "X" :
                return {
                        activePointOfCompass: poc$3,
                        bids: /* :: */[
                          {
                            contractLevel: undefined,
                            contractSuit: undefined,
                            contractPointOfCompass: undefined,
                            isDoubled: true,
                            isRedoubled: false,
                            isPass: false
                          },
                          state.bids
                        ],
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        discardIndex: state.discardIndex,
                        discardSuit: state.discardSuit,
                        handVisible: state.handVisible,
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        isReviewDealVisible: state.isReviewDealVisible,
                        lastAction: "BidAddSpecial - X",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            case "XX" :
                return {
                        activePointOfCompass: poc$3,
                        bids: /* :: */[
                          {
                            contractLevel: undefined,
                            contractSuit: undefined,
                            contractPointOfCompass: state.activePointOfCompass,
                            isDoubled: false,
                            isRedoubled: true,
                            isPass: false
                          },
                          state.bids
                        ],
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        discardIndex: state.discardIndex,
                        discardSuit: state.discardSuit,
                        handVisible: state.handVisible,
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        isReviewDealVisible: state.isReviewDealVisible,
                        lastAction: "BidAddSpecial - XX",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            default:
              return state;
          }
      
    }
  }
}

exports.initialState = initialState;
exports.reducer = reducer;
/*  Not a pure module */
