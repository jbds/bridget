'use strict';

var React = require("react");

function SpanStd(Props) {
  var id = Props.id;
  var text = Props.text;
  var isWarningOpt = Props.isWarning;
  var isWarning = isWarningOpt !== undefined ? isWarningOpt : false;
  return React.createElement(React.Fragment, undefined, React.createElement("span", {
                  id: id,
                  style: {
                    color: isWarning ? "#C00000" : "#26653B",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.0vh",
                    margin: "0vh",
                    textAlign: "center",
                    width: "10vh"
                  },
                  onClick: (function (_e) {
                      console.log("Clicked span element");
                      
                    })
                }, text));
}

var make = SpanStd;

exports.make = make;
/* react Not a pure module */
