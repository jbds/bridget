'use strict';

var React = require("react");

function BidTable(Props) {
  return React.createElement(React.Fragment, undefined, React.createElement("table", {
                  style: {
                    color: "#404040",
                    fontFamily: "Trebuchet MS",
                    fontSize: "3.25vh",
                    margin: "auto",
                    textAlign: "center",
                    width: "calc(var(--vh, 1vh) * 45)"
                  }
                }, React.createElement("thead", undefined, React.createElement("tr", undefined, React.createElement("th", {
                              style: {
                                width: "25%"
                              }
                            }, "West"), React.createElement("th", undefined, "North"), React.createElement("th", {
                              style: {
                                width: "25%"
                              }
                            }, "East"), React.createElement("th", undefined, "South"))), React.createElement("tbody", undefined, React.createElement("tr", undefined, React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass")), React.createElement("tr", undefined, React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass")), React.createElement("tr", undefined, React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass")), React.createElement("tr", undefined, React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass")), React.createElement("tr", undefined, React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass")), React.createElement("tr", undefined, React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass")), React.createElement("tr", undefined, React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass"), React.createElement("td", undefined, "Pass")))));
}

var make = BidTable;

exports.make = make;
/* react Not a pure module */
