'use strict';

var React = require("react");

function ChicagoScoreTable(Props) {
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
                            }, "E-W")))));
}

var make = ChicagoScoreTable;

exports.make = make;
/* react Not a pure module */
