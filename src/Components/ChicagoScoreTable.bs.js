'use strict';

var List = require("bs-platform/lib/js/list.js");
var React = require("react");
var Random = require("bs-platform/lib/js/random.js");
var $$String = require("bs-platform/lib/js/string.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Shuffle$ReasonReactExamples = require("../Shuffle.bs.js");
var ChicagoBidTableCell$ReasonReactExamples = require("./ChicagoBidTableCell.bs.js");

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
                              backgroundColor: "#f8f8f8",
                              color: "#000000"
                            }
                          }, React.createElement("td", {
                                style: {
                                  padding: "1vh 1vh 1vh 1vh"
                                }
                              }, "Vuln"), React.createElement("td", {
                                style: {
                                  padding: "1vh 0.5vh 1vh 0.5vh"
                                }
                              }, "Decl"), React.createElement("td", {
                                style: {
                                  padding: "1vh 1.5vh 1vh 1.5vh"
                                }
                              }, "Bid"), React.createElement("td", {
                                style: {
                                  padding: "1vh 0vh 1vh 0vh",
                                  width: "6.5vh"
                                }
                              }, "NS Tricks"), React.createElement("td", {
                                style: {
                                  padding: "1vh 0vh 1vh 0vh",
                                  width: "6.5vh"
                                }
                              }, "NS Score"), React.createElement("td", {
                                style: {
                                  padding: "1vh 0vh 1vh 0vh",
                                  width: "6.5vh"
                                }
                              }, "EW Tricks"), React.createElement("td", {
                                style: {
                                  padding: "1vh 0vh 1vh 0vh",
                                  width: "6.5vh"
                                }
                              }, "EW Score")), Belt_Array.map(Belt_List.toArray(Belt_List.reverse(state.chicagoScoreSheet)), (function (x) {
                              var match = x.contractSuit;
                              var denominationValue;
                              if (match !== undefined) {
                                switch (match) {
                                  case "Clubs" :
                                      denominationValue = "\u2663";
                                      break;
                                  case "Diamonds" :
                                      denominationValue = "\u2666";
                                      break;
                                  case "Hearts" :
                                      denominationValue = "\u2665";
                                      break;
                                  case "NoTrumps" :
                                      denominationValue = "";
                                      break;
                                  case "Spades" :
                                      denominationValue = "\u2660";
                                      break;
                                  default:
                                    denominationValue = "Error";
                                }
                              } else {
                                denominationValue = "";
                              }
                              var match$1 = x.contractSuit;
                              var denominationColor;
                              if (match$1 !== undefined) {
                                switch (match$1) {
                                  case "Diamonds" :
                                  case "Hearts" :
                                      denominationColor = "#FF0000A0";
                                      break;
                                  case "NoTrumps" :
                                      denominationColor = "white";
                                      break;
                                  case "Clubs" :
                                  case "Spades" :
                                      denominationColor = "#606060";
                                      break;
                                  default:
                                    denominationColor = "white";
                                }
                              } else {
                                denominationColor = "white";
                              }
                              var getLevelPlusPossibleNT = function (n) {
                                if (x.contractSuit === "NoTrumps") {
                                  return String(n) + "NT";
                                } else {
                                  return String(n);
                                }
                              };
                              var n = x.contractLevel;
                              var textValue = n !== undefined ? getLevelPlusPossibleNT(n) : "";
                              var n$1 = x.totalTricksNorthSouth;
                              var n$2 = x.totalTricksWestEast;
                              return React.createElement("tr", {
                                          key: String(Random.$$int(1000000)),
                                          style: {
                                            backgroundColor: "white",
                                            color: "#606060"
                                          }
                                        }, React.createElement("td", {
                                              style: {
                                                backgroundColor: x.vulnerable !== "" ? "white" : "#f0f0f0"
                                              }
                                            }, x.vulnerable), React.createElement("td", {
                                              style: {
                                                backgroundColor: x.vulnerable !== "" ? "white" : "#f0f0f0"
                                              }
                                            }, x.contractDeclarer === undefined ? "" : $$String.sub(Shuffle$ReasonReactExamples.pocAsString(x.contractDeclarer), 0, 1)), React.createElement("td", {
                                              style: {
                                                backgroundColor: x.vulnerable !== "" ? "white" : "#f0f0f0"
                                              }
                                            }, React.createElement(ChicagoBidTableCell$ReasonReactExamples.make, {
                                                  textValue: textValue,
                                                  denominationValue: denominationValue,
                                                  denominationColor: denominationColor,
                                                  suffixTextValue: x.isDoubled ? "x" : (
                                                      x.isRedoubled ? "xx" : ""
                                                    )
                                                })), React.createElement("td", {
                                              style: {
                                                backgroundColor: x.vulnerable !== "" ? "white" : "#f0f0f0"
                                              }
                                            }, n$1 !== undefined ? String(n$1) : ""), React.createElement("td", {
                                              style: {
                                                color: x.vulnerable !== "" ? "#606060" : "#000000",
                                                paddingRight: "1vh",
                                                textAlign: "right"
                                              }
                                            }, Shuffle$ReasonReactExamples.optionIntAsString(x.scoreNorthSouth)), React.createElement("td", {
                                              style: {
                                                backgroundColor: x.vulnerable !== "" ? "white" : "#f0f0f0"
                                              }
                                            }, n$2 !== undefined ? String(n$2) : ""), React.createElement("td", {
                                              style: {
                                                color: x.vulnerable !== "" ? "#606060" : "#000000",
                                                paddingRight: "1vh",
                                                textAlign: "right"
                                              }
                                            }, Shuffle$ReasonReactExamples.optionIntAsString(x.scoreWestEast)));
                            })))));
  }
}

var make = ChicagoScoreTable;

exports.make = make;
/* react Not a pure module */
