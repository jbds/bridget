'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var $$String = require("bs-platform/lib/js/string.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Chicago$ReasonReactExamples = require("./Chicago.bs.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

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
                  handVisible: state.handVisible,
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
          var chicagoScoreSheetHead = Belt_List.headExn(state.chicagoScoreSheet);
          var chicagoScoreSheetTail = Belt_List.tailExn(state.chicagoScoreSheet);
          var myChicagoScoreSheetRecord_vulnerable = chicagoScoreSheetHead.vulnerable;
          var myChicagoScoreSheetRecord_contractLevel = chicagoScoreSheetHead.contractLevel;
          var myChicagoScoreSheetRecord_contractSuit = chicagoScoreSheetHead.contractSuit;
          var myChicagoScoreSheetRecord_contractDeclarer = chicagoScoreSheetHead.contractDeclarer;
          var myChicagoScoreSheetRecord_isDoubled = chicagoScoreSheetHead.isDoubled;
          var myChicagoScoreSheetRecord_isRedoubled = chicagoScoreSheetHead.isRedoubled;
          var myChicagoScoreSheetRecord_totalTricksNorthSouth = chicagoScoreSheetHead.totalTricksNorthSouth + totalTricksNorthSouthIncrement | 0;
          var myChicagoScoreSheetRecord_scoreNorthSouth = chicagoScoreSheetHead.scoreNorthSouth;
          var myChicagoScoreSheetRecord_totalTricksWestEast = chicagoScoreSheetHead.totalTricksWestEast + totalTricksWestEastIncrement | 0;
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
            var scoreLookup = Chicago$ReasonReactExamples.getScore(Shuffle$ReasonReactExamples.optionIntAsInt(scoreSheetRecord.contractLevel), myScoreLookupDenomination, scoreSheetRecord.contractDeclarer === "North" || scoreSheetRecord.contractDeclarer === "South" ? chicagoScoreSheetHead.totalTricksNorthSouth + totalTricksNorthSouthIncrement | 0 : chicagoScoreSheetHead.totalTricksWestEast + totalTricksWestEastIncrement | 0, isVulnerable, false, false);
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
          var myPack$1 = $$Array.map((function (card) {
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
          return {
                  activePointOfCompass: state.discardIndex !== 51 ? winningDiscardPoc : endOfDealNextPoc,
                  bids: state.bids,
                  chicagoScoreSheet: /* :: */[
                    myChicagoScoreSheetRecordWithOptionalScore,
                    chicagoScoreSheetTail
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
                  pack: myPack$1,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      
    }
  } else {
    switch (action.tag | 0) {
      case /* Flip */0 :
          ((window.isLastActionSync = false));
          switch (action[0]) {
            case /* North */0 :
                var init = state.handVisible;
                return {
                        activePointOfCompass: state.activePointOfCompass,
                        bids: state.bids,
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        discardIndex: state.discardIndex,
                        discardSuit: state.discardSuit,
                        handVisible: {
                          north: !state.handVisible.north,
                          east: init.east,
                          south: init.south,
                          west: init.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        isReviewDealVisible: state.isReviewDealVisible,
                        lastAction: "Flip",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            case /* East */1 :
                var init$1 = state.handVisible;
                return {
                        activePointOfCompass: state.activePointOfCompass,
                        bids: state.bids,
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        discardIndex: state.discardIndex,
                        discardSuit: state.discardSuit,
                        handVisible: {
                          north: init$1.north,
                          east: !state.handVisible.east,
                          south: init$1.south,
                          west: init$1.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        isReviewDealVisible: state.isReviewDealVisible,
                        lastAction: "Flip",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            case /* South */2 :
                var init$2 = state.handVisible;
                return {
                        activePointOfCompass: state.activePointOfCompass,
                        bids: state.bids,
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        discardIndex: state.discardIndex,
                        discardSuit: state.discardSuit,
                        handVisible: {
                          north: init$2.north,
                          east: init$2.east,
                          south: !state.handVisible.south,
                          west: init$2.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        isReviewDealVisible: state.isReviewDealVisible,
                        lastAction: "Flip",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            case /* West */3 :
                var init$3 = state.handVisible;
                return {
                        activePointOfCompass: state.activePointOfCompass,
                        bids: state.bids,
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        discardIndex: state.discardIndex,
                        discardSuit: state.discardSuit,
                        handVisible: {
                          north: init$3.north,
                          east: init$3.east,
                          south: init$3.south,
                          west: !state.handVisible.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        isReviewDealVisible: state.isReviewDealVisible,
                        lastAction: "Flip",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            
          }
      case /* AssignPlayer */1 :
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
      case /* BidAdd */2 :
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
      case /* BidUpdate */3 :
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
      case /* BidAddSpecial */4 :
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
                          lastAction: "4 Passes - so New Deal",
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
                var match = List.length(state.chicagoScoreSheet) % 4;
                var vulnerable = match > 2 || match < 0 ? (
                    match !== 3 ? "Error" : "All"
                  ) : (
                    match !== 0 ? $$String.sub(Shuffle$ReasonReactExamples.pocAsString(state.dealer), 0, 1) : "None"
                  );
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
                var contractSuit$1 = bidRecordOfInterest2.contractSuit;
                var contractPoc = bidRecordOfInterest2.contractPointOfCompass;
                var isDoubled = bidRecordOfInterest1.contractLevel === undefined && bidRecordOfInterest1.isDoubled === true;
                var isRedoubled = bidRecordOfInterest1.contractLevel === undefined && bidRecordOfInterest1.isRedoubled === true;
                var bidsFilteredBySuitAnd2Poc = Belt_List.keep(state.bids, (function (x) {
                        if (Caml_obj.caml_equal(x.contractSuit, contractSuit$1)) {
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
                var chicagoScoreSheetRecord = {
                  vulnerable: vulnerable,
                  contractLevel: contractLevel,
                  contractSuit: contractSuit$1,
                  contractDeclarer: contractDeclarer,
                  isDoubled: isDoubled,
                  isRedoubled: isRedoubled,
                  totalTricksNorthSouth: 0,
                  scoreNorthSouth: undefined,
                  totalTricksWestEast: 0,
                  scoreWestEast: undefined
                };
                return {
                        activePointOfCompass: Shuffle$ReasonReactExamples.getNextActivePointOfCompass(contractDeclarer),
                        bids: state.bids,
                        chicagoScoreSheet: contractLevel !== undefined ? /* :: */[
                            chicagoScoreSheetRecord,
                            state.chicagoScoreSheet
                          ] : state.chicagoScoreSheet,
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
