'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function ButtonBidLarge(Props) {
  var dispatch = Props.dispatch;
  var action = Props.action;
  var label = Props.label;
  var id = Props.id;
  var backgroundColor = Props.backgroundColor;
  var isVisibleOpt = Props.isVisible;
  var isVisible = isVisibleOpt !== undefined ? isVisibleOpt : true;
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: backgroundColor,
                    border: "1px solid #26653B",
                    color: "white",
                    display: isVisible ? "inline" : "none",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.0vh",
                    height: "6.25vh",
                    margin: "0.25vh",
                    width: "calc(var(--vh, 1vh) * 9)",
                    borderRadius: "5px"
                  },
                  onClick: (function (_e) {
                      return Curry._1(dispatch, action);
                    })
                }, label));
}

var make = ButtonBidLarge;

exports.make = make;
/* react Not a pure module */
