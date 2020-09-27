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
var TopLevel$ReasonReactExamples = require("./TopLevel.bs.js");

var Online = require('./Online.bs');
;

var initialState_pack = [];

var initialState_pointOfCompassAndPlayers = [];

var initialState_transition = {
  northStartY: 0.0,
  eastStartX: 0.0,
  southStartY: 0.0,
  westStartX: 0.0,
  northEndY: 0.0,
  eastEndX: 0.0,
  southEndY: 0.0,
  westEndX: 0.0,
  northStartX: 0.0,
  eastStartY: 0.0,
  southStartX: 0.0,
  westStartY: 0.0,
  northEndX: 0.0,
  eastEndY: 0.0,
  southEndX: 0.0,
  westEndY: 0.0
};

var initialState = {
  activePointOfCompass: undefined,
  bids: /* [] */0,
  chicagoScoreSheet: Chicago$ReasonReactExamples.initialChicagoScoreSheet,
  dealer: undefined,
  dealIndex: -1,
  declarer: undefined,
  discardIndex: -1,
  discardPointOfCompass: undefined,
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
  randomInt: 1,
  transition: initialState_transition
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
          var m = window.m;
          var cardHeightToCanvasHeightRatio = window.cardHeightToCanvasHeightRatio;
          var cardAspectRatio = window.cardAspectRatio;
          var cardWidthNormalized = m * cardHeightToCanvasHeightRatio / cardAspectRatio;
          var cardHeightNormalized = m * cardHeightToCanvasHeightRatio;
          var cardWidthOffsetFraction = window.cardWidthOffsetFraction;
          var cardHeightOffsetFraction = window.cardHeightOffsetFraction;
          var northEndY = -cardHeightNormalized * cardHeightOffsetFraction;
          var eastEndX = cardWidthNormalized * cardWidthOffsetFraction;
          var southEndY = cardHeightNormalized * cardHeightOffsetFraction;
          var westEndX = -cardWidthNormalized * cardWidthOffsetFraction;
          var tR;
          switch (discardPoc) {
            case "East" :
                var init = state.transition;
                tR = {
                  northStartY: init.northStartY,
                  eastStartX: 0.5,
                  southStartY: init.southStartY,
                  westStartX: init.westStartX,
                  northEndY: init.northEndY,
                  eastEndX: eastEndX,
                  southEndY: init.southEndY,
                  westEndX: init.westEndX,
                  northStartX: init.northStartX,
                  eastStartY: 0.0,
                  southStartX: init.southStartX,
                  westStartY: init.westStartY,
                  northEndX: init.northEndX,
                  eastEndY: 0.0,
                  southEndX: init.southEndX,
                  westEndY: init.westEndY
                };
                break;
            case "North" :
                var init$1 = state.transition;
                tR = {
                  northStartY: -0.5,
                  eastStartX: init$1.eastStartX,
                  southStartY: init$1.southStartY,
                  westStartX: init$1.westStartX,
                  northEndY: northEndY,
                  eastEndX: init$1.eastEndX,
                  southEndY: init$1.southEndY,
                  westEndX: init$1.westEndX,
                  northStartX: 0.0,
                  eastStartY: init$1.eastStartY,
                  southStartX: init$1.southStartX,
                  westStartY: init$1.westStartY,
                  northEndX: 0.0,
                  eastEndY: init$1.eastEndY,
                  southEndX: init$1.southEndX,
                  westEndY: init$1.westEndY
                };
                break;
            case "South" :
                var init$2 = state.transition;
                tR = {
                  northStartY: init$2.northStartY,
                  eastStartX: init$2.eastStartX,
                  southStartY: 0.5,
                  westStartX: init$2.westStartX,
                  northEndY: init$2.northEndY,
                  eastEndX: init$2.eastEndX,
                  southEndY: southEndY,
                  westEndX: init$2.westEndX,
                  northStartX: init$2.northStartX,
                  eastStartY: init$2.eastStartY,
                  southStartX: 0.0,
                  westStartY: init$2.westStartY,
                  northEndX: init$2.northEndX,
                  eastEndY: init$2.eastEndY,
                  southEndX: 0.0,
                  westEndY: init$2.westEndY
                };
                break;
            case "West" :
                var init$3 = state.transition;
                tR = {
                  northStartY: init$3.northStartY,
                  eastStartX: init$3.eastStartX,
                  southStartY: init$3.southStartY,
                  westStartX: -0.5,
                  northEndY: init$3.northEndY,
                  eastEndX: init$3.eastEndX,
                  southEndY: init$3.southEndY,
                  westEndX: westEndX,
                  northStartX: init$3.northStartX,
                  eastStartY: init$3.eastStartY,
                  southStartX: init$3.southStartX,
                  westStartY: 0.0,
                  northEndX: init$3.northEndX,
                  eastEndY: init$3.eastEndY,
                  southEndX: init$3.southEndX,
                  westEndY: 0.0
                };
                break;
            default:
              tR = state.transition;
          }
          var poc = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.activePointOfCompass);
          var myDiscardArray = Belt_Array.keep(myPack, (function (x) {
                  return x.lifecycle === /* Discard */2;
                }));
          console.log("QtyDiscards");
          console.log(myDiscardArray.length);
          if (myDiscardArray.length === 4) {
            ((setTimeout(function(){document.getElementById('btnPostDiscard').click();}, 2000)));
          }
          var newrecord = Caml_obj.caml_obj_dup(state);
          newrecord.transition = tR;
          newrecord.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
          newrecord.pack = myPack;
          newrecord.lastAction = "Discard";
          newrecord.isDummyVisible = discardPoc === pocFollowingDeclarer ? true : state.isDummyVisible;
          newrecord.discardSuit = (state.discardIndex + 1 | 0) % 4 === 0 ? cardDiscardSuit : state.discardSuit;
          newrecord.discardPointOfCompass = (state.discardIndex + 1 | 0) % 4 === 0 ? discardPoc : state.discardPointOfCompass;
          newrecord.discardIndex = state.discardIndex + 1 | 0;
          newrecord.activePointOfCompass = poc;
          return newrecord;
      case /* PostDiscard */2 :
          var m$1 = window.m;
          var cardHeightToCanvasHeightRatio$1 = window.cardHeightToCanvasHeightRatio;
          var cardAspectRatio$1 = window.cardAspectRatio;
          var cardWidthNormalized$1 = m$1 * cardHeightToCanvasHeightRatio$1 / cardAspectRatio$1;
          var cardHeightNormalized$1 = m$1 * cardHeightToCanvasHeightRatio$1;
          var cardWidthOffsetFraction$1 = window.cardWidthOffsetFraction;
          var cardHeightOffsetFraction$1 = window.cardHeightOffsetFraction;
          var northStartY = -cardHeightNormalized$1 * cardHeightOffsetFraction$1;
          var eastStartX = cardWidthNormalized$1 * cardWidthOffsetFraction$1;
          var southStartY = cardHeightNormalized$1 * cardHeightOffsetFraction$1;
          var westStartX = -cardWidthNormalized$1 * cardWidthOffsetFraction$1;
          var winningDiscardPoc = TopLevel$ReasonReactExamples.getWinningDiscardPoc(state);
          var commonEndPositionY;
          switch (winningDiscardPoc) {
            case "North" :
                commonEndPositionY = -0.5 - cardHeightNormalized$1 * 0.5;
                break;
            case "South" :
                commonEndPositionY = 0.5 + cardHeightNormalized$1 * 0.5;
                break;
            case "East" :
            case "West" :
                commonEndPositionY = 0.0;
                break;
            default:
              commonEndPositionY = 0.0;
          }
          var commonEndPositionX;
          switch (winningDiscardPoc) {
            case "East" :
                commonEndPositionX = 0.5 + cardWidthNormalized$1 * 0.5;
                break;
            case "North" :
            case "South" :
                commonEndPositionX = 0.0;
                break;
            case "West" :
                commonEndPositionX = -0.5 - cardWidthNormalized$1 * 0.5;
                break;
            default:
              commonEndPositionX = 0.0;
          }
          var tR$1 = {
            northStartY: northStartY,
            eastStartX: eastStartX,
            southStartY: southStartY,
            westStartX: westStartX,
            northEndY: commonEndPositionY,
            eastEndX: commonEndPositionX,
            southEndY: commonEndPositionY,
            westEndX: commonEndPositionX,
            northStartX: 0.0,
            eastStartY: 0.0,
            southStartX: 0.0,
            westStartY: 0.0,
            northEndX: commonEndPositionX,
            eastEndY: commonEndPositionY,
            southEndX: commonEndPositionX,
            westEndY: commonEndPositionY
          };
          ((setTimeout(function(){document.getElementById('btnEndTrick').click();}, 500)));
          var newrecord$1 = Caml_obj.caml_obj_dup(state);
          newrecord$1.transition = tR$1;
          newrecord$1.lastAction = "PostDiscard";
          return newrecord$1;
      case /* Sync */3 :
          ((window.isLastActionSync = true));
          return {
                  activePointOfCompass: undefined,
                  bids: /* [] */0,
                  chicagoScoreSheet: /* [] */0,
                  dealer: undefined,
                  dealIndex: -1,
                  declarer: undefined,
                  discardIndex: -1,
                  discardPointOfCompass: undefined,
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
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined),
                  transition: {
                    northStartY: 0.0,
                    eastStartX: 0.0,
                    southStartY: 0.0,
                    westStartX: 0.0,
                    northEndY: 0.0,
                    eastEndX: 0.0,
                    southEndY: 0.0,
                    westEndX: 0.0,
                    northStartX: 0.0,
                    eastStartY: 0.0,
                    southStartX: 0.0,
                    westStartY: 0.0,
                    northEndX: 0.0,
                    eastEndY: 0.0,
                    southEndX: 0.0,
                    westEndY: 0.0
                  }
                };
      case /* LoginSync */4 :
          ((window.isLastActionSync = true));
          var cSS = window.gameState.chicagoScoreSheet;
          var dealer = window.gameState.dealer;
          var declarer = window.gameState.declarer;
          var hV = window.gameState.handVisible;
          var tR$2 = window.gameState.transition;
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
          var discardPointOfCompass = window.gameState.discardPointOfCompass;
          return {
                  activePointOfCompass: poc$1,
                  bids: bids,
                  chicagoScoreSheet: cSS,
                  dealer: dealer,
                  dealIndex: dealIndex,
                  declarer: declarer,
                  discardIndex: discardIndex,
                  discardPointOfCompass: discardPointOfCompass,
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
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined),
                  transition: tR$2
                };
      case /* Test */5 :
          ((window.isLastActionSync = true));
          var newrecord$2 = Caml_obj.caml_obj_dup(state);
          newrecord$2.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
          newrecord$2.lastAction = "Test";
          return newrecord$2;
      case /* EndTrick */6 :
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
          var newrecord$3 = Caml_obj.caml_obj_dup(state);
          newrecord$3.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
          newrecord$3.pointOfCompassAndPlayers = myArray2;
          newrecord$3.lastAction = "AssignPlayer";
          return newrecord$3;
      case /* BidAdd */1 :
          ((window.isLastActionSync = false));
          var newrecord$4 = Caml_obj.caml_obj_dup(state);
          newrecord$4.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
          newrecord$4.lastAction = "BidAdd";
          newrecord$4.isBiddingHideDenominationButtons = false;
          newrecord$4.bids = /* :: */[
            {
              contractLevel: action[0],
              contractSuit: "",
              contractPointOfCompass: state.activePointOfCompass,
              isDoubled: false,
              isRedoubled: false,
              isPass: false
            },
            state.bids
          ];
          return newrecord$4;
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
          var newrecord$5 = Caml_obj.caml_obj_dup(state);
          newrecord$5.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
          newrecord$5.lastAction = "BidUpdate";
          newrecord$5.isBiddingHideDenominationButtons = true;
          newrecord$5.bids = bidsUpdated;
          newrecord$5.activePointOfCompass = poc$2;
          return newrecord$5;
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
                  var newrecord$6 = Caml_obj.caml_obj_dup(state);
                  newrecord$6.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
                  newrecord$6.pack = Shuffle$ReasonReactExamples.getShuffledPack(undefined);
                  newrecord$6.lastAction = "4 Passes - so fresh cards dealt";
                  newrecord$6.isDummyVisible = false;
                  newrecord$6.isBiddingHideDenominationButtons = true;
                  newrecord$6.isBiddingCycle = true;
                  newrecord$6.discardIndex = -1;
                  newrecord$6.declarer = undefined;
                  newrecord$6.bids = /* [] */0;
                  newrecord$6.activePointOfCompass = state.dealer;
                  return newrecord$6;
                }
                if (bidsLength >= 3) {
                  var hd1 = List.hd(state.bids);
                  var tl = List.tl(state.bids);
                  var hd2 = List.hd(tl);
                  if (hd1.isPass === true && hd2.isPass === true) {
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
                    var myPack$1 = $$Array.map((function (card) {
                            if (contractSuit !== undefined && contractSuit === "NoTrumps" && card.handOrder <= 12) {
                              return {
                                      noTrumpValue: card.noTrumpValue,
                                      handOrder: card.handOrder + 300 | 0,
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
                    var newrecord$7 = Caml_obj.caml_obj_dup(state);
                    newrecord$7.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
                    newrecord$7.pack = myPack$1;
                    newrecord$7.lastAction = contractLevel !== undefined ? "BidAddSpecial- 3 Passes" : "BidAddSpecial- 4 Passes";
                    newrecord$7.isBiddingCycle = false;
                    newrecord$7.declarer = contractDeclarer;
                    newrecord$7.chicagoScoreSheet = contractLevel !== undefined ? /* :: */[
                        myChicagoScoreSheetRecord,
                        chicagoScoreSheetTail
                      ] : chicagoScoreSheetTail;
                    newrecord$7.activePointOfCompass = Shuffle$ReasonReactExamples.getNextActivePointOfCompass(contractDeclarer);
                    return newrecord$7;
                  }
                  var newrecord$8 = Caml_obj.caml_obj_dup(state);
                  newrecord$8.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
                  newrecord$8.lastAction = "BidAddSpecial";
                  newrecord$8.bids = /* :: */[
                    {
                      contractLevel: undefined,
                      contractSuit: undefined,
                      contractPointOfCompass: state.activePointOfCompass,
                      isDoubled: false,
                      isRedoubled: false,
                      isPass: true
                    },
                    state.bids
                  ];
                  newrecord$8.activePointOfCompass = poc$3;
                  return newrecord$8;
                }
                var newrecord$9 = Caml_obj.caml_obj_dup(state);
                newrecord$9.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
                newrecord$9.lastAction = "BidAddSpecial";
                newrecord$9.bids = /* :: */[
                  {
                    contractLevel: undefined,
                    contractSuit: undefined,
                    contractPointOfCompass: state.activePointOfCompass,
                    isDoubled: false,
                    isRedoubled: false,
                    isPass: true
                  },
                  state.bids
                ];
                newrecord$9.activePointOfCompass = poc$3;
                return newrecord$9;
            case "X" :
                var newrecord$10 = Caml_obj.caml_obj_dup(state);
                newrecord$10.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
                newrecord$10.lastAction = "BidAddSpecial - X";
                newrecord$10.bids = /* :: */[
                  {
                    contractLevel: undefined,
                    contractSuit: undefined,
                    contractPointOfCompass: undefined,
                    isDoubled: true,
                    isRedoubled: false,
                    isPass: false
                  },
                  state.bids
                ];
                newrecord$10.activePointOfCompass = poc$3;
                return newrecord$10;
            case "XX" :
                var newrecord$11 = Caml_obj.caml_obj_dup(state);
                newrecord$11.randomInt = Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined);
                newrecord$11.lastAction = "BidAddSpecial - XX";
                newrecord$11.bids = /* :: */[
                  {
                    contractLevel: undefined,
                    contractSuit: undefined,
                    contractPointOfCompass: state.activePointOfCompass,
                    isDoubled: false,
                    isRedoubled: true,
                    isPass: false
                  },
                  state.bids
                ];
                newrecord$11.activePointOfCompass = poc$3;
                return newrecord$11;
            default:
              return state;
          }
      
    }
  }
}

exports.initialState = initialState;
exports.reducer = reducer;
/*  Not a pure module */
