'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

var initialState_locationAndPlayers = [];

var initialState = {
  pack: Shuffle$ReasonReactExamples.initialPack,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  locationAndPlayers: initialState_locationAndPlayers
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
                  locationAndPlayers: state.locationAndPlayers
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
                  locationAndPlayers: state.locationAndPlayers
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
                  locationAndPlayers: state.locationAndPlayers
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
                  locationAndPlayers: state.locationAndPlayers
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
                  locationAndPlayers: state.locationAndPlayers
                };
      
    }
  }
}

exports.initialState = initialState;
exports.reducer = reducer;
/* No side effect */
