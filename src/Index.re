// test only
//Js.log("Hello, BuckleScript and Reason!");
// test only, this forces this module to use a js import
//Js.log(Extra.myName);

// hack for iOS vh bug, and for detecting Action-Sync
%raw
{|
  const setVh = () => {
    const vh = window.innerHeight * 0.01;
    document.documentElement.style.setProperty('--vh', `${vh}px`);
  };

  window.addEventListener('load', setVh);
  window.addEventListener('resize', setVh);

  window.isLastActionSync = false;
  window.userState = {}; // prevent undefined error before p5 starts up

  // be certain we have the correct version of bundled file aka index.js
  document.title = 'Bridget v0.54';
|};

// all sidebar and biddingWindow events are managed by ReasonReact components (ReasonML)
ReactDOMRe.renderToElementWithId(<App />, "root");

// whereas all canvas related events are managed by p5 libary (Javascript)
%raw
{|
'use strict';
var p5 = require('p5');
// NB needs ./
const SideEffect = require('./SideEffect');
const P5Event = require('./P5Event');


const callbackFunctionForP5 = (p) => {
  // p5 library functions available via injected libary object p
  // decalare all other variables specific to drawing process
  // as properies of a 'global' object g
  const g = {
    // std playing card is 3.5in x 2.25in and svg is 336px x 216px
    cardAspectRatio: 3.5 / 2.25,
    // For card segments on periphery to just meet without overlap
    // we need cardHeightToCanvasHeightRatio of 336 / (2 * 91 + 13 * 37) or approx 0.507
    cardHeightToCanvasHeightRatio: 336 / 663,
    // 91px min height that allows visibility of rank and suit
    cardSegmentHeightToCardRatio: 91 / 336,
  };

  const w = window;
  // maps 1 background image filename and 53 card filenames to full path
  g.imgMap = new Map();


  p.preload = () => {
    // preload runs once first
    g.imgMap.set('GB', p.loadImage('assets/green_baize.jpg'));
    g.imgMap.set('1B', p.loadImage('assets/1B.svg'));
    g.imgMap.set('AS', p.loadImage('assets/AS.svg'));
    g.imgMap.set('KS', p.loadImage('assets/KS.svg'));
    g.imgMap.set('QS', p.loadImage('assets/QS.svg'));
    g.imgMap.set('JS', p.loadImage('assets/JS.svg'));
    g.imgMap.set('TS', p.loadImage('assets/TS.svg'));
    g.imgMap.set('9S', p.loadImage('assets/9S.svg'));
    g.imgMap.set('8S', p.loadImage('assets/8S.svg'));
    g.imgMap.set('7S', p.loadImage('assets/7S.svg'));
    g.imgMap.set('6S', p.loadImage('assets/6S.svg'));
    g.imgMap.set('5S', p.loadImage('assets/5S.svg'));
    g.imgMap.set('4S', p.loadImage('assets/4S.svg'));
    g.imgMap.set('3S', p.loadImage('assets/3S.svg'));
    g.imgMap.set('2S', p.loadImage('assets/2S.svg'));
    g.imgMap.set('AH', p.loadImage('assets/AH.svg'));
    g.imgMap.set('KH', p.loadImage('assets/KH.svg'));
    g.imgMap.set('QH', p.loadImage('assets/QH.svg'));
    g.imgMap.set('JH', p.loadImage('assets/JH.svg'));
    g.imgMap.set('TH', p.loadImage('assets/TH.svg'));
    g.imgMap.set('9H', p.loadImage('assets/9H.svg'));
    g.imgMap.set('8H', p.loadImage('assets/8H.svg'));
    g.imgMap.set('7H', p.loadImage('assets/7H.svg'));
    g.imgMap.set('6H', p.loadImage('assets/6H.svg'));
    g.imgMap.set('5H', p.loadImage('assets/5H.svg'));
    g.imgMap.set('4H', p.loadImage('assets/4H.svg'));
    g.imgMap.set('3H', p.loadImage('assets/3H.svg'));
    g.imgMap.set('2H', p.loadImage('assets/2H.svg'));
    g.imgMap.set('AD', p.loadImage('assets/AD.svg'));
    g.imgMap.set('KD', p.loadImage('assets/KD.svg'));
    g.imgMap.set('QD', p.loadImage('assets/QD.svg'));
    g.imgMap.set('JD', p.loadImage('assets/JD.svg'));
    g.imgMap.set('TD', p.loadImage('assets/TD.svg'));
    g.imgMap.set('9D', p.loadImage('assets/9D.svg'));
    g.imgMap.set('8D', p.loadImage('assets/8D.svg'));
    g.imgMap.set('7D', p.loadImage('assets/7D.svg'));
    g.imgMap.set('6D', p.loadImage('assets/6D.svg'));
    g.imgMap.set('5D', p.loadImage('assets/5D.svg'));
    g.imgMap.set('4D', p.loadImage('assets/4D.svg'));
    g.imgMap.set('3D', p.loadImage('assets/3D.svg'));
    g.imgMap.set('2D', p.loadImage('assets/2D.svg'));
    g.imgMap.set('AC', p.loadImage('assets/AC.svg'));
    g.imgMap.set('KC', p.loadImage('assets/KC.svg'));
    g.imgMap.set('QC', p.loadImage('assets/QC.svg'));
    g.imgMap.set('JC', p.loadImage('assets/JC.svg'));
    g.imgMap.set('TC', p.loadImage('assets/TC.svg'));
    g.imgMap.set('9C', p.loadImage('assets/9C.svg'));
    g.imgMap.set('8C', p.loadImage('assets/8C.svg'));
    g.imgMap.set('7C', p.loadImage('assets/7C.svg'));
    g.imgMap.set('6C', p.loadImage('assets/6C.svg'));
    g.imgMap.set('5C', p.loadImage('assets/5C.svg'));
    g.imgMap.set('4C', p.loadImage('assets/4C.svg'));
    g.imgMap.set('3C', p.loadImage('assets/3C.svg'));
    g.imgMap.set('2C', p.loadImage('assets/2C.svg'));
  }

  p.setup = () => {
    // waits for preload to complete, then runs once
    g.canvasWidth = p.windowHeight;
    g.canvasHeight = p.windowHeight;
    //get a handle on the canvas so we can adjust z-index
    g.cnv = p.createCanvas(g.canvasWidth, g.canvasHeight);
    // z-index has no effect unless we set position to absolute too
    g.cnv.style('position: absolute');
    g.cnv.style('z-index: 1');
    g.cnv.id('mycanvas');
    //let p5btn1 = p.select('#btn1');
    //p5btn1.mousePressed(changeBgColor);
    // init userState
    w.userState = {
      tableRotationDegrees: 0,
      player: "?"
    }
    // fetch default username from persistent store
    document.getElementById('txtMyLoginName').value =
      localStorage.getItem('myLoginName');
    };

  p.draw = () => {
    // z-index of canvas is controlled by gameState
    window.gameState.isBiddingCycle ? g.cnv.style('z-index: -1') : g.cnv.style('z-index: 1');
    // main loop repeats at frame rate
    p.image(g.imgMap.get('GB'), 0, 0, g.canvasWidth, g.canvasHeight)
    SideEffect.drawCards(p, g, w, 'South');
    SideEffect.drawCards(p, g, w, 'West');
    SideEffect.drawCards(p, g, w, 'East');
    SideEffect.drawCards(p, g, w, 'North');
    SideEffect.drawCards(p, g, w, 'Discard');
    SideEffect.drawLabels(p, g, w);

  };

  p.windowResized = () => {
    g.canvasWidth = p.windowHeight;
    g.canvasHeight = p.windowHeight;
    p.resizeCanvas(g.canvasWidth, g.canvasHeight);
  }

  p.mousePressed = ()  => {
    if (p.mouseX <= g.canvasWidth && p.mouseY <= g.canvasHeight) {
      P5Event.mouseDecode(p, g, w);
    }
  }

  // project specific functions

  function changeBgColor() {
    //bgColor = p.color(p.random(255), p.random(255), p.random(255));
    //console.log('Test P5 clicked');
  }

  // draws 4 hand fans - keep for possible re-use
  // function drawHand(pointOfCompass) {
  //   let rotationOriginXPercent, rotationOriginYPercent,
  //       cardWidth, cardHeight,
  //       myHandArray;
  //   p.push()
  //   switch (pointOfCompass) {
  //     case 'North':
  //       rotationOriginXPercent = 50;
  //       rotationOriginYPercent = 0;
  //       break;
  //     case 'East':
  //       rotationOriginXPercent = 100;
  //       rotationOriginYPercent = 50;
  //       break;
  //     case "South":
  //       rotationOriginXPercent = 50;
  //       //rotationOriginYPercent = 500;
  //       rotationOriginYPercent = 100;
  //       break;
  //     case 'West':
  //       rotationOriginXPercent = 0;
  //       rotationOriginYPercent = 50;
  //       break;
  //     default:
  //       console.log('Unexpected pointOfCompass argument');
  //   }
  //   let rotationOriginXPixels = rotationOriginXPercent * g.canvasWidth / 100;
  //   let rotationOriginYPixels = rotationOriginYPercent * g.canvasHeight / 100;
  //   // move the origin to this point
  //   p.translate(rotationOriginXPixels, rotationOriginYPixels);
  //   // for debug, indicate this (translated) point, which may or may not be off the canvas
  //   p.stroke(255);
  //   p.strokeWeight(3);
  //   p.point(0,0);
  //   // draw the card with
  //   // an x offset from origin of 1/4 of card width
  //   // a y offeset from origin of N * card height
  //   // (found by trial and error to give realistic card fan shape)
  //   cardWidth = g.canvasHeight * g.cardHeightToCanvasHeightRatio / g.cardAspectRatio;
  //   cardHeight = g.canvasHeight * g.cardHeightToCanvasHeightRatio;
  //   switch (pointOfCompass) {
  //     case 'North':
  //       myHandArray = window.gameState.pack.filter(obj => {
  //           return (obj.shuffleIndex >= 0 && obj.shuffleIndex <=12)
  //         }
  //       );
  //       break;
  //     case 'East':
  //       myHandArray = window.gameState.pack.filter(obj => {
  //           return (obj.shuffleIndex >= 13 && obj.shuffleIndex <=25)
  //         }
  //       );
  //       break;
  //     case "South":
  //       myHandArray = window.gameState.pack.filter(obj => {
  //           return (obj.shuffleIndex >= 26 && obj.shuffleIndex <=38)
  //         }
  //       );
  //       break;
  //     case 'West':
  //       myHandArray = window.gameState.pack.filter(obj => {
  //           return (obj.shuffleIndex >= 39 && obj.shuffleIndex <=51)
  //         }
  //       );
  //       break;
  //     default:
  //       console.log('Unexpected pointOfCompass argument');
  //   }
  //   // 13 records selected, but we need to reorder by handOrder
  //   myHandArray.sort((a, b) => {return b.handOrder - a.handOrder});
  //   // 13 records in correct hand order by suit and rank.
  //   // setup the rotation angle increment
  //   //let rotationDeltaRadians = p.radians(0.95);
  //   let rotationDeltaRadians = p.radians(3.5);
  //   // apply an initial rotation offset based on array length and pointOfCompass
  //   switch (pointOfCompass) {
  //     case 'North':
  //       p.rotate((-rotationDeltaRadians * ((myHandArray.length / 2.0) - 1.5)) + p.PI);
  //       break;
  //     case 'East':
  //       p.rotate((-rotationDeltaRadians * ((myHandArray.length / 2.0) - 1.5)) - p.HALF_PI);
  //       break;
  //     case 'South':
  //       p.rotate(-rotationDeltaRadians * ((myHandArray.length / 2.0) - 1.5));
  //       break;
  //     case 'West':
  //       p.rotate((-rotationDeltaRadians * ((myHandArray.length / 2.0) - 1.5)) + p.HALF_PI);
  //       break;
  //     default:
  //       console.log('Unexpected pointOfCompass argument');
  //   }
  //   myHandArray.forEach((obj, i) => {
  //     // now we can draw a card using each fileName in myHandArray
  //     let p5img = g.imgMap.get(obj.fileName);
  //     //p.image(p5img, -cardWidth / 4 , -cardHeight * 6.26, cardWidth, cardHeight);
  //     p.image(p5img, -cardWidth / 4 , -cardHeight * 1.5, cardWidth, cardHeight);
  //     // note that each rotation is cumulative
  //     p.rotate(rotationDeltaRadians);
  //   });
  //   p.pop();
  // }
};

let myP5Instance = new p5(callbackFunctionForP5);
|};
