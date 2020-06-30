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
                                fontFamily: "Arial Narrow"
                              }
                            }, "Vulnerable"), React.createElement("td", {
                              style: {
                                fontFamily: "Arial Narrow"
                              }
                            }, "Declarer"), React.createElement("td", {
                              style: {
                                fontFamily: "Arial Narrow"
                              }
                            }, "Contract"), React.createElement("td", {
                              style: {
                                fontFamily: "Arial Narrow"
                              }
                            }, "Tricks"), React.createElement("td", {
                              style: {
                                fontFamily: "Arial Narrow",
                                padding: "1vh 2.5vh 1vh 2.5vh"
                              }
                            }, "N-S"), React.createElement("td", {
                              style: {
                                fontFamily: "Arial Narrow",
                                padding: "1vh 2.5vh 1vh 2.5vh"
                              }
                            }, "E-W")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "None"), React.createElement("td", undefined, "West"), React.createElement("td", undefined, "1C"), React.createElement("td", undefined, "13"), React.createElement("td", undefined, "9999"), React.createElement("td", undefined, "")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "West"), React.createElement("td", undefined, "Noth"), React.createElement("td", undefined, "6NT"), React.createElement("td", undefined, "8"), React.createElement("td", undefined, ""), React.createElement("td", undefined, "-777")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "North"), React.createElement("td", undefined, "North"), React.createElement("td", undefined, "3H"), React.createElement("td", undefined, "6"), React.createElement("td", undefined, "-25"), React.createElement("td", undefined, "")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "All"), React.createElement("td", undefined, "East"), React.createElement("td", undefined, "1NT"), React.createElement("td", undefined, "7"), React.createElement("td", undefined, "50"), React.createElement("td", undefined, "")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, "."), React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, ""), React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, ""), React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, ""), React.createElement("td", undefined, "1000"), React.createElement("td", undefined, "500")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "None"), React.createElement("td", undefined, "West"), React.createElement("td", undefined, "1C"), React.createElement("td", undefined, "13"), React.createElement("td", undefined, "9999"), React.createElement("td", undefined, "")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "West"), React.createElement("td", undefined, "Noth"), React.createElement("td", undefined, "6NT"), React.createElement("td", undefined, "8"), React.createElement("td", undefined, ""), React.createElement("td", undefined, "-777")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "North"), React.createElement("td", undefined, "North"), React.createElement("td", undefined, "3H"), React.createElement("td", undefined, "6"), React.createElement("td", undefined, "-25"), React.createElement("td", undefined, "")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", undefined, "All"), React.createElement("td", undefined, "East"), React.createElement("td", undefined, "1NT"), React.createElement("td", undefined, "7"), React.createElement("td", undefined, "50"), React.createElement("td", undefined, "")), React.createElement("tr", {
                          style: {
                            backgroundColor: "white"
                          }
                        }, React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, "."), React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, ""), React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, ""), React.createElement("td", {
                              style: {
                                backgroundColor: "#f8f8f8",
                                color: "#f8f8f8"
                              }
                            }, ""), React.createElement("td", undefined, "1000"), React.createElement("td", undefined, "500")))));
}

var make = ChicagoScoreTable;

exports.make = make;
/* react Not a pure module */
