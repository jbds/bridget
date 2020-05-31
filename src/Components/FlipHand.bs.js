'use strict';

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
                                  action: /* Flip */[/* North */0],
                                  label: "North",
                                  id: "btnNorth"
                                })), React.createElement("td", undefined, " ")), React.createElement("tr", undefined, React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                  dispatch: dispatch,
                                  action: /* Flip */[/* West */3],
                                  label: "West",
                                  id: "btnWest"
                                })), React.createElement("td", undefined, "< Flip >"), React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                  dispatch: dispatch,
                                  action: /* Flip */[/* East */1],
                                  label: "East",
                                  id: "btnEast"
                                }))), React.createElement("tr", undefined, React.createElement("td", undefined, " "), React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                  dispatch: dispatch,
                                  action: /* Flip */[/* South */2],
                                  label: "South",
                                  id: "btnSouth"
                                })), React.createElement("td", undefined, " ")))));
}

var make = FlipHand;

exports.make = make;
/* react Not a pure module */
