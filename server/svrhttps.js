'use strict';

const session = require('express-session');
const express = require('express');
const http = require('http');
const uuid = require('uuid');
const bodyParser = require('body-parser');
const https = require('https');
const fs = require('fs');

const WebSocket = require('ws');

const app = express();
app.use(express.static(__dirname + '/public', {dotfiles: 'allow'}));

const options = {
        key: fs.readFileSync('/etc/letsencrypt/live/98765.co.uk/privkey.pem'),
        cert: fs.readFileSync('/etc/letsencrypt/live/98765.co.uk/cert.pem'),
        ca: fs.readFileSync('/etc/letsencrypt/live/98765.co.uk/chain.pem')
};


const map = new Map();
//const json_body_parser = bodyParser.json();

// we need a global variable to hold initial and subsequent gameStates
// this structure MUST match the client app state structure
// and each property must be initialised to at least something even if empty
// note bids = list(bid), list(chicagoScoreSheet) when empty [] maps to javascript as plain 0
let gameState = {
  activePointOfCompass: undefined,
  bids: 0,
  chicagoScoreSheet: 0,
  dealer: undefined,
  dealIndex: -1,
  declarer: undefined,
  discardIndex: -1,
  discardSuit: undefined,
  handVisible: {north: true, east: true, south: true, west: true},
  isBiddingCycle: false,
  isBiddingHideDenominationButtons: true,
  isDummyVisible: false,
  isRebootVisible: true,
  lastAction: "None(fromServer) then LoginSync(client)",
  pack: [],
  pointOfCompassAndPlayers: [],
  randomInt: -999,
};

// shallow copy?
let rebootGameState = JSON.parse(JSON.stringify(gameState));
rebootGameState.pointOfCompassAndPlayers = [];

// Undo requires an array of gameState objects, initialised to just the above
let arrGameStates = [gameState];


// and a global function for rebroadcast, called by login and logout
function broadcastGameStateToAll(gS){
  //WebSocket.Server.clients property is only added when the clientTracking is truthy.    
  // broadcast to all clients
  wss.clients.forEach(function each(client) {
    // send a message to every connected client
    if (client.readyState === WebSocket.OPEN) {
      //client.send('Broadcast!');
      //iterate over all connected users
      // let usersMessage = 'Online: ';
      // map.forEach(function(v, k) {
      //     usersMessage += (k + ' ');
      //   }
      // );
      // client.send(usersMessage);
      // console.log(Array.from(map.keys()));
      //client.send({ usernames: '[Fred, Bill]'});
      // we need to add to the pointOfCompassAndPlayers array
      //let arrLength = gS.pointOfCompassAndPlayers.length;
      //console.log('Array length: ' + arrLength);
      //let userId = req.session.userId;
      //gS.pointOfCompassAndPlayers.push({pointOfCompass: "", player: userId});
      client.send(JSON.stringify(gS));
    }
  });
}

// and a global function for rebroadcast, called by message
// (client !== ws) caused error until we passed this variable into the func
function broadcastGameStateToOthers(gS, ws){
  //WebSocket.Server.clients property is only added when the clientTracking is truthy.    
  // broadcast to all clients
  wss.clients.forEach(function each(client) {
    // send a message to every connected client EXCEPT initiator
    // to avoid an infinite handshake loop!
    if (client !== ws && client.readyState === WebSocket.OPEN) {
      //client.send('Broadcast!');
      //iterate over all connected users
      // let usersMessage = 'Online: ';
      // map.forEach(function(v, k) {
      //     usersMessage += (k + ' ');
      //   }
      // );
      // client.send(usersMessage);
      // console.log(Array.from(map.keys()));
      //client.send({ usernames: '[Fred, Bill]'});
      // we need to add to the pointOfCompassAndPlayers array
      //let arrLength = gS.pointOfCompassAndPlayers.length;
      //console.log('Array length: ' + arrLength);
      //let userId = req.session.userId;
      //gS.pointOfCompassAndPlayers.push({pointOfCompass: "", player: userId});
      client.send(JSON.stringify(gS));
    }
  });
}

//
// We need the same instance of the session parser in express and
// WebSocket server.
//
const sessionParser = session({
  saveUninitialized: false,
  secret: '$eCuRiTy',
  resave: false
});

//
// Serve static files from the 'public' folder.
//
app.use(express.static('public'));
app.use(sessionParser);
app.use(bodyParser.json());

