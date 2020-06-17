'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Chicago$ReasonReactExamples = require("./Chicago.bs.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

var Online = require('./Online.bs');
;

var initialState_pointOfCompassAndPlayers = [];

var initialState = {
  chicagoScoreSheet: Chicago$ReasonReactExamples.initialChicagoScoreSheet,
  dealer: undefined,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
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
                  chicagoScoreSheet: [],
                  dealer: undefined,
                  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
                  lastAction: "NewGame",
                  pack: [],
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Shuffle */1 :
          ((window.isLastActionSync = false));
          return {
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: Shuffle$ReasonReactExamples.getNextDealerLocation(state.dealer),
                  handVisible: state.handVisible,
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
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  handVisible: state.handVisible,
                  lastAction: "Discard",
                  pack: myPack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Sync */3 :
          ((window.isLastActionSync = true));
          return {
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  handVisible: state.handVisible,
                  lastAction: "LogoutOrServerDownSync",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* LoginSync */4 :
          ((window.isLastActionSync = true));
          var cSS = window.gameState.chicagoScoreSheet;
          var dealer = window.gameState.dealer;
          var hV = window.gameState.handVisible;
          var pOCAP = window.gameState.pointOfCompassAndPlayers;
          var pack = window.gameState.pack;
          return {
                  chicagoScoreSheet: cSS,
                  dealer: dealer,
                  handVisible: hV,
                  lastAction: "LoginSync",
                  pack: pack,
                  pointOfCompassAndPlayers: pOCAP,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Test */5 :
          ((window.isLastActionSync = true));
          console.log("benign action: 'Test'");
          return {
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  handVisible: state.handVisible,
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
      var myArray1 = $$Array.map((function (pointOfCompassAndPlayer) {
              if (pointOfCompassAndPlayer.pointOfCompass === pOfCAndP.pointOfCompass) {
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
              chicagoScoreSheet: state.chicagoScoreSheet,
              dealer: state.dealer,
              handVisible: state.handVisible,
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
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  handVisible: {
                    north: !state.handVisible.north,
                    east: init.east,
                    south: init.south,
                    west: init.west
                  },
                  lastAction: "Flip",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* East */1 :
          var init$1 = state.handVisible;
          return {
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  handVisible: {
                    north: init$1.north,
                    east: !state.handVisible.east,
                    south: init$1.south,
                    west: init$1.west
                  },
                  lastAction: "Flip",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* South */2 :
          var init$2 = state.handVisible;
          return {
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  handVisible: {
                    north: init$2.north,
                    east: init$2.east,
                    south: !state.handVisible.south,
                    west: init$2.west
                  },
                  lastAction: "Flip",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* West */3 :
          var init$3 = state.handVisible;
          return {
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  handVisible: {
                    north: init$3.north,
                    east: init$3.east,
                    south: init$3.south,
                    west: !state.handVisible.west
                  },
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
