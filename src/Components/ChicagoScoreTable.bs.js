'use strict';

var List = require("bs-platform/lib/js/list.js");
var React = require("react");
var $$String = require("bs-platform/lib/js/string.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");

function ChicagoScoreTable(Props) {
  var state = Props.state;
  if (List.length(state.chicagoScoreSheet) === 0) {
    return null;
  } else {
    return React.createElement(React.Fragment, undefined, React.createElement("table", {
                    style: {
                      color: "#26653B",
                      fontFamily: "Trebuchet MS",
                      fontSize: "2.0vh",
                      margin: "auto",
                      textAlign: "center"
                    }
                  }, React.createElement("thead", undefined), React.createElement("tbody", undefined, React.createElement("tr", {
                            style: {
                              backgroundColor: "#f8f8f8"
                            }
                          }, React.createElement("td", {
                                style: {
                                  padding: "1vh 1vh 1vh 1vh"
                                }
                              }, "Vuln"), React.createElement("td", {
                                style: {
                                  padding: "1vh 1vh 1vh 1vh"
                                }
                              }, "Decl"), React.createElement("td", {
                                style: {
                                  padding: "1vh 2vh 1vh 2vh"
                                }
                              }, "Bid"), React.createElement("td", {
                                style: {
                                  padding: "1vh 1vh 1vh 1vh"
                                }
                              }, "Tricks"), React.createElement("td", {
                                style: {
                                  padding: "1vh 2vh 1vh 2vh"
                                }
                              }, "N-S"), React.createElement("td", {
                                style: {
                                  padding: "1vh 2vh 1vh 2vh"
                                }
                              }, "E-W")), Belt_Array.map(Belt_List.toArray(state.chicagoScoreSheet), (function (x) {
                              return React.createElement("tr", {
                                          key: x.vulnerable,
                                          style: {
                                            backgroundColor: "white"
                                          }
                                        }, React.createElement("td", undefined, x.vulnerable), React.createElement("td", undefined, $$String.sub(Shuffle$ReasonReactExamples.pocAsString(x.contractDeclarer), 0, 1)), React.createElement("td", undefined, Shuffle$ReasonReactExamples.optionIntAsString(x.contractLevel)), React.createElement("td", undefined, String(x.totalTricks)), React.createElement("td", undefined, Shuffle$ReasonReactExamples.optionIntAsString(x.scoreNorthSouth)), React.createElement("td", undefined, Shuffle$ReasonReactExamples.optionIntAsString(x.scoreWestEast)));
                            })))));
  }
}

var make = ChicagoScoreTable;

exports.make = make;
/* react Not a pure module */
