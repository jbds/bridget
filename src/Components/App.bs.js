'use strict';

var React = require("react");
var Global$ReasonReactExamples = require("../Global.bs.js");
var SpanStd$ReasonReactExamples = require("./SpanStd.bs.js");
var InputStd$ReasonReactExamples = require("./InputStd.bs.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");
var ButtonStdJsx$ReasonReactExamples = require("./ButtonStdJsx.bs.js");
var TablePosition$ReasonReactExamples = require("./TablePosition.bs.js");
var ButtonBidSmall$ReasonReactExamples = require("./ButtonBidSmall.bs.js");

const Online = require('../Online.bs');
;

function App(Props) {
  var match = React.useReducer(Global$ReasonReactExamples.reducer, Global$ReasonReactExamples.initialState);
  var dispatch = match[1];
  var state = match[0];
  ((!window.isLastActionSync ? window.gameState = match[0] : false));
  ((!window.isLastActionSync 
    ? 
    Online.doMessage() 
    : 
    //console.log('Action-Sync: doMessage suppressed')
    false));
  var handlerBtnRotateTable = function (_e) {
    ((window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)));
    
  };
  var handlerBtnLogin = function (_e) {
    ((userState.player = (document.getElementById('txtMyLoginName').value).toUpperCase()));
    ((localStorage.setItem(
                      'myLoginName',
                      userState.player
                    )));
    ((Online.doLogin(userState.player)));
    
  };
  var handlerBtnLogout = function (_e) {
    ((window.userState.player = '?'));
    ((Online.doLogout((document.getElementById('txtMyLoginName').value).toUpperCase())));
    
  };
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  id: "sidebar1"
                }, React.createElement("br", undefined), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn1",
                      text: "Player: "
                    }), React.createElement(InputStd$ReasonReactExamples.make, {
                      id: "txtMyLoginName"
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn2",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Login",
                      id: "btnLogin",
                      onClick: handlerBtnLogin
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spn2",
                      text: " "
                    }), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Logout",
                      id: "btnLogout",
                      onClick: handlerBtnLogout
                    }), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement(TablePosition$ReasonReactExamples.make, {
                      state: state,
                      dispatch: dispatch
                    })), React.createElement("div", {
                  id: "sidebar2"
                }, React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Discard */1,
                      label: "Discard",
                      id: "btnDiscard",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Sync */2,
                      label: "Sync state with gameState",
                      id: "btnSync",
                      isVisible: false
                    }), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Shuffle */0,
                      label: "Shuffle",
                      id: "btnShuffle"
                    }), React.createElement("div", {
                      id: "spnGS"
                    }, String(state.randomInt))), React.createElement("div", {
                  id: "sidebar3"
                }, React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Rotate table",
                      id: "btnRotateTable",
                      onClick: handlerBtnRotateTable
                    }), React.createElement("br", undefined)), React.createElement("div", {
                  id: "biddingWindow"
                }, React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "1",
                      id: "btnBid1",
                      color: "#606060"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "2",
                      id: "btnBid2",
                      color: "#606060"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "3",
                      id: "btnBid3",
                      color: "#606060"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "4",
                      id: "btnBid4",
                      color: "#606060"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "5",
                      id: "btnBid5",
                      color: "#606060"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "6",
                      id: "btnBid6",
                      color: "#606060"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "7",
                      id: "btnBid7",
                      color: "#606060"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "\u2663",
                      id: "btnBidC",
                      color: "black"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "\u2666",
                      id: "btnBidD",
                      color: "red"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "\u2665",
                      id: "btnBidH",
                      color: "red"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "\u2660",
                      id: "btnBidS",
                      color: "black"
                    }), React.createElement(ButtonBidSmall$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Test */3,
                      label: "NT",
                      id: "btnBidNT",
                      color: "#606060"
                    })));
}

var make = App;

exports.make = make;
/*  Not a pure module */
