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

  ws = new WebSocket(`ws://${location.host}`);
  ws.onerror = function() {
    showMessageInConsole('Websocket error');
  };
  ws.onopen = function() {
    showMessageInConsole('Websocket connection established');
  };
  ws.onclose = function() {
    showMessageInConsole('Websocket connection closed');
    ws = null;
  };
  // add detection of message received from server
  ws.onmessage = function(e) {
    showMessageInConsole(e.data);
  };
}

function doLogin(myLoginNameValue) {
  if(!myLoginNameValue) {
    alert('Please enter your name before you login');
    return;
  }
  fetch('/login', {
    method: 'POST',
    credentials: 'same-origin',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({userName: myLoginNameValue})
  })
  .then(showMessageInConsole)
  // this replaces a separate button for "open websocket connection"
  .then(handleWsOpen)
  .catch(function(err){
    showMessageInConsole(err.message);
  });
}

exports.test = test;
exports.doLogin = doLogin;
;

/*  Not a pure module */
