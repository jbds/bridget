'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var Random = require("bs-platform/lib/js/random.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var BidFlexbox$ReasonReactExamples = require("./BidFlexbox.bs.js");

function BidTable(Props) {
  var state = Props.state;
  var emptyFlexbox = React.createElement(BidFlexbox$ReasonReactExamples.make, {
        textValue: "---",
        textColor: "#404040",
        denominationValue: "",
        denominationColor: "white",
        backgroundColor: "#ffffff00"
      });
  var arrayOfFlexboxes = Belt_Array.map($$Array.of_list(List.rev(state.bids)), (function (x) {
          var getLevelIfNone = x.isPass ? "Pass" : (
              x.isDoubled ? "X" : (
                  x.isRedoubled ? "XX" : "Error"
                )
            );
          var getLevelPlusPossibleNT = function (n) {
            if (x.contractSuit === "NoTrumps") {
              return String(n) + "NT";
            } else {
              return String(n);
            }
          };
          var n = x.contractLevel;
          var textValue = n !== undefined ? getLevelPlusPossibleNT(n) : getLevelIfNone;
          var match = x.contractSuit;
          var denominationValue;
          if (match !== undefined) {
            switch (match) {
              case "Clubs" :
                  denominationValue = "\u2663";
                  break;
              case "Diamonds" :
                  denominationValue = "\u2666";
                  break;
              case "Hearts" :
                  denominationValue = "\u2665";
                  break;
              case "NoTrumps" :
                  denominationValue = "";
                  break;
              case "Spades" :
                  denominationValue = "\u2660";
                  break;
              default:
                denominationValue = "Error";
            }
          } else {
            denominationValue = "";
          }
          var textColor;
          switch (textValue) {
            case "Pass" :
                textColor = "#26653B";
                break;
            case "" :
            case "X" :
            case "XX" :
                textColor = "white";
                break;
            default:
              textColor = "#404040";
          }
          var backgroundColor;
          switch (textValue) {
            case "X" :
                backgroundColor = "#E00000";
                break;
            case "XX" :
                backgroundColor = "#000080";
                break;
            default:
              backgroundColor = "white";
          }
          var match$1 = x.contractSuit;
          var denominationColor;
          if (match$1 !== undefined) {
            switch (match$1) {
              case "Diamonds" :
              case "Hearts" :
                  denominationColor = "red";
                  break;
              case "NoTrumps" :
                  denominationColor = "white";
                  break;
              case "Clubs" :
              case "Spades" :
                  denominationColor = "#404040";
                  break;
              default:
                denominationColor = "white";
            }
          } else {
            denominationColor = "white";
          }
          return React.createElement(BidFlexbox$ReasonReactExamples.make, {
                      textValue: textValue,
                      textColor: textColor,
                      denominationValue: denominationValue,
                      denominationColor: denominationColor,
                      backgroundColor: backgroundColor,
                      key: String(Random.$$int(1000000))
                    });
        }));
  return React.createElement("div", {
              style: {
                backgroundColor: "#f8f8f800",
                border: "1px solid #c0c0c0",
                borderWidth: "1px 0 0 1px",
                color: "#404040",
                display: "flex",
                fontFamily: "Trebuchet MS",
                fontSize: "3.25vh",
                margin: "auto",
                textAlign: "center",
                width: "calc(var(--vh, 1vh) * 46)",
                alignContent: "flex-start",
                alignItems: "flex-start",
                flexDirection: "row",
                flexWrap: "wrap",
                justifyContent: "flex-start"
              }
            }, React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "West",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#c0c0c0"
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "North",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#e8e8e8"
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "East",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#c0c0c0"
                }), React.createElement(BidFlexbox$ReasonReactExamples.make, {
                  textValue: "South",
                  textColor: "#404040",
                  denominationValue: "",
                  denominationColor: "white",
                  backgroundColor: "#e8e8e8"
                }), List.length(state.bids) === 0 ? null : (
                List.hd(List.rev(state.bids)).contractPointOfCompass === "West" ? arrayOfFlexboxes : (
                    List.hd(List.rev(state.bids)).contractPointOfCompass === "North" ? React.createElement(React.Fragment, undefined, emptyFlexbox, arrayOfFlexboxes) : (
                        List.hd(List.rev(state.bids)).contractPointOfCompass === "East" ? React.createElement(React.Fragment, undefined, emptyFlexbox, emptyFlexbox, arrayOfFlexboxes) : (
                            List.hd(List.rev(state.bids)).contractPointOfCompass === "South" ? React.createElement(React.Fragment, undefined, emptyFlexbox, emptyFlexbox, emptyFlexbox, arrayOfFlexboxes) : null
                          )
                      )
                  )
              ));
}

var make = BidTable;

exports.make = make;
/* react Not a pure module */
