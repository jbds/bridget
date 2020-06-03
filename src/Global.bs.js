'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

var initialState_pointOfCompassAndPlayers = [];

var initialState = {
  pack: Shuffle$ReasonReactExamples.initialPack,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  pointOfCompassAndPlayers: initialState_pointOfCompassAndPlayers
};

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* Shuffle */0 :
          return Shuffle$ReasonReactExamples.shufflePack(undefined);
      case /* Discard */1 :
          var myPack = $$Array.map((function (card) {
                  if (card.shuffleIndex === 13) {
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
                  pack: myPack,
                  handVisible: state.handVisible,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers
                };
      case /* Sync */2 :
          return window.gameState;
      
    }
  } else {
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
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers
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
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers
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
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers
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
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers
                };
      
    }
  }
}

exports.initialState = initialState;
exports.reducer = reducer;
/* No side effect */