app.post('/login', function(req, res) {
  //
  // "Log in" user and set userId to session.
  //
  console.log(JSON.stringify(req.body));
  const id = req.body.userName;

  console.log(`Updating session for user ${id}`);
  req.session.userId = id;

  // push the state on to the history stack
  arrGameStates.push(gameState);
  // this should happen one time only, so good place to add to pointOfCompass array
  // but might happen more than once, so check array first
  let arrObj = gameState.pointOfCompassAndPlayers.find(el => el.player == id);
  if (!arrObj) {
    gameState.pointOfCompassAndPlayers.push({pointOfCompass: "", player: id});
  }
  // we need to set activePointofCompass and dealer too
  // ideally random
  // only set it once!
  if (gameState.activePointOfCompass == undefined || gameState.dealer == undefined) {
    let rnd = Math.floor(Math.random() * 4);
    let poc;
    switch(rnd) {
      case 0: poc = "West";
      break;
      case 1: poc = "North";
      break;
      case 2: poc = "East";
      break;
      case 3: poc = "South";
      break;
      default: poc = "West";
    }
    gameState.activePointOfCompass = poc;
    gameState.dealer = poc;
  }
  res.send({ result: 'OK', message: `Session created/updated for ${id}`});
  //console.log(gameState);
});

app.delete('/logout', function(req, response) {
  // identify the logout user
  console.log(JSON.stringify(req.body));
  // we will want to echo the logout username
  const oldId = req.body.userName;
  const ws = map.get(req.body.userName);

  // BEFORE we destroy the session, we need to remove the user 
  // from the pointOfCompassAndPlayers array
  gameState.pointOfCompassAndPlayers = gameState.pointOfCompassAndPlayers.filter(obj => {
    return obj.player !== oldId;
  });
  // and broadcast to all
  broadcastGameStateToAll(gameState);


  console.log('Destroying session');
  req.session.destroy(function() {
    if (ws) ws.close();
    response.send({ result: 'OK', message: `Session destroyed for ${oldId}` });
  });
});

//
// Create HTTPS server by ourselves.
//
const httpsServer = https.createServer(options, app);
//WebSocket.Server.clients property is only added when the clientTracking is truthy.
const wss = new WebSocket.Server({ clientTracking: true, noServer: true });

httpsServer.on('upgrade', function(req, socket, head) {
  console.log('Parsing session from req...');

  sessionParser(req, {}, () => {
    if (!req.session.userId) {
      socket.destroy();
      return;
    }

    console.log('Session is parsed!');

    wss.handleUpgrade(req, socket, head, function(ws) {
      wss.emit('connection', ws, req);
    });
  });
});

wss.on('connection', function(ws, req) {
  const userId = req.session.userId;

  // each userId is just the userName string used as a key
  // associated with each unique websocket
  map.set(userId, ws);

  //inspect all users
  map.forEach(function(v, k) {
      console.log(k);

    }
  );

  console.log('about to broadcast gameState to ALL');
  //console.log(gameState);
  // at this point, all other clients will hear about the new user who is logging in
  broadcastGameStateToAll(gameState);

  // function broadcastUserList() {
  //   //WebSocket.Server.clients property is only added when the clientTracking is truthy.    
  //   // broadcast to all clients
  //   wss.clients.forEach(function each(client) {
  //     // send a message to every connected client
  //     if (client.readyState === WebSocket.OPEN) {
  //       //client.send('Broadcast!');
  //       //iterate over all connected users
  //       let usersMessage = 'Online: ';
  //       map.forEach(function(v, k) {
  //           usersMessage += (k + ' ');
  //         }
  //       );
  //       client.send(usersMessage);
  //       console.log(Array.from(map.keys()));
  //       //client.send({ usernames: '[Fred, Bill]'});
  //     }
  //   });
  // };

  //broadcastUserList();
  // instead of broadcasting the usersMessage, which is just a list of users
  // we want to broadcast the gameState modified to take account of latest logged in user



  ws.on('message', function(message) {
    //
    // Here we can now use session parameters.
    //
    console.log(`Received message ${message} from user ${userId}`);
    //console.log(message);

    //broadcastUserList();

    if (message === '"Undo"') {
      //console.log('Undo not yet implemented')
      gameState = arrGameStates.pop();
      broadcastGameStateToAll(gameState);
    } else if (message === '"Reboot"') {
      console.log('about to Reboot, and broadcast to ALL');
      // destroy all history to free up memory
      // no good because referenced elsewhere
      //arrGameStates = [];
      // SO 1232040
      arrGameStates.length = 0;
      // shallow copy? - is good enough to make pointOfCompassAndPlayers = []
      gameState = JSON.parse(JSON.stringify(rebootGameState));
      broadcastGameStateToAll(gameState);
    } else {
      // push the state on to the history stack
      arrGameStates.push(gameState);
      // set server gameState to the gameState sent as a message
      console.log('about to broadcast game state to others');
      //console.log(gameState);
      gameState = JSON.parse(message);
      //console.log(arrGameStates);
      // rebroadcast to others to update other's local state to server gameState
      broadcastGameStateToOthers(gameState, ws);
    }

  });

  ws.on('close', function() {
    map.delete(userId);
    //broadcastUserList();
  });
});

//
// Start the https server.
//
httpsServer.listen(443, function() {
  console.log('Listening on https://localhost:443');
});

//
// Start an http server and redirect all http to https
//
const httpServer = http.createServer((req, res) => {
	res.writeHead(301,
		{"Location": "https://" + req.headers['host'] + req.url});
	res.end();
});

httpServer.listen(80, () => {
	console.log('Redirecting on http://localhost:80');
});
