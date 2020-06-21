'use strict';

var React = require("react");
var ButtonBidLarge$ReasonReactExamples = require("./ButtonBidLarge.bs.js");
var ButtonBidSmall$ReasonReactExamples = require("./ButtonBidSmall.bs.js");

function BiddingWindow(Props) {
  var dispatch = Props.dispatch;
  return React.createElement(React.Fragment, undefined, React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "Pass",
                  id: "btnBidPass",
                  backgroundColor: "#26653B"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "1",
                  id: "btnBid1",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "2",
                  id: "btnBid2",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "3",
                  id: "btnBid3",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "4",
                  id: "btnBid4",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "5",
                  id: "btnBid5",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "6",
                  id: "btnBid6",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "7",
                  id: "btnBid7",
                  color: "#606060"
                }), React.createElement("br", undefined), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "X",
                  id: "btnBidX",
                  backgroundColor: "#E00000"
                }), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "XX",
                  id: "btnBidXX",
                  backgroundColor: "#000080"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "\u2663",
                  id: "btnBidC",
                  color: "black"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "\u2666",
                  id: "btnBidD",
                  color: "red"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "\u2665",
                  id: "btnBidH",
                  color: "red"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "\u2660",
                  id: "btnBidS",
                  color: "black"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* Test */5,
                  label: "NT",
                  id: "btnBidNT",
                  color: "#606060"
                }));
}

var make = BiddingWindow;

exports.make = make;
/* react Not a pure module */
