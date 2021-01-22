'use strict';

var React = require("react");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Global$ReasonReactExamples = require("../Global.bs.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");
var SpanStd$ReasonReactExamples = require("./SpanStd.bs.js");
var BidTable$ReasonReactExamples = require("./BidTable.bs.js");
var InputStd$ReasonReactExamples = require("./InputStd.bs.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");
var ButtonStdJsx$ReasonReactExamples = require("./ButtonStdJsx.bs.js");
var BiddingWindow$ReasonReactExamples = require("./BiddingWindow.bs.js");
var TablePosition$ReasonReactExamples = require("./TablePosition.bs.js");
var ChicagoScoreTable$ReasonReactExamples = require("./ChicagoScoreTable.bs.js");

const Online = require('../Online.bs');
;

function App(Props) {
  var match = React.useReducer(Global$ReasonReactExamples.reducer, Global$ReasonReactExamples.initialState);
  var dispatch = match[1];
  var state = match[0];
  console.log(state);
  ((window.gameState = match[0]));
  ((!window.isLastActionSync
    ?
    Online.doMessage(gameState)
    :
    //console.log('Action-Sync: doMessage suppressed')
    null));
  var handlerBtnRotateTable = function (_e) {
    ((window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)));
    
  };
  var handlerBtnLogin = function (_e) {
    ((userState.player = (document.getElementById('txtMyLoginName').value).toUpperCase()));
    ((localStorage.setItem(
                      'myLoginName',
                      userState.player
                    )));
    ((setTimeout(function(){
        //alert('rotate?');
        // after the delay, we can be certain that the player has been added
        // but we do not know if a poc has been previously assigned and remembered
        let arrObj = gameState.pointOfCompassAndPlayers.find(el => el.player === userState.player);
        // force the player to be at 6PM
        if (arrObj.pointOfCompass === 'South') {
          window.userState.tableRotationDegrees = 0;
        } else if (arrObj.pointOfCompass === 'East') {
          window.userState.tableRotationDegrees = 90;
        } else if (arrObj.pointOfCompass === 'North') {
          window.userState.tableRotationDegrees = 180;
        } else if (arrObj.pointOfCompass === 'West') {
          window.userState.tableRotationDegrees = 270;
        } else {
          // do nothing
        }
      }, 1500)));
    ((Online.doLogin(userState.player)));
    
  };
  var handlerBtnLogout = function (_e) {
    ((Online.doLogout((document.getElementById('txtMyLoginName').value).toUpperCase())));
    ((location.reload()));
    
  };
  var handlerBtnUndo = function (_e) {
    ((Online.doMessage('Undo')));
    
  };
  var handlerBtnReboot2 = function (_e) {
    console.log("btnReboot2 clicked");
    var bln = (window.confirm('Are you sure you want to DELETE ALL SCORES and start afresh?'));
    if (bln) {
      ((Online.doMessage('Reboot')));
    }
    
  };
  var handlerBtnReviewDeal = function (_e) {
    console.log("btnReviewDeal clicked");
    ((Online.doMessage('ReviewDeal')));
    
  };
  var isFourSeatsOccupied = function (param) {
    var myShorterArray = Belt_Array.keep(state.pointOfCompassAndPlayers, (function (x) {
            if (x.pointOfCompass !== "") {
              return x.pointOfCompass !== "Observer";
            } else {
              return false;
            }
          }));
    return myShorterArray.length === 4;
  };
  var isDealButtonVisible = function (param) {
    var localPlayer = window.userState.player;
    var userPointOfCompassWrappedInArray = Belt_Array.keep(state.pointOfCompassAndPlayers, (function (obj) {
            if (obj.player === localPlayer) {
              return obj.pointOfCompass === Shuffle$ReasonReactExamples.pocAsString(state.dealer);
            } else {
              return false;
            }
          }));
    if (userPointOfCompassWrappedInArray.length === 0 || !(isFourSeatsOccupied(undefined) && state.lastAction !== "4 Passes - so fresh cards dealt")) {
      return false;
    } else if (state.pack.length === 0) {
      return true;
    } else {
      return state.discardIndex === 51;
    }
  };
  var isUndoVisible = function (param) {
    var localPlayer = window.userState.player;
    var userPointOfCompassWrappedInArray = Belt_Array.keep(state.pointOfCompassAndPlayers, (function (obj) {
            return obj.player === localPlayer;
          }));
    return userPointOfCompassWrappedInArray.length !== 0;
  };
  var isBiddingWindowVisible = function (param) {
    if (!(state.isBiddingCycle === true && state.pointOfCompassAndPlayers.length >= 4)) {
      return false;
    }
    var localPlayer = window.userState.player;
    var userPointOfCompassWrappedInArray = Belt_Array.keep(state.pointOfCompassAndPlayers, (function (obj) {
            return obj.player === localPlayer;
          }));
    if (userPointOfCompassWrappedInArray.length === 0) {
      return false;
    }
    var userPointOfCompass = Caml_array.caml_array_get(userPointOfCompassWrappedInArray, 0).pointOfCompass;
    if (Caml_obj.caml_equal(state.activePointOfCompass, userPointOfCompass)) {
      return true;
    } else {
      return false;
    }
  };
  var isQtyCardsInHandsDivFour = function (param) {
    var lifecycleHandCardsArray = Belt_Array.keep(state.pack, (function (x) {
            return x.lifecycle === /* Hand */1;
          }));
    return lifecycleHandCardsArray.length % 4 === 0;
  };
  var isQtyCardsInDiscardZero = function (param) {
    var lifecycleDiscardCardsArray = Belt_Array.keep(state.pack, (function (x) {
            return x.lifecycle === /* Discard */2;
          }));
    return lifecycleDiscardCardsArray.length === 0;
  };
  var isQtyCardsInHandGT0LTE16 = function (param) {
    var lifecycleHandCardsArray = Belt_Array.keep(state.pack, (function (x) {
            return x.lifecycle === /* Hand */1;
          }));
    if (lifecycleHandCardsArray.length <= 16) {
      return lifecycleHandCardsArray.length !== 0;
    } else {
      return false;
    }
  };
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  id: "sidebar1"
                }, React.createElement("br", undefined), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn1",
                      text: "Me: "
                    }), React.createElement(InputStd$ReasonReactExamples.make, {
                      id: "txtMyLoginName"
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn2",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Join",
                      id: "btnLogin",
                      onClick: handlerBtnLogin
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn3",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Leave",
                      id: "btnLogout",
                      onClick: handlerBtnLogout
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn4",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Restart",
                      id: "btnReboot2",
                      onClick: handlerBtnReboot2,
                      isWasteOfSpace: !state.isRebootVisible
                    }), React.createElement("br", undefined), React.createElement(TablePosition$ReasonReactExamples.make, {
                      state: state,
                      dispatch: dispatch
                    }), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Shuffle */0,
                      label: "My Deal",
                      id: "btnShuffle",
                      isWasteOfSpace: !isDealButtonVisible(undefined)
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn5",
                      text: "\u200A"
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "\u27F3",
                      id: "btnRotateTable",
                      onClick: handlerBtnRotateTable,
                      isWasteOfSpace: !isFourSeatsOccupied(undefined)
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn6",
                      text: "\u200A"
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Undo",
                      id: "btnUndo",
                      onClick: handlerBtnUndo,
                      isWasteOfSpace: !isUndoVisible(undefined)
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn7",
                      text: "\u200A"
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Concede */8,
                      label: "\uD83C\uDFC1",
                      id: "btnConcede",
                      isWasteOfSpace: !(isQtyCardsInHandsDivFour(undefined) && isQtyCardsInDiscardZero(undefined) && isQtyCardsInHandGT0LTE16(undefined) && isFourSeatsOccupied(undefined))
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn8",
                      text: "\u200A"
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Review",
                      id: "btnReviewDeal",
                      onClick: handlerBtnReviewDeal,
                      isWasteOfSpace: !state.isReviewDealVisible
                    })), React.createElement("div", {
                  id: "sidebar2"
                }, React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* EndOneTrick */7,
                      label: "End One Trick",
                      id: "btnEndTrick",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* PostDiscard */2,
                      label: "Post Discard",
                      id: "btnPostDiscard",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Discard */1,
                      label: "Discard",
                      id: "btnDiscard",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Sync */3,
                      label: "Sync state with gameState",
                      id: "btnSync",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* LoginSync */4,
                      label: "Login sync with server",
                      id: "btnLoginSync",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* PostBid */6,
                      label: "Post Bid",
                      id: "btnPostBid",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Post4Passes */9,
                      label: "Post 4 Passes",
                      id: "btnPost4Passes",
                      isVisible: false
                    }), React.createElement(ChicagoScoreTable$ReasonReactExamples.make, {
                      state: state
                    })), React.createElement("div", {
                  id: "sidebar3"
                }, React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnRandomInt",
                      text: "Last action:",
                      fontSize: "1.5vh"
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnRILA",
                      text: " ",
                      fontSize: "1.5vh"
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnLastAction",
                      text: state.lastAction,
                      isWarning: state.lastAction === "Logout or Server Down",
                      fontSize: "1.5vh"
                    })), React.createElement("div", {
                  id: "bidTable",
                  style: {
                    padding: "1vh 0vh 0vh 0vh",
                    borderRadius: "5px"
                  }
                }, React.createElement(BidTable$ReasonReactExamples.make, {
                      state: state
                    })), React.createElement("div", {
                  id: "biddingWindow",
                  style: {
                    display: isBiddingWindowVisible(undefined) ? "inline" : "none",
                    padding: "1vh 1vh 1vh 3vh",
                    borderRadius: "10px"
                  }
                }, React.createElement(BiddingWindow$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      state: state
                    })));
}

var make = App;

exports.make = make;
/*  Not a pure module */
