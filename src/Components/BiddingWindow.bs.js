'use strict';

var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var SpacerStd$ReasonReactExamples = require("./SpacerStd.bs.js");
var ButtonBidLarge$ReasonReactExamples = require("./ButtonBidLarge.bs.js");
var ButtonBidSmall$ReasonReactExamples = require("./ButtonBidSmall.bs.js");

function BiddingWindow(Props) {
  var dispatch = Props.dispatch;
  return React.createElement(React.Fragment, undefined, React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [1]),
                  label: "1",
                  id: "btnBid1",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [2]),
                  label: "2",
                  id: "btnBid2",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [3]),
                  label: "3",
                  id: "btnBid3",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [4]),
                  label: "4",
                  id: "btnBid4",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [5]),
                  label: "5",
                  id: "btnBid5",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [6]),
                  label: "6",
                  id: "btnBid6",
                  color: "#606060"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [7]),
                  label: "7",
                  id: "btnBid7",
                  color: "#606060"
                }), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAddSpecial */Block.__(4, ["Pass"]),
                  label: "Pass",
                  id: "btnBidPass",
                  backgroundColor: "#26653B"
                }), React.createElement("br", undefined), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Clubs"]),
                  label: "\u2663",
                  id: "btnBidC",
                  color: "black"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Diamonds"]),
                  label: "\u2666",
                  id: "btnBidD",
                  color: "red",
                  isVisible: false
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Hearts"]),
                  label: "\u2665",
                  id: "btnBidH",
                  color: "red"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Spades"]),
                  label: "\u2660",
                  id: "btnBidS",
                  color: "black"
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["NoTrumps"]),
                  label: "NT",
                  id: "btnBidNT",
                  color: "#606060"
                }), React.createElement(SpacerStd$ReasonReactExamples.make, {
                  spacerWidth: "4vh"
                }), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAddSpecial */Block.__(4, ["X"]),
                  label: "X",
                  id: "btnBidX",
                  backgroundColor: "#E00000"
                }), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAddSpecial */Block.__(4, ["XX"]),
                  label: "XX",
                  id: "btnBidXX",
                  backgroundColor: "#000080"
                }));
}

var make = BiddingWindow;

exports.make = make;
/* react Not a pure module */
