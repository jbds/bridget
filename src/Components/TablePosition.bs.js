'use strict';

var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");

function TablePosition(Props) {
  var arr = Props.arr;
  var dispatch = Props.dispatch;
  console.log(arr);
  return React.createElement(React.Fragment, undefined, React.createElement("table", {
                  style: {
                    border: "1px solid #26653B",
                    borderCollapse: "collapse",
                    color: "#26653B",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.5vh",
                    margin: "auto",
                    padding: "0px",
                    textAlign: "center",
                    whiteSpace: "nowrap",
                    width: "30vh"
                  }
                }, React.createElement("tbody", undefined, React.createElement("tr", undefined, React.createElement("td", {
                              style: {
                                textAlign: "center",
                                whiteSpace: "nowrap"
                              }
                            }, "Table Position"), React.createElement("td", {
                              style: {
                                textAlign: "center"
                              }
                            }, "Player")), Belt_Array.map(arr, (function (x) {
                            return React.createElement("tr", {
                                        key: x.player
                                      }, React.createElement("td", undefined, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                dispatch: dispatch,
                                                action: /* Test */3,
                                                label: "N",
                                                id: "btnN" + x.player
                                              }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                dispatch: dispatch,
                                                action: /* Test */3,
                                                label: "S",
                                                id: "btnS" + x.player
                                              }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                dispatch: dispatch,
                                                action: /* Test */3,
                                                label: "W",
                                                id: "btnW" + x.player
                                              }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                dispatch: dispatch,
                                                action: /* Test */3,
                                                label: "E",
                                                id: "btnE" + x.player
                                              })), React.createElement("td", undefined, "x" + x.player));
                          })))));
}

var make = TablePosition;

exports.make = make;
/* react Not a pure module */
