'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function ButtonBidSmall(Props) {
  var dispatch = Props.dispatch;
  var action = Props.action;
  var label = Props.label;
  var id = Props.id;
  var color = Props.color;
  var isActiveOpt = Props.isActive;
  var isVisibleOpt = Props.isVisible;
  var isActive = isActiveOpt !== undefined ? isActiveOpt : true;
  var isVisible = isVisibleOpt !== undefined ? isVisibleOpt : true;
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: isActive ? "#ffffff" : "#ffe0e0",
                    border: "1px solid #26653B",
                    color: color,
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.5vh",
                    height: "6.25vh",
                    margin: "1vh 0.25vh 0.25vh 0.25vh",
                    padding: "0vh",
                    visibility: isVisible ? "visible" : "hidden",
                    width: "calc(var(--vh, 1vh) * 6.25)",
                    borderRadius: "5px"
                  },
                  onClick: (function (_e) {
                      return Curry._1(dispatch, action);
                    })
                }, label));
}

var make = ButtonBidSmall;

exports.make = make;
/* react Not a pure module */
