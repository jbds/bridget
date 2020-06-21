'use strict';

var React = require("react");
var Global$ReasonReactExamples = require("../Global.bs.js");
var SpanStd$ReasonReactExamples = require("./SpanStd.bs.js");
var BidTable$ReasonReactExamples = require("./BidTable.bs.js");
var InputStd$ReasonReactExamples = require("./InputStd.bs.js");
var ButtonStd$ReasonReactExamples = require("./ButtonStd.bs.js");
var ButtonStdJsx$ReasonReactExamples = require("./ButtonStdJsx.bs.js");
var BiddingWindow$ReasonReactExamples = require("./BiddingWindow.bs.js");
var TablePosition$ReasonReactExamples = require("./TablePosition.bs.js");

const Online = require('../Online.bs');
;

function App(Props) {
  var match = React.useReducer(Global$ReasonReactExamples.reducer, Global$ReasonReactExamples.initialState);
  var dispatch = match[1];
  var state = match[0];
  ((window.gameState = match[0]));
  ((!window.isLastActionSync 
    ? 
    Online.doMessage() 
    : 
    console.log('Action-Sync: doMessage suppressed')));
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
                      action: /* Discard */2,
                      label: "Discard",
                      id: "btnDiscard",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Sync */3,
                      label: "Sync state with gameState",
                      id: "btnSync",
                      isVisible: false
                    }), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* LoginSync */4,
                      label: "Login sync with server",
                      id: "btnLoginSync",
                      isVisible: false
                    }), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* NewGame */0,
                      label: "New Game",
                      id: "btnNewGame"
                    }), React.createElement("br", undefined), React.createElement(ButtonStd$ReasonReactExamples.make, {
                      dispatch: dispatch,
                      action: /* Shuffle */1,
                      label: "New Deal",
                      id: "btnShuffle"
                    })), React.createElement("div", {
                  id: "sidebar3"
                }, React.createElement("br", undefined), React.createElement(ButtonStdJsx$ReasonReactExamples.make, {
                      label: "Rotate table",
                      id: "btnRotateTable",
                      onClick: handlerBtnRotateTable
                    }), React.createElement("br", undefined), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnRandomInt",
                      text: String(state.randomInt)
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnRILA",
                      text: " "
                    }), React.createElement(SpanStd$ReasonReactExamples.make, {
                      id: "spnLastAction",
                      text: state.lastAction
                    })), React.createElement("div", {
                  id: "bidTable",
                  style: {
                    padding: "1vh 0vh 0vh 0vh",
                    borderRadius: "5px"
                  }
                }, React.createElement(BidTable$ReasonReactExamples.make, { })), React.createElement("div", {
                  id: "biddingWindow",
                  style: {
                    display: "inline",
                    padding: "1vh 1vh 1vh 3vh",
                    borderRadius: "10px"
                  }
                }, React.createElement(BiddingWindow$ReasonReactExamples.make, {
                      dispatch: dispatch
                    })));
}

var make = App;

exports.make = make;
/*  Not a pure module */
