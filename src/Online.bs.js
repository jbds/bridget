'use strict';


let ws;

// make sure we can invoke a func in this module
function test() {
  alert('Online.test invoked!');
}

function showMessageInConsole(message) {
  console.log(message);
}

function handleResponse(response) {
  return response.ok
  ? response.json().then((data) => JSON.stringify(data, null, 2))
  : Promise.reject(new Error('Unexpected response'));
}

function handleWsOpen(){
  if (ws) {
    ws.onerror = ws.onopen = ws.onclose = null;
    ws.close();
  }

  ws = new WebSocket(`wss://${location.host}`);
  ws.onerror = function() {
    showMessageInConsole('clent ws.onerror fired, so Websocket error');
  };
  ws.onopen = function() {
    //showMessageInConsole('client ws.onopen fired, so Websocket connection established');
  };
  ws.onclose = function() {
    // event fires at doLogout, we want to force gameState to nothing locally
    // it also fires if server goes down!
    // is this necessary?
    // gameState = {
    //   activePointOfCompass: "",
    //   bids: [],
    //   chicagoScoreSheet: [],
    //   dealer: 0,
    //   handVisible: {},
    //   lastAction: 'ws.onclose',  //gets replaced by LogOutOrServerDownSync
    //   pack: [],
    //   pointOfCompassAndPlayers: [],
    //   randomInt: -888,
    //   pointOfCompassAndPlayers: [],
    //   dealIndex: -1,
    //   isBiddingCycle: false
    // }
    // is this even desirable?
    // and sync state to this (actually, recreate state same as gameState)
    //showMessageInConsole('ws.onclose - dispatch Sync action via hidden key on sidebar');
    //document.getElementById('btnSync').click();
    showMessageInConsole('client ws.onclose fired, so Websocket connection closed');
    ws = null;
  };
  ws.onmessage = function(e) {
    // add detection of message received from server
    showMessageInConsole('client ws.onmessage fired, see Websocket message received below:');
    window.jbObj = JSON.parse(e.data);
    //showMessageInConsole(window.jbObj);
    //showMessageInConsole('will now update gameState with jbObj');
    gameState = window.jbObj;
    //showMessageInConsole(gameState);
    showMessageInConsole('client ws.onmessage - dispatch LoginSync action via hidden key on sidebar');
    document.getElementById('btnLoginSync').click();
  };
}

function doLogin(myLoginNameValue) {
  if(!myLoginNameValue) {
    alert('Please enter your name before you login');
    return;
  }
  fetch(`https://${location.host}/login`, {
    method: 'POST',
    credentials: 'same-origin',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({userName: myLoginNameValue})
  })
  .then(handleResponse)
  .then(showMessageInConsole)
  // this replaces a separate button for "open websocket connection"
  .then(handleWsOpen)
  .catch(function(err){
    showMessageInConsole(err.message);
  });
}

function doLogout(myLoginNameValue) {
  fetch(`https://${location.host}/logout`, {
    method: 'DELETE',
    credentials: 'same-origin',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({userName: myLoginNameValue})
  })
  .then(handleResponse)
  .then(showMessageInConsole)
  .catch(function(err) {
    showMessageInConsole(err.message);
  });
}

function doMessage(msg) {
  if(!ws) {
    //showMessageInConsole('cannot send message - no websocket connection');
    return;
  }
  ws.send(JSON.stringify(msg));
  //showMessageInConsole('client doMessage - sent message to server as below:');
  //showMessageInConsole(JSON.stringify(gameState));
  showMessageInConsole('client doMessage(msg)');
}

exports.test = test;
exports.doLogin = doLogin;
exports.doLogout = doLogout;
exports.doMessage = doMessage;
;

/*  Not a pure module */
