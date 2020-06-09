'use strict';

var React = require("react");
var Global$ReasonReactExamples = require("../Global.bs.js");
var SpanStd$ReasonReactExamples = require("./SpanStd.bs.js");
var InputStd$ReasonReactExamples = require("./InputStd.bs.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");
var ButtonStdJsx$ReasonReactExamples = require("./ButtonStdJsx.bs.js");
var TablePosition$ReasonReactExamples = require("./TablePosition.bs.js");

const Online = require('../Online.bs');
;

function Sidebar(Props) {
  var match = React.useReducer(Global$ReasonReactExamples.reducer, Global$ReasonReactExamples.initialState);
  var dispatch = match[1];
  ((window.gameState = match[0]));
  var handlerBtnRotateTable = function (_e) {
    ((window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)));
    
  };
  var handlerBtnLogin = function (_e) {
    ((localStorage.setItem(
                      'myLoginName',
                      document.getElementById('txtMyLoginName').value
                    )));
    ((window.userState.player = document.getElementById('txtMyLoginName').value));
    ((Online.doLogin(document.getElementById('txtMyLoginName').value)));
    
  };
  var handlerBtnLogout = function (_e) {
    console.log("btnLogout clicked");
    ((window.userState.player = '?'));
    ((Online.doLogout(document.getElementById('txtMyLoginName').value)));
    
  };
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  id: "sidebar1"
                }, React.createElement("br", undefined), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn1",
                      text: "Player: "
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
                    }), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement(TablePosition$ReasonReactExamples.make, {
                      state: match[0],
                      dispatch: dispatch
                    })), React.createElement("div", {
                  id: "sidebar2"
                }, React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
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
                    }), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Shuffle */0,
                      label: "Shuffle",
                      id: "btnShuffle"
                    })), React.createElement("div", {
                  id: "sidebar3"
                }, React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Rotate table",
                      id: "btnRotateTable",
                      onClick: handlerBtnRotateTable
                    }), React.createElement("br", undefined)), React.createElement("div", {
                  id: "biddingWindow"
                }, "TEST"));
}

var make = Sidebar;

exports.make = make;
/*  Not a pure module */
