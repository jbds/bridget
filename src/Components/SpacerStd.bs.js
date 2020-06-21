'use strict';

var React = require("react");

function SpacerStd(Props) {
  var spacerWidth = Props.spacerWidth;
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  style: {
                    color: "#000000",
                    display: "inline",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.0vh",
                    margin: "0.0vh " + (spacerWidth + " 0.0vh 0.0vh"),
                    textAlign: "center",
                    width: "0px"
                  }
                }, ""));
}

var make = SpacerStd;

exports.make = make;
/* react Not a pure module */
