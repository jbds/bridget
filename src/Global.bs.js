'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Chicago$ReasonReactExamples = require("./Chicago.bs.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

var Online = require('./Online.bs');
;

var initialState_pointOfCompassAndPlayers = [];

var initialState = {
  activePointOfCompass: undefined,
  bids: /* [] */0,
  chicagoScoreSheet: Chicago$ReasonReactExamples.initialChicagoScoreSheet,
  dealer: undefined,
  dealIndex: -1,
  declarer: undefined,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  isBiddingCycle: false,
  isBiddingHideDenominationButtons: true,
  lastAction: "None(fromClient)",
  pack: Shuffle$ReasonReactExamples.initialPack,
  pointOfCompassAndPlayers: initialState_pointOfCompassAndPlayers,
  randomInt: -111
};

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* NewGame */0 :
          ((window.isLastActionSync = false));
          return {
                  activePointOfCompass: undefined,
                  bids: /* [] */0,
                  chicagoScoreSheet: [],
                  dealer: undefined,
                  dealIndex: -1,
                  declarer: undefined,
                  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
                  isBiddingCycle: false,
                  isBiddingHideDenominationButtons: true,
                  lastAction: "NewGame",
                  pack: [],
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Shuffle */1 :
          ((window.isLastActionSync = false));
          var poc = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.dealer);
          return {
                  activePointOfCompass: poc,
                  bids: /* [] */0,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: poc,
                  dealIndex: state.dealIndex + 1 | 0,
                  declarer: undefined,
                  handVisible: state.handVisible,
                  isBiddingCycle: true,
                  isBiddingHideDenominationButtons: true,
                  lastAction: "Shuffle",
                  pack: Shuffle$ReasonReactExamples.getShuffledPack(undefined),
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Discard */2 :
          ((window.isLastActionSync = false));
          var discardFileName = window.discardFileName;
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
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  bids: state.bids,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                  lastAction: "Discard",
                  pack: myPack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Sync */3 :
          ((window.isLastActionSync = true));
          return {
                  activePointOfCompass: undefined,
                  bids: /* [] */0,
                  chicagoScoreSheet: [],
                  dealer: undefined,
                  dealIndex: -1,
                  declarer: undefined,
                  handVisible: {
                    north: false,
                    east: false,
                    south: false,
                    west: false
                  },
                  isBiddingCycle: false,
                  isBiddingHideDenominationButtons: true,
                  lastAction: "LogoutOrServerDownSync",
                  pack: [],
                  pointOfCompassAndPlayers: [],
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* LoginSync */4 :
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
          return {
                  activePointOfCompass: poc$1,
                  bids: bids,
                  chicagoScoreSheet: cSS,
                  dealer: dealer,
                  dealIndex: dealIndex,
                  declarer: declarer,
                  handVisible: hV,
                  isBiddingCycle: isBiddingCycle,
                  isBiddingHideDenominationButtons: isBiddingHideDenominationButtons,
                  lastAction: "LoginSync",
                  pack: pack,
                  pointOfCompassAndPlayers: pOCAP,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Test */5 :
          ((window.isLastActionSync = true));
          console.log("benign action: 'Test'");
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  bids: state.bids,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                  lastAction: "Test",
                  pack: state.pack,
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
                        handVisible: {
                          north: !state.handVisible.north,
                          east: init.east,
                          south: init.south,
                          west: init.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
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
                        handVisible: {
                          north: init$1.north,
                          east: !state.handVisible.east,
                          south: init$1.south,
                          west: init$1.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
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
                        handVisible: {
                          north: init$2.north,
                          east: init$2.east,
                          south: !state.handVisible.south,
                          west: init$2.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
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
                        handVisible: {
                          north: init$3.north,
                          east: init$3.east,
                          south: init$3.south,
                          west: !state.handVisible.west
                        },
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        lastAction: "Flip",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            
          }
      case /* AssignPlayer */1 :
          var pOfCAndP = action[0];
          ((window.isLastActionSync = false));
          console.log("action AssignPlayer " + (pOfCAndP.player + (" to " + pOfCAndP.pointOfCompass)));
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
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                  lastAction: "AssignPlayer",
                  pack: state.pack,
                  pointOfCompassAndPlayers: myArray2,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* BidAdd */2 :
          console.log("Action - BidAdd");
          ((window.isLastActionSync = false));
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  bids: /* :: */[
                    {
                      contractLevel: action[0],
                      contractSuit: "",
                      contractPointOfCompass: state.activePointOfCompass,
                      isDoubled: false,
                      isRedoubled: false
                    },
                    state.bids
                  ],
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: false,
                  lastAction: "BidAdd",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* BidUpdate */3 :
          console.log("Action - BidUpdate");
          ((window.isLastActionSync = false));
          var bids$1 = state.bids;
          var head = List.hd(bids$1);
          var newHead_contractLevel = head.contractLevel;
          var newHead_contractSuit = action[0];
          var newHead_contractPointOfCompass = head.contractPointOfCompass;
          var newHead_isDoubled = head.isDoubled;
          var newHead_isRedoubled = head.isRedoubled;
          var newHead = {
            contractLevel: newHead_contractLevel,
            contractSuit: newHead_contractSuit,
            contractPointOfCompass: newHead_contractPointOfCompass,
            isDoubled: newHead_isDoubled,
            isRedoubled: newHead_isRedoubled
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
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                  lastAction: "BidUpdate",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* BidAddSpecial */4 :
          var special = action[0];
          console.log("Action - BidAddSpecial");
          ((window.isLastActionSync = false));
          var poc$3 = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.activePointOfCompass);
          console.log(poc$3);
          if (special === undefined) {
            return state;
          }
          switch (special) {
            case "Pass" :
                return {
                        activePointOfCompass: poc$3,
                        bids: /* :: */[
                          {
                            contractLevel: undefined,
                            contractSuit: undefined,
                            contractPointOfCompass: state.activePointOfCompass,
                            isDoubled: false,
                            isRedoubled: false
                          },
                          state.bids
                        ],
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        handVisible: state.handVisible,
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        lastAction: "BidAddSpecial",
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
                            contractPointOfCompass: state.activePointOfCompass,
                            isDoubled: true,
                            isRedoubled: false
                          },
                          state.bids
                        ],
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        handVisible: state.handVisible,
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        lastAction: "BidAddSpecial",
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
                            isRedoubled: true
                          },
                          state.bids
                        ],
                        chicagoScoreSheet: state.chicagoScoreSheet,
                        dealer: state.dealer,
                        dealIndex: state.dealIndex,
                        declarer: state.declarer,
                        handVisible: state.handVisible,
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        lastAction: "BidAddSpecial",
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
