'use strict';

var React = require("react");
var BidFlexbox$ReasonReactExamples = require("./BidFlexbox.bs.js");

function BidTable(Props) {
  var state = Props.state;
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
            }, React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "West",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#c0c0c0",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "North",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#e8e8e8",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "East",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#c0c0c0",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "South",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#e8e8e8",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "---",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#ffffff00",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "4NT",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "#404040",
                  backgroundColor: "#ffffff",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "1",
                  textColor: "#404040",
                  denominationValue: "\u2665",
                  denominationColor: "red",
                  backgroundColor: "#ffffff",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "Pass",
                  textColor: "#26653B",
                  denominationValue: "",
                  denominationColor: "#404040",
                  backgroundColor: "#ffffff",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "X",
                  textColor: "#E00000",
                  denominationValue: "",
                  denominationColor: "#404040",
                  backgroundColor: "#ffffff",
                  state: state
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "XX",
                  textColor: "blue",
                  denominationValue: "",
                  denominationColor: "#404040",
                  backgroundColor: "#ffffff",
                  state: state
                }));
}

var make = BidTable;

exports.make = make;
/* react Not a pure module */
