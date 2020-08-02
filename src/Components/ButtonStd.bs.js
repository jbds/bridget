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
  var isWasteOfSpaceOpt = Props.isWasteOfSpace;
  var colorOpt = Props.color;
  var isActive = isActiveOpt !== undefined ? isActiveOpt : true;
  var isVisible = isVisibleOpt !== undefined ? isVisibleOpt : true;
  var isWasteOfSpace = isWasteOfSpaceOpt !== undefined ? isWasteOfSpaceOpt : false;
  var color = colorOpt !== undefined ? colorOpt : "#26653B";
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: isActive ? "#ffffff" : "#e0e0e0",
                    border: "1px solid #26653B",
                    color: color,
                    display: isVisible ? "inline" : "none",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.0vh",
                    height: "5.0vh",
                    margin: "0vh 0.5vh 0vh 0vh",
                    visibility: isWasteOfSpace ? "hidden" : "visible",
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
