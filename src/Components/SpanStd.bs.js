'use strict';

var React = require("react");

function SpanStd(Props) {
  var id = Props.id;
  var text = Props.text;
  var isWarningOpt = Props.isWarning;
  var fontSizeOpt = Props.fontSize;
  var isWarning = isWarningOpt !== undefined ? isWarningOpt : false;
  var fontSize = fontSizeOpt !== undefined ? fontSizeOpt : "2.0vh";
  return React.createElement(React.Fragment, undefined, React.createElement("span", {
                  id: id,
                  style: {
                    color: isWarning ? "#C00000" : "#404040",
                    fontFamily: "Trebuchet MS",
                    fontSize: fontSize,
                    margin: "0vh",
                    textAlign: "center",
                    width: "10vh"
                  }
                }, text));
}

var make = SpanStd;

exports.make = make;
/* react Not a pure module */
