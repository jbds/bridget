'use strict';

var React = require("react");
var Global$ReasonReactExamples = require("../Global.bs.js");
var SpanStd$ReasonReactExamples = require("./SpanStd.bs.js");
var FlipHand$ReasonReactExamples = require("./FlipHand.bs.js");
var InputStd$ReasonReactExamples = require("./InputStd.bs.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");
var ButtonStdJsx$ReasonReactExamples = require("./ButtonStdJsx.bs.js");

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
    
  };
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  id: "sidebar1"
                }, React.createElement("br", undefined), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spanLabel1",
                      text: "My username: "
                    }), React.createElement(InputStd$ReasonReactExamples.make, {
                      id: "txtMyLoginName"
                    }), " ", React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Login",
                      id: "btnLogin",
                      onClick: handlerBtnLogin
                    }), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Shuffle */0,
                      label: "Shuffle",
                      id: "btnShuffle"
                    })), React.createElement("div", {
                  id: "sidebar2"
                }, "Sidebar2", React.createElement("br", undefined), React.createElement("button", {
                      id: "btn2"
                    }, "Test ReasonML"), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Discard */1,
                      label: "Discard",
                      id: "btnDiscard"
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Sync */2,
                      label: "Sync state with gameState",
                      id: "btnSync"
                    })), React.createElement("div", {
                  id: "sidebar3"
                }, "Sidebar3", React.createElement("br", undefined), React.createElement("span", {
                      id: "span1"
                    }), React.createElement(FlipHand$ReasonReactExamples.make, {
                      dispatch: dispatch
                    }), React.createElement("br", undefined), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Rotate table",
                      id: "btnRotateTable",
                      onClick: handlerBtnRotateTable
                    }), React.createElement("br", undefined)), React.createElement("div", {
                  id: "biddingWindow"
                }, "TEST"));
}

var make = Sidebar;

exports.make = make;
/* react Not a pure module */
