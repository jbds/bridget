'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Shuffle$ReasonReactExamples = require("./Shuffle.bs.js");

var initialState = {
  pack: Shuffle$ReasonReactExamples.initialPack,
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  dealer: undefined,
  cardsDealtCount: 0
};

function reducer(state, action) {
  if (typeof action === "number") {
    if (action === /* Shuffle */0) {
      return Shuffle$ReasonReactExamples.shufflePack(undefined);
    }
    var myPack = $$Array.map((function (card) {
            if (card.shuffleIndex === 13) {
              return {
                      noTrumpValue: card.noTrumpValue,
                      handOrder: card.handOrder,
                      shuffleIndex: card.shuffleIndex,
                      rank: card.rank,
                      suit: card.suit,
                      fileName: card.fileName,
                      lifecycle: /* Discard */1
                    };
            } else {
              return card;
            }
          }), state.pack);
    return {
            pack: myPack,
            handVisible: state.handVisible,
            dealer: state.dealer,
            cardsDealtCount: state.cardsDealtCount
          };
  } else if (action.tag) {
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
                  dealer: state.dealer,
                  cardsDealtCount: state.cardsDealtCount
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
                  dealer: state.dealer,
                  cardsDealtCount: state.cardsDealtCount
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
                  dealer: state.dealer,
                  cardsDealtCount: state.cardsDealtCount
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
                  dealer: state.dealer,
                  cardsDealtCount: state.cardsDealtCount
                };
      
    }
  } else {
    switch (action[0]) {
      case "E" :
          return {
                  pack: state.pack,
                  handVisible: state.handVisible,
                  dealer: /* East */1,
                  cardsDealtCount: state.cardsDealtCount
                };
      case "N" :
          return {
                  pack: state.pack,
                  handVisible: state.handVisible,
                  dealer: /* North */0,
                  cardsDealtCount: state.cardsDealtCount
                };
      case "S" :
          return {
                  pack: state.pack,
                  handVisible: state.handVisible,
                  dealer: /* South */2,
                  cardsDealtCount: state.cardsDealtCount
                };
      case "W" :
          return {
                  pack: state.pack,
                  handVisible: state.handVisible,
                  dealer: /* West */3,
                  cardsDealtCount: state.cardsDealtCount
                };
      default:
        return {
                pack: state.pack,
                handVisible: state.handVisible,
                dealer: undefined,
                cardsDealtCount: state.cardsDealtCount
              };
    }
  }
}

exports.initialState = initialState;
exports.reducer = reducer;
/* No side effect */
