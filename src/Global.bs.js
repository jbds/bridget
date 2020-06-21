'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Chicago$ReasonReactExamples = require("./Chicago.bs.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

var Online = require('./Online.bs');
;

var initialState_pointOfCompassAndPlayers = [];

var initialState = {
  activePointOfCompass: undefined,
  chicagoScoreSheet: Chicago$ReasonReactExamples.initialChicagoScoreSheet,
  dealer: undefined,
  dealIndex: -1,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  isBiddingCycle: false,
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
                  chicagoScoreSheet: [],
                  dealer: undefined,
                  dealIndex: -1,
                  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
                  isBiddingCycle: state.isBiddingCycle,
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
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: poc,
                  dealIndex: state.dealIndex + 1 | 0,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
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
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  lastAction: "Discard",
                  pack: myPack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Sync */3 :
          ((window.isLastActionSync = true));
          return {
                  activePointOfCompass: undefined,
                  chicagoScoreSheet: [],
                  dealer: undefined,
                  dealIndex: -1,
                  handVisible: {
                    north: false,
                    east: false,
                    south: false,
                    west: false
                  },
                  isBiddingCycle: false,
                  lastAction: "LogoutOrServerDownSync",
                  pack: [],
                  pointOfCompassAndPlayers: [],
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* LoginSync */4 :
          ((window.isLastActionSync = true));
          var cSS = window.gameState.chicagoScoreSheet;
          var dealer = window.gameState.dealer;
          var hV = window.gameState.handVisible;
          var pOCAP = window.gameState.pointOfCompassAndPlayers;
          var pack = window.gameState.pack;
          var dealIndex = window.gameState.dealIndex;
          var isBiddingCycle = window.gameState.isBiddingCycle;
          var poc$1 = window.gameState.activePointOfCompass;
          return {
                  activePointOfCompass: poc$1,
                  chicagoScoreSheet: cSS,
                  dealer: dealer,
                  dealIndex: dealIndex,
                  handVisible: hV,
                  isBiddingCycle: isBiddingCycle,
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
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  lastAction: "Test",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      
    }
  } else {
    if (action.tag) {
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
              chicagoScoreSheet: state.chicagoScoreSheet,
              dealer: state.dealer,
              dealIndex: state.dealIndex,
              handVisible: state.handVisible,
              isBiddingCycle: state.isBiddingCycle,
              lastAction: "AssignPlayer",
              pack: state.pack,
              pointOfCompassAndPlayers: myArray2,
              randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
            };
    }
    ((window.isLastActionSync = false));
    switch (action[0]) {
      case /* North */0 :
          var init = state.handVisible;
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  handVisible: {
                    north: !state.handVisible.north,
                    east: init.east,
                    south: init.south,
                    west: init.west
                  },
                  isBiddingCycle: state.isBiddingCycle,
                  lastAction: "Flip",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* East */1 :
          var init$1 = state.handVisible;
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  handVisible: {
                    north: init$1.north,
                    east: !state.handVisible.east,
                    south: init$1.south,
                    west: init$1.west
                  },
                  isBiddingCycle: state.isBiddingCycle,
                  lastAction: "Flip",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* South */2 :
          var init$2 = state.handVisible;
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  handVisible: {
                    north: init$2.north,
                    east: init$2.east,
                    south: !state.handVisible.south,
                    west: init$2.west
                  },
                  isBiddingCycle: state.isBiddingCycle,
                  lastAction: "Flip",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* West */3 :
          var init$3 = state.handVisible;
          return {
                  activePointOfCompass: state.activePointOfCompass,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  handVisible: {
                    north: init$3.north,
                    east: init$3.east,
                    south: init$3.south,
                    west: !state.handVisible.west
                  },
                  isBiddingCycle: state.isBiddingCycle,
                  lastAction: "Flip",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      
    }
  }
}

exports.initialState = initialState;
exports.reducer = reducer;
/*  Not a pure module */
