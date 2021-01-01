'use strict';

var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var App$ReasonReactExamples = require("./Components/App.bs.js");

const setVh = () => {
    const vh = window.innerHeight * 0.01;
    document.documentElement.style.setProperty('--vh', `${vh}px`);
  };

  window.addEventListener('load', setVh);
  window.addEventListener('resize', setVh);

  window.isLastActionSync = false;
  window.userState = {}; // prevent undefined error before p5 starts up

  // be certain we have the correct version of bundled file aka index.js
  document.title = 'Bridget v3.37';

  // for transitions we need to move card constants up to global scope
  // std playing card is 3.5in x 2.25in and svg is 336px x 216px
  window.cardAspectRatio = 3.5 / 2.25;
  // For card segments on periphery to just meet without overlap
  // we need cardHeightToCanvasHeightRatio of 336 / (2 * 91 + 13 * 37) or approx 0.507
  window.cardHeightToCanvasHeightRatio = 336 / 663;
  // 91px min height that allows visibility of rank and suit
  window.cardSegmentHeightToCardRatio = 91 / 336;
  // discarded cards magnification factor
  window.m = 0.65;
  // discarded cards relative offset
  window.cardHeightOffsetFraction = 0.275;
  window.cardWidthOffsetFraction = 0.5;
  // for refs to canvasHeight and canvasWidth just use window.innerHeight
  // smaller cards at 3PM and 9PM
  window.threePMninePMshrinkFactor = 0.83;
  // expanded cards at 12PM and 6PM
  window.twelvePMsixPMgrowthFactor = 1.28;
  //
  window.cardSegmentWidthToCardHeightRatio = 37 / 336;
;

ReactDOMRe.renderToElementWithId(React.createElement(App$ReasonReactExamples.make, { }), "root");

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
      // scope of all the following changed to be window scope
      // std playing card is 3.5in x 2.25in and svg is 336px x 216px
      //cardAspectRatio: 3.5 / 2.25,
      // For card segments on periphery to just meet without overlap
      // we need cardHeightToCanvasHeightRatio of 336 / (2 * 91 + 13 * 37) or approx 0.507
      //cardHeightToCanvasHeightRatio: 336 / 663,
      // 91px min height that allows visibility of rank and suit
      //cardSegmentHeightToCardRatio: 91 / 336,
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
      console.log('resize event');
      console.log(gameState);
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

  };

  let myP5Instance = new p5(callbackFunctionForP5);
;

/*  Not a pure module */
