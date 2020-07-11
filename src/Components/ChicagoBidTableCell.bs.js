'use strict';

var React = require("react");

function ChicagoBidTableCell(Props) {
  var textValue = Props.textValue;
  var denominationValue = Props.denominationValue;
  var denominationColor = Props.denominationColor;
  var suffixTextValue = Props.suffixTextValue;
  return React.createElement("div", undefined, React.createElement("span", {
                  style: {
                    color: "#404040"
                  }
                }, textValue), React.createElement("span", {
                  style: {
                    color: denominationColor
                  }
                }, denominationValue), React.createElement("span", {
                  style: {
                    color: "#404040"
                  }
                }, suffixTextValue));
}

var make = ChicagoBidTableCell;

exports.make = make;
/* react Not a pure module */
