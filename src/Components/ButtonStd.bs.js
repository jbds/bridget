'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function ButtonStd(Props) {
  var dispatch = Props.dispatch;
  var action = Props.action;
  var label = Props.label;
  var id = Props.id;
  var isActiveOpt = Props.isActive;
  var isVisibleOpt = Props.isVisible;
  var isActive = isActiveOpt !== undefined ? isActiveOpt : true;
  var isVisible = isVisibleOpt !== undefined ? isVisibleOpt : true;
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: isActive ? "#ffffff" : "#ffe0e0",
                    border: "1px solid #26653B",
                    color: "#26653B",
                    display: isVisible ? "inline" : "none",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.0vh",
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
