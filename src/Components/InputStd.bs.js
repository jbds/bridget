'use strict';

var React = require("react");

function InputStd(Props) {
  var id = Props.id;
  return React.createElement(React.Fragment, undefined, React.createElement("input", {
                  id: id,
                  style: {
                    backgroundColor: "#FFFFFF",
                    border: "1px solid #26653B",
                    color: "#808080",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.0vh",
                    height: "4.0vh",
                    margin: "0vh",
                    textAlign: "center",
                    width: "8vh"
                  }
                }));
}

var make = InputStd;

exports.make = make;
/* react Not a pure module */
