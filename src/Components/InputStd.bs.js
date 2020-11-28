'use strict';

var React = require("react");

function InputStd(Props) {
  var id = Props.id;
  return React.createElement(React.Fragment, undefined, React.createElement("input", {
                  id: id,
                  style: {
                    backgroundColor: "#FFFFFF",
                    border: "1px solid #26653B",
                    color: "#404040",
                    fontFamily: "Trebuchet MS",
                    fontSize: "1.9vh",
                    height: "4.0vh",
                    margin: "0vh",
                    textAlign: "center",
                    width: "8vh",
                    borderRadius: "5px"
                  }
                }));
}

var make = InputStd;

exports.make = make;
/* react Not a pure module */
