'use strict';

var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");
var ButtonObserver$ReasonReactExamples = require("./ButtonObserver.bs.js");

function TablePosition(Props) {
  var state = Props.state;
  var dispatch = Props.dispatch;
  if (state.pointOfCompassAndPlayers.length === 0) {
    return null;
  } else {
    return React.createElement(React.Fragment, undefined, React.createElement("table", {
                    style: {
                      border: "1px solid #800000",
                      borderCollapse: "collapse",
                      color: "#404040",
                      fontFamily: "Trebuchet MS",
                      fontSize: "1.9vh",
                      margin: "auto",
                      padding: "0px",
                      textAlign: "center",
                      whiteSpace: "nowrap",
                      width: "30vh"
                    }
                  }, React.createElement("tbody", undefined, React.createElement("tr", undefined, React.createElement("td", {
                                style: {
                                  backgroundColor: "#f8f8f8",
                                  border: "1px solid #f8f8f8",
                                  borderCollapse: "collapse",
                                  fontSize: "1.5vh",
                                  textAlign: "center",
                                  whiteSpace: "nowrap"
                                },
                                colSpan: 2
                              }, "-------------- Table Seating --------------")), Belt_Array.map(state.pointOfCompassAndPlayers, (function (x) {
                              return React.createElement("tr", {
                                          key: x.player
                                        }, React.createElement("td", {
                                              style: {
                                                border: "1px solid #f8f8f8",
                                                borderCollapse: "collapse",
                                                textAlign: "right"
                                              }
                                            }, x.player), React.createElement("td", {
                                              style: {
                                                border: "1px solid #f8f8f8",
                                                borderCollapse: "collapse"
                                              }
                                            }, React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                  dispatch: dispatch,
                                                  action: /* AssignPlayer */Block.__(1, [{
                                                        pointOfCompass: x.pointOfCompass === "West" ? "" : "West",
                                                        player: x.player
                                                      }]),
                                                  label: "W",
                                                  id: "btnW" + x.player,
                                                  isActive: x.pointOfCompass === "West",
                                                  color: "#404040"
                                                }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                  dispatch: dispatch,
                                                  action: /* AssignPlayer */Block.__(1, [{
                                                        pointOfCompass: x.pointOfCompass === "North" ? "" : "North",
                                                        player: x.player
                                                      }]),
                                                  label: "N",
                                                  id: "btnN" + x.player,
                                                  isActive: x.pointOfCompass === "North",
                                                  color: "#404040"
                                                }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                  dispatch: dispatch,
                                                  action: /* AssignPlayer */Block.__(1, [{
                                                        pointOfCompass: x.pointOfCompass === "East" ? "" : "East",
                                                        player: x.player
                                                      }]),
                                                  label: "E",
                                                  id: "btnE" + x.player,
                                                  isActive: x.pointOfCompass === "East",
                                                  color: "#404040"
                                                }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                                                  dispatch: dispatch,
                                                  action: /* AssignPlayer */Block.__(1, [{
                                                        pointOfCompass: x.pointOfCompass === "South" ? "" : "South",
                                                        player: x.player
                                                      }]),
                                                  label: "S",
                                                  id: "btnS" + x.player,
                                                  isActive: x.pointOfCompass === "South",
                                                  color: "#404040"
                                                }), React.createElement(ButtonObserver$ReasonReactExamples.make, {
                                                  dispatch: dispatch,
                                                  action: /* AssignPlayer */Block.__(1, [{
                                                        pointOfCompass: x.pointOfCompass === "Observer" ? "" : "Observer",
                                                        player: x.player
                                                      }]),
                                                  label: "_",
                                                  id: "btnO" + x.player,
                                                  isActive: x.pointOfCompass === "Observer"
                                                })));
                            })))));
  }
}

var make = TablePosition;

exports.make = make;
/* react Not a pure module */
