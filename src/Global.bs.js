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
  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
  isBiddingCycle: false,
  isBiddingHideDenominationButtons: true,
  isDummyVisible: false,
  isRebootVisible: false,
  lastAction: "None (initialState from Client)",
  pack: initialState_pack,
  pointOfCompassAndPlayers: initialState_pointOfCompassAndPlayers,
  randomInt: 1
};

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* NewGame */0 :
          ((window.isLastActionSync = false));
          return {
                  activePointOfCompass: undefined,
                  bids: /* [] */0,
                  chicagoScoreSheet: /* [] */0,
                  dealer: undefined,
                  dealIndex: -1,
                  declarer: undefined,
                  handVisible: Shuffle$ReasonReactExamples.initialHandVisible,
                  isBiddingCycle: false,
                  isBiddingHideDenominationButtons: true,
                  isDummyVisible: false,
                  isRebootVisible: true,
                  lastAction: "Reboot (clears scores & logins)",
                  pack: [],
                  pointOfCompassAndPlayers: [],
                  randomInt: 2
                };
      case /* Shuffle */1 :
          ((window.isLastActionSync = false));
          return {
                  activePointOfCompass: state.dealer,
                  bids: /* [] */0,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: undefined,
                  handVisible: state.handVisible,
                  isBiddingCycle: true,
                  isBiddingHideDenominationButtons: true,
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
                  lastAction: "Deal",
                  pack: Shuffle$ReasonReactExamples.getShuffledPack(undefined),
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* Discard */2 :
          ((window.isLastActionSync = false));
          var discardFileName = window.discardFileName;
          var cardWrappedInArray = Belt_Array.keep(state.pack, (function (x) {
                  return x.fileName === discardFileName;
                }));
          var cardShuffleIndex = Caml_array.caml_array_get(cardWrappedInArray, 0).shuffleIndex;
          var discardPoc = cardShuffleIndex < 13 ? "North" : (
              cardShuffleIndex < 26 ? "East" : (
                  cardShuffleIndex < 39 ? "South" : "West"
                )
            );
          console.log("discardPoc:");
          console.log(discardPoc);
          var pocFollowingDeclarer = Caml_obj.caml_equal(state.declarer, "North") ? "East" : (
              Caml_obj.caml_equal(state.declarer, "East") ? "South" : (
                  Caml_obj.caml_equal(state.declarer, "South") ? "West" : (
                      Caml_obj.caml_equal(state.declarer, "West") ? "North" : ""
                    )
                )
            );
          console.log("pocFollowingDeclarer:");
          console.log(pocFollowingDeclarer);
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
                  isDummyVisible: discardPoc === pocFollowingDeclarer ? true : state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
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
                  chicagoScoreSheet: /* [] */0,
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
                  isDummyVisible: false,
                  isRebootVisible: false,
                  lastAction: "Logout or Server Down",
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
          var poc = window.gameState.activePointOfCompass;
          var bids = window.gameState.bids;
          var isBiddingHideDenominationButtons = window.gameState.isBiddingHideDenominationButtons;
          var isRebootVisible = window.gameState.isRebootVisible;
          var isDummyVisible = window.gameState.isDummyVisible;
          return {
                  activePointOfCompass: poc,
                  bids: bids,
                  chicagoScoreSheet: cSS,
                  dealer: dealer,
                  dealIndex: dealIndex,
                  declarer: declarer,
                  handVisible: hV,
                  isBiddingCycle: isBiddingCycle,
                  isBiddingHideDenominationButtons: isBiddingHideDenominationButtons,
                  isDummyVisible: isDummyVisible,
                  isRebootVisible: isRebootVisible,
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
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
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
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
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
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
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
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
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
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
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
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
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
                      isRedoubled: false,
                      isPass: false
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
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
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
          var poc$1 = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.activePointOfCompass);
          return {
                  activePointOfCompass: poc$1,
                  bids: bidsUpdated,
                  chicagoScoreSheet: state.chicagoScoreSheet,
                  dealer: state.dealer,
                  dealIndex: state.dealIndex,
                  declarer: state.declarer,
                  handVisible: state.handVisible,
                  isBiddingCycle: state.isBiddingCycle,
                  isBiddingHideDenominationButtons: true,
                  isDummyVisible: state.isDummyVisible,
                  isRebootVisible: state.isRebootVisible,
                  lastAction: "BidUpdate",
                  pack: state.pack,
                  pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                  randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                };
      case /* BidAddSpecial */4 :
          var special = action[0];
          console.log("Action - BidAddSpecial");
          ((window.isLastActionSync = false));
          var poc$2 = Shuffle$ReasonReactExamples.getNextPointOfCompass(state.activePointOfCompass);
          if (special === undefined) {
            return state;
          }
          switch (special) {
            case "Pass" :
                var bidsLength = List.length(state.bids);
                if (bidsLength < 3) {
                  return {
                          activePointOfCompass: poc$2,
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
                          handVisible: state.handVisible,
                          isBiddingCycle: state.isBiddingCycle,
                          isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                          isDummyVisible: state.isDummyVisible,
                          isRebootVisible: state.isRebootVisible,
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
                          activePointOfCompass: poc$2,
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
                          handVisible: state.handVisible,
                          isBiddingCycle: state.isBiddingCycle,
                          isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                          isDummyVisible: state.isDummyVisible,
                          isRebootVisible: state.isRebootVisible,
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
                var bidRecordOfInterest1 = List.hd(List.tl(tl));
                var contractLevel = bidRecordOfInterest1.contractLevel;
                var contractSuit = bidRecordOfInterest1.contractSuit;
                var contractPoc = bidRecordOfInterest1.contractPointOfCompass;
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
                var chicagoScoreSheetRecord = {
                  vulnerable: vulnerable,
                  contractLevel: contractLevel,
                  contractSuit: contractSuit,
                  contractDeclarer: contractDeclarer,
                  totalTricks: 0,
                  scoreNorthSouth: undefined,
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
                        handVisible: state.handVisible,
                        isBiddingCycle: false,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        lastAction: contractLevel !== undefined ? "BidAddSpecial- 3 Passes" : "BidAddSpecial- 4 Passes",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            case "X" :
                return {
                        activePointOfCompass: state.activePointOfCompass,
                        bids: /* :: */[
                          {
                            contractLevel: undefined,
                            contractSuit: undefined,
                            contractPointOfCompass: state.activePointOfCompass,
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
                        handVisible: state.handVisible,
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
                        lastAction: "BidAddSpecial",
                        pack: state.pack,
                        pointOfCompassAndPlayers: state.pointOfCompassAndPlayers,
                        randomInt: Shuffle$ReasonReactExamples.impureGetTimeBasedSeedUpTo60k(undefined)
                      };
            case "XX" :
                return {
                        activePointOfCompass: state.activePointOfCompass,
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
                        handVisible: state.handVisible,
                        isBiddingCycle: state.isBiddingCycle,
                        isBiddingHideDenominationButtons: state.isBiddingHideDenominationButtons,
                        isDummyVisible: state.isDummyVisible,
                        isRebootVisible: state.isRebootVisible,
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
