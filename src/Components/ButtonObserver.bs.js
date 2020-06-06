'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function ButtonObserver(Props) {
  var dispatch = Props.dispatch;
  var action = Props.action;
  var label = Props.label;
  var id = Props.id;
  var isActive = Props.isActive;
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: isActive ? "#ffffff" : "#ffe0e0",
                    backgroundImage: "url(assets/EyeSpikeyTransparent.png)",
                    border: "1px solid #26653B",
                    color: isActive ? "#ffffff" : "#e0e0e0",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.5vh",
                    margin: "0vh",
                    backgroundSize: "100% 100%",
                    borderRadius: "5px"
                  },
                  onClick: (function (_e) {
                      return Curry._1(dispatch, action);
                    })
                }, label));
}

var make = ButtonObserver;

exports.make = make;
/* react Not a pure module */
