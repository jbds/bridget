'use strict';

var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var SpacerStd$ReasonReactExamples = require("./SpacerStd.bs.js");
var ButtonBidLarge$ReasonReactExamples = require("./ButtonBidLarge.bs.js");
var ButtonBidSmall$ReasonReactExamples = require("./ButtonBidSmall.bs.js");

function BiddingWindow(Props) {
  var dispatch = Props.dispatch;
  var state = Props.state;
  var bidListHead = Belt_List.head(state.bids);
  var isShowXAndXX = bidListHead !== undefined ? bidListHead.contractSuit !== "" : false;
  var bidsListFilteredByContractLevel = Belt_List.keep(state.bids, (function (x) {
          return x.contractLevel !== undefined;
        }));
  var optionCurrentContractLevelBid = Belt_List.head(bidsListFilteredByContractLevel);
  var optionCurrentContractLevel = optionCurrentContractLevelBid !== undefined ? optionCurrentContractLevelBid.contractLevel : undefined;
  var currentContractLevel = optionCurrentContractLevel !== undefined ? optionCurrentContractLevel : 0;
  console.log("currentContractLevel:");
  console.log(currentContractLevel);
  var optionCurrentContractSuit = optionCurrentContractLevelBid !== undefined ? optionCurrentContractLevelBid.contractSuit : undefined;
  var currentContractSuitAsString = optionCurrentContractSuit !== undefined ? optionCurrentContractSuit : "";
  var currentContractSuitAsRank;
  switch (currentContractSuitAsString) {
    case "Clubs" :
        currentContractSuitAsRank = 0;
        break;
    case "Diamonds" :
        currentContractSuitAsRank = 1;
        break;
    case "Hearts" :
        currentContractSuitAsRank = 2;
        break;
    case "NoTrumps" :
        currentContractSuitAsRank = 4;
        break;
    case "Spades" :
        currentContractSuitAsRank = 3;
        break;
    default:
      currentContractSuitAsRank = -1;
  }
  var optionBidListTail = Belt_List.tail(bidsListFilteredByContractLevel);
  var bidListTail = optionBidListTail !== undefined ? optionBidListTail : /* [] */0;
  var optionPreviousBid = Belt_List.head(bidListTail);
  var optionPreviousContractSuit = optionPreviousBid !== undefined ? optionPreviousBid.contractSuit : undefined;
  var previousContractSuitAsString = optionPreviousContractSuit !== undefined ? optionPreviousContractSuit : "";
  var previousContractSuitAsRank;
  switch (previousContractSuitAsString) {
    case "Clubs" :
        previousContractSuitAsRank = 0;
        break;
    case "Diamonds" :
        previousContractSuitAsRank = 1;
        break;
    case "Hearts" :
        previousContractSuitAsRank = 2;
        break;
    case "NoTrumps" :
        previousContractSuitAsRank = 4;
        break;
    case "Spades" :
        previousContractSuitAsRank = 3;
        break;
    default:
      previousContractSuitAsRank = -1;
  }
  var optionPreviousContractLevel = optionPreviousBid !== undefined ? optionPreviousBid.contractLevel : undefined;
  var previousContractLevel = optionPreviousContractLevel !== undefined ? optionPreviousContractLevel : -1;
  console.log("previousContractLevel:");
  console.log(previousContractLevel);
  return React.createElement(React.Fragment, undefined, React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [1]),
                  label: "1",
                  id: "btnBid1",
                  color: "#606060",
                  isVisible: state.isBiddingHideDenominationButtons && (currentContractLevel <= 1 && currentContractSuitAsRank !== 4 || currentContractLevel < 1 && currentContractSuitAsRank === 4)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [2]),
                  label: "2",
                  id: "btnBid2",
                  color: "#606060",
                  isVisible: state.isBiddingHideDenominationButtons && (currentContractLevel <= 2 && currentContractSuitAsRank !== 4 || currentContractLevel < 2 && currentContractSuitAsRank === 4)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [3]),
                  label: "3",
                  id: "btnBid3",
                  color: "#606060",
                  isVisible: state.isBiddingHideDenominationButtons && (currentContractLevel <= 3 && currentContractSuitAsRank !== 4 || currentContractLevel < 3 && currentContractSuitAsRank === 4)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [4]),
                  label: "4",
                  id: "btnBid4",
                  color: "#606060",
                  isVisible: state.isBiddingHideDenominationButtons && (currentContractLevel <= 4 && currentContractSuitAsRank !== 4 || currentContractLevel < 4 && currentContractSuitAsRank === 4)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [5]),
                  label: "5",
                  id: "btnBid5",
                  color: "#606060",
                  isVisible: state.isBiddingHideDenominationButtons && (currentContractLevel <= 5 && currentContractSuitAsRank !== 4 || currentContractLevel < 5 && currentContractSuitAsRank === 4)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [6]),
                  label: "6",
                  id: "btnBid6",
                  color: "#606060",
                  isVisible: state.isBiddingHideDenominationButtons && (currentContractLevel <= 6 && currentContractSuitAsRank !== 4 || currentContractLevel < 6 && currentContractSuitAsRank === 4)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAdd */Block.__(2, [7]),
                  label: "7",
                  id: "btnBid7",
                  color: "#606060",
                  isVisible: state.isBiddingHideDenominationButtons && (currentContractLevel <= 7 && currentContractSuitAsRank !== 4 || currentContractLevel < 7 && currentContractSuitAsRank === 4)
                }), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAddSpecial */Block.__(4, ["Pass"]),
                  label: "Pass",
                  id: "btnBidPass",
                  backgroundColor: "#26653B",
                  isVisible: state.isBiddingHideDenominationButtons
                }), React.createElement("br", undefined), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Clubs"]),
                  label: "\u2663",
                  id: "btnBidC",
                  color: "black",
                  isVisible: !state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 0 || previousContractSuitAsRank === 4 || currentContractLevel > previousContractLevel)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Diamonds"]),
                  label: "\u2666",
                  id: "btnBidD",
                  color: "red",
                  isVisible: !state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 1 || previousContractSuitAsRank === 4 || currentContractLevel > previousContractLevel)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Hearts"]),
                  label: "\u2665",
                  id: "btnBidH",
                  color: "red",
                  isVisible: !state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 2 || previousContractSuitAsRank === 4 || currentContractLevel > previousContractLevel)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["Spades"]),
                  label: "\u2660",
                  id: "btnBidS",
                  color: "black",
                  isVisible: !state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 3 || previousContractSuitAsRank === 4 || currentContractLevel > previousContractLevel)
                }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidUpdate */Block.__(3, ["NoTrumps"]),
                  label: "NT",
                  id: "btnBidNT",
                  color: "#606060",
                  isVisible: !state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 4 || previousContractSuitAsRank === 4 || currentContractLevel > previousContractLevel)
                }), React.createElement(SpacerStd$ReasonReactExamples.make, {
                  spacerWidth: "4vh"
                }), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAddSpecial */Block.__(4, ["X"]),
                  label: "X",
                  id: "btnBidX",
                  backgroundColor: "#E00000",
                  isVisible: isShowXAndXX
                }), React.createElement(ButtonBidLarge$ReasonReactExamples.make, {
                  dispatch: dispatch,
                  action: /* BidAddSpecial */Block.__(4, ["XX"]),
                  label: "XX",
                  id: "btnBidXX",
                  backgroundColor: "#000080",
                  isVisible: isShowXAndXX
                }));
}

var make = BiddingWindow;

exports.make = make;
/* react Not a pure module */
