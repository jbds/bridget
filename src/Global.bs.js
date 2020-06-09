'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

var initialState_pointOfCompassAndPlayers = [];

var initialState = {
  pack: Shuffle$ReasonReactExamples.initialPack,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  pointOfCompassAndPlayers: initialState_pointOfCompassAndPlayers,
  randomInt: 0
};

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* Shuffle */0 :
          ((window.isLastActionSync = false));
          return Shuffle$ReasonReactExamples.shufflePack(undefined);
      case /* Discard */1 :
          console.log("Action-Discard");
          ((window.isLastActionSync = false));
          return window.gameState;
      case /* Sync */2 :
          var myNewState = window.gameState;
          ((window.isLastActionSync = true));
          return myNewState;
      case /* Test */3 :
          ((window.isLastActionSync = true));
          console.log("benign action: 'Test'");
          return state;
      
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
              pack: state.pack,
              handVisible: state.handVisible,
              pointOfCompassAndPlayers: myArray2,
              randomInt: state.randomInt
            };
    }
    ((window.isLastActionSync = false));
    switch (action[0]) {
      case /* North */0 :
          var init = state.handVisible;
          return {
                  pack: state.pack,
                  handVisible: {
                    north: !state.handVisible.north,
                    east: init.east,
                    south: init.south,
                    west: init.west
                  },
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: state.randomInt
                };
      case /* East */1 :
          var init$1 = state.handVisible;
          return {
                  pack: state.pack,
                  handVisible: {
                    north: init$1.north,
                    east: !state.handVisible.east,
                    south: init$1.south,
                    west: init$1.west
                  },
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: state.randomInt
                };
      case /* South */2 :
          var init$2 = state.handVisible;
          return {
                  pack: state.pack,
                  handVisible: {
                    north: init$2.north,
                    east: init$2.east,
                    south: !state.handVisible.south,
                    west: init$2.west
                  },
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: state.randomInt
                };
      case /* West */3 :
          var init$3 = state.handVisible;
          return {
                  pack: state.pack,
                  handVisible: {
                    north: init$3.north,
                    east: init$3.east,
                    south: init$3.south,
                    west: !state.handVisible.west
                  },
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: state.randomInt
                };
      
    }
  }
}

exports.initialState = initialState;
exports.reducer = reducer;
/* No side effect */
