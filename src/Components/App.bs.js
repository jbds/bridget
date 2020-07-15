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
    ((Online.doLogin(userState.player)));
    
  };
  var handlerBtnLogout = function (_e) {
    ((window.userState.player = '?'));
    ((Online.doLogout((document.getElementById('txtMyLoginName').value).toUpperCase())));
    
  };
  var handlerBtnUndo = function (_e) {
    ((Online.doMessage('Undo')));
    
  };
  var handlerBtnReboot2 = function (_e) {
    console.log("btnReboot2 clicked");
    ((Online.doMessage('Reboot')));
    
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
    if (userPointOfCompassWrappedInArray.length === 0 || !isFourSeatsOccupied(undefined)) {
      return false;
    } else {
      return true;
    }
  };
  var isUndoVisible = function (param) {
    var localPlayer = window.userState.player;
    var userPointOfCompassWrappedInArray = Belt_Array.keep(state.pointOfCompassAndPlayers, (function (obj) {
            if (obj.player === localPlayer) {
              return obj.pointOfCompass !== "";
            } else {
              return false;
            }
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
                      label: "Login",
                      id: "btnLogin",
                      onClick: handlerBtnLogin
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn2",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Logout",
                      id: "btnLogout",
                      onClick: handlerBtnLogout
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn2",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Reboot",
                      id: "btnReboot2",
                      onClick: handlerBtnReboot2,
                      isWasteOfSpace: !state.isRebootVisible
                    }), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement(TablePosition$ReasonReactExamples.make, {
                      state: state,
                      dispatch: dispatch
                    }), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Shuffle */0,
                      label: "My Deal",
                      id: "btnShuffle",
                      isWasteOfSpace: !isDealButtonVisible(undefined)
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn2",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Rotate my table",
                      id: "btnRotateTable",
                      onClick: handlerBtnRotateTable,
                      isWasteOfSpace: !isFourSeatsOccupied(undefined)
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn2",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Undo",
                      id: "btnUndo",
                      onClick: handlerBtnUndo,
                      isWasteOfSpace: !isUndoVisible(undefined)
                    })), React.createElement("div", {
                  id: "sidebar2"
                }, React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* EndTrick */5,
                      label: "End Trick",
                      id: "btnEndTrick",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Discard */1,
                      label: "Discard",
                      id: "btnDiscard",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Sync */2,
                      label: "Sync state with gameState",
                      id: "btnSync",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* LoginSync */3,
                      label: "Login sync with server",
                      id: "btnLoginSync",
                      isVisible: false
                    }), React.createElement(ChicagoScoreTable$ReasonReactExamples.make, {
                      state: state
                    })), React.createElement("div", {
                  id: "sidebar3"
                }, React.createElement("br", undefined), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnRandomInt",
                      text: "Last action:"
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnRILA",
                      text: " "
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnLastAction",
                      text: state.lastAction,
                      isWarning: state.lastAction === "Logout or Server Down"
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
