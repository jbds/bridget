'use strict';

var React = require("react");
var Global$ReasonReactExamples = require("../Global.bs.js");
var FlipHand$ReasonReactExamples = require("./FlipHand.bs.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");
var ButtonStdJsx$ReasonReactExamples = require("./ButtonStdJsx.bs.js");

function Sidebar(Props) {
  var match = React.useReducer(Global$ReasonReactExamples.reducer, Global$ReasonReactExamples.initialState);
  var dispatch = match[1];
  ((window.gameState = match[0]));
  var handlerBtnRotateTable = function (_e) {
    ((window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)));
    
  };
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  id: "sidebar1"
                }, "Sidebar1", React.createElement("br", undefined), React.createElement("button", {
                      id: "btn1"
                    }, "Test P5"), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
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
                    }), React.createElement("br", undefined)));
}

var make = Sidebar;

exports.make = make;
/* react Not a pure module */
