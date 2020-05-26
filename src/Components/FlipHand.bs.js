'use strict';

var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");

function FlipHand(Props) {
  var dispatch = Props.dispatch;
  return React.createElement(React.Fragment, undefined, React.createElement("table", {
                  style: {
                    borderCollapse: "collapse",
                    color: "#404040",
                    fontSize: "2.5vh",
                    margin: "auto",
                    padding: "0px"
                  }
                }, React.createElement("tbody", undefined, React.createElement("tr", undefined, React.createElement("td", undefined, " "), React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                  dispatch: dispatch,
                                  action: /* Flip */Block.__(1, [/* North */0]),
                                  label: "North"
                                })), React.createElement("td", undefined, " ")), React.createElement("tr", undefined, React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                  dispatch: dispatch,
                                  action: /* Flip */Block.__(1, [/* West */3]),
                                  label: "West"
                                })), React.createElement("td", undefined, "< Flip >"), React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                  dispatch: dispatch,
                                  action: /* Flip */Block.__(1, [/* East */1]),
                                  label: "East"
                                }))), React.createElement("tr", undefined, React.createElement("td", undefined, " "), React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                  dispatch: dispatch,
                                  action: /* Flip */Block.__(1, [/* South */2]),
                                  label: "South"
                                })), React.createElement("td", undefined, " ")))));
}

var make = FlipHand;

exports.make = make;
/* react Not a pure module */
