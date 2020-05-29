'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function ButtonStd(Props) {
  var dispatch = Props.dispatch;
  var action = Props.action;
  var label = Props.label;
  var id = Props.id;
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: "#FFFFFF",
                    border: "1px solid #26653B",
                    color: "#26653B",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.5vh",
                    margin: "0vh",
                    borderRadius: "5px"
                  },
                  onClick: (function (_e) {
                      return Curry._1(dispatch, action);
                    })
                }, label));
}

var make = ButtonStd;

exports.make = make;
/* react Not a pure module */
