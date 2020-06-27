'use strict';

var React = require("react");

function BidFlexbox(Props) {
  var textValue = Props.textValue;
  var textColor = Props.textColor;
  var denominationValue = Props.denominationValue;
  var denominationColor = Props.denominationColor;
  var backgroundColor = Props.backgroundColor;
  return React.createElement("div", {
              style: {
                backgroundColor: backgroundColor,
                border: "1px solid #c0c0c0",
                borderWidth: "0px 1px 1px 0",
                height: "4.5vh",
                padding: denominationValue === "" ? "0.5vh 0 0 0" : "0 0 0.5vh 0",
                flex: "0 0 calc(var(--vh, 1vh) * 11)"
              }
            }, React.createElement("span", {
                  style: {
                    color: textColor
                  }
                }, textValue), React.createElement("span", {
                  style: {
                    color: denominationColor
                  }
                }, denominationValue));
}

var make = BidFlexbox;

exports.make = make;
/* react Not a pure module */
