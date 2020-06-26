'use strict';

var React = require("react");
var BidFlexbox$ReasonReactExamples = require("./BidFlexbox.bs.js");

function BidTable(Props) {
  return React.createElement("div", {
              style: {
                backgroundColor: "#f8f8f800",
                border: "1px solid #c0c0c0",
                borderWidth: "1px 0 0 1px",
                color: "#404040",
                display: "flex",
                fontFamily: "Trebuchet MS",
                fontSize: "3.25vh",
                margin: "auto",
                textAlign: "center",
                width: "calc(var(--vh, 1vh) * 46)",
                alignContent: "flex-start",
                alignItems: "flex-start",
                flexDirection: "row",
                flexWrap: "wrap",
                justifyContent: "flex-start"
              }
            }, React.createElement("div", {
                  style: {
                    backgroundColor: "#c0c0c0",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, "West"), React.createElement("div", {
                  style: {
                    backgroundColor: "#e8e8e8",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, "North"), React.createElement("div", {
                  style: {
                    backgroundColor: "#c0c0c0",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, "East"), React.createElement("div", {
                  style: {
                    backgroundColor: "#e8e8e8",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, "South"), React.createElement("div", {
                  style: {
                    backgroundColor: "#f8f8f800",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, React.createElement("span", undefined, "1"), React.createElement("span", {
                      style: {
                        color: "red",
                        fontSize: "2.0vh"
                      }
                    }, "\u2665")), React.createElement("div", {
                  style: {
                    backgroundColor: "#f8f8f800",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, React.createElement("span", {
                      style: {
                        color: "#26653B"
                      }
                    }, "Pass")), React.createElement("div", {
                  style: {
                    backgroundColor: "#f8f8f800",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, React.createElement("span", {
                      style: {
                        color: "#E00000"
                      }
                    }, "X")), React.createElement("div", {
                  style: {
                    backgroundColor: "#f8f8f800",
                    border: "1px solid #c0c0c0",
                    borderWidth: "0px 1px 1px 0",
                    flex: "0 0 calc(var(--vh, 1vh) * 11)"
                  }
                }, React.createElement("span", {
                      style: {
                        color: "#000080"
                      }
                    }, "XX")), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "2",
                  textColor: "blue",
                  denominationValue: "\u2666",
                  denominationColor: "silver",
                  backgroundColor: "#ffffffff"
                }));
}

var make = BidTable;

exports.make = make;
/* react Not a pure module */
