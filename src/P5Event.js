'use strict';

let mouseDecode = (p, g, w) => {
  // x and y ranges define 4 regions of interest
  // NB 13 segments means lower bound 0 and upper bound 13
  let cardSegmentHeightToCanvasHeightRatio =
    g.cardSegmentHeightToCardRatio * g.cardHeightToCanvasHeightRatio;
  let cardSegmentIndex;
  let cardSegmentIndexAdjusted;
  let myHandArray;
  const myHandArrayN = window.gameState.pack.filter(obj => {
    return (obj.shuffleIndex >= 0 && obj.shuffleIndex <= 12 && obj.lifecycle === 1)
  });
  const myHandArrayE = window.gameState.pack.filter(obj => {
    return (obj.shuffleIndex >= 13 && obj.shuffleIndex <= 25 && obj.lifecycle === 1)
  });
  const myHandArrayS = window.gameState.pack.filter(obj => {
    return (obj.shuffleIndex >= 26 && obj.shuffleIndex <=38 && obj.lifecycle === 1)
  });
  const myHandArrayW = window.gameState.pack.filter(obj => {
    return (obj.shuffleIndex >= 39 && obj.shuffleIndex <= 51 && obj.lifecycle === 1)
  });
//console.log('mouse decode');
  switch (true) {
    // TABLE TOP
    case (p.mouseY <= cardSegmentHeightToCanvasHeightRatio * g.canvasHeight &&
      p.mouseX >= cardSegmentHeightToCanvasHeightRatio * g.canvasHeight &&
      p.mouseX < (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight
    ):
    cardSegmentIndex = p.map(
      p.mouseX, 
      cardSegmentHeightToCanvasHeightRatio * g.canvasHeight,
      (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight,
      13, // 0, Dummy hand will be reversed
      0   // 13
    );
    // this floating number needs an offset based on hand array length
    // fetch array dependent on card table rotation
    switch(w.userState.tableRotationDegrees) {
      case 0:
        myHandArray = myHandArrayN;
        break;
      case 90:
        myHandArray = myHandArrayW;
        break;
      case 180:
        myHandArray = myHandArrayS;
        break;
      case 270:
        myHandArray = myHandArrayE;
      break;
      default:
        console.log('Unexpected tableRotationDegrees');
    }
    cardSegmentIndexAdjusted = Math.floor(cardSegmentIndex - ((13 - myHandArray.length) / 2));
    if (cardSegmentIndexAdjusted < 0 || cardSegmentIndexAdjusted > (myHandArray.length - 1)) {
      // do nothing
    } else {
      //console.log('top area, indexAdjustedAndConstrained=' + cardSegmentIndexAdjusted);
      convertAdjustedIndexToCardKey(cardSegmentIndexAdjusted, myHandArray);
    }
    break;
    // TABLE RHS
    case (p.mouseX >= (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight &&
          p.mouseY >= cardSegmentHeightToCanvasHeightRatio * g.canvasHeight &&
          p.mouseY < (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight
      ):
      cardSegmentIndex = p.map(
        p.mouseY, 
        cardSegmentHeightToCanvasHeightRatio * g.canvasHeight,
        (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight,
        13,
        0
      );
      // this floating number needs an offset based on hand array length
    // fetch array dependent on card table rotation
    switch(w.userState.tableRotationDegrees) {
      case 0:
        myHandArray = myHandArrayE;
        break;
      case 90:
        myHandArray = myHandArrayN
        break;
      case 180:
        myHandArray = myHandArrayW;
        break;
      case 270:
        myHandArray = myHandArrayS;
      break;
      default:
        console.log('Unexpected tableRotationDegrees');
    }
      cardSegmentIndexAdjusted = Math.floor(cardSegmentIndex - ((13 - myHandArray.length) / 2));
      if (cardSegmentIndexAdjusted < 0 || cardSegmentIndexAdjusted > (myHandArray.length - 1)) {
        // do nothing
      } else {
        //console.log('right area, indexAdjustedAndConstrained=' + cardSegmentIndexAdjusted);
        convertAdjustedIndexToCardKey(cardSegmentIndexAdjusted, myHandArray);
      }
      break;
    // TABLE BOTTOM
    case (p.mouseY >= (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight &&
          p.mouseX >= cardSegmentHeightToCanvasHeightRatio * g.canvasHeight &&
          p.mouseX < (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight
        ):
      cardSegmentIndex = p.map(
        p.mouseX, 
        cardSegmentHeightToCanvasHeightRatio * g.canvasHeight,
        (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight,
        0,
        13
      );
      // this floating number needs an offset based on hand array length
    // fetch array dependent on card table rotation
    switch(w.userState.tableRotationDegrees) {
      case 0:
        myHandArray = myHandArrayS;
        break;
      case 90:
        myHandArray = myHandArrayE;
        break;
      case 180:
        myHandArray = myHandArrayN;
        break;
      case 270:
        myHandArray = myHandArrayW;
      break;
      default:
        console.log('Unexpected tableRotationDegrees');
    }
      cardSegmentIndexAdjusted = Math.floor(cardSegmentIndex - ((13 - myHandArray.length) / 2));
      if (cardSegmentIndexAdjusted < 0 || cardSegmentIndexAdjusted > (myHandArray.length - 1)) {
        // do nothing
      } else {
        //console.log('bottom area, indexAdjustedAndConstrained=' + cardSegmentIndexAdjusted);
        convertAdjustedIndexToCardKey(cardSegmentIndexAdjusted, myHandArray);
      }
    break;
    // TABLE LHS
    case (p.mouseX <= cardSegmentHeightToCanvasHeightRatio * g.canvasHeight &&
          p.mouseY >= cardSegmentHeightToCanvasHeightRatio * g.canvasHeight &&
          p.mouseY < (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight
      ):
      cardSegmentIndex = p.map(
        p.mouseY, 
        cardSegmentHeightToCanvasHeightRatio * g.canvasHeight,
        (1 - cardSegmentHeightToCanvasHeightRatio) * g.canvasHeight,
        0,
        13
      );
      // this floating number needs an offset based on hand array length
      // fetch array dependent on card table rotation
      switch(w.userState.tableRotationDegrees) {
        case 0:
          myHandArray = myHandArrayW;
          break;
        case 90:
          myHandArray = myHandArrayS;
          break;
        case 180:
          myHandArray = myHandArrayE;
          break;
        case 270:
          myHandArray = myHandArrayN;
        break;
        default:
          console.log('Unexpected tableRotationDegrees');
      }
      cardSegmentIndexAdjusted = Math.floor(cardSegmentIndex - ((13 - myHandArray.length) / 2));
      if (cardSegmentIndexAdjusted < 0 || cardSegmentIndexAdjusted > (myHandArray.length - 1)) {
        // do nothing
      } else {
        //console.log('left area, indexAdjustedAndConstrained=' + cardSegmentIndexAdjusted);
        convertAdjustedIndexToCardKey(cardSegmentIndexAdjusted, myHandArray);
      }
      break;
    default:
    //console.log('Do-nothing mouseX or mouseY argument')
  };
};

let convertAdjustedIndexToCardKey = (cardSegmentIndexAdjusted, myHandArray) => {
  // sort the array in the same way as cards are displayed
  myHandArray.sort((a, b) => {return b.handOrder - a.handOrder});
  let myCard = myHandArray[cardSegmentIndexAdjusted];
  console.log(myCard.fileName);
  // NO - always update via ReasonML action
  // at this point we know which card was clicked
  // so we can update the (mutable) js gameState object
  // let pack = gameState.pack;
  // pack.find((value, index) => {
  //   if (value.fileName === myCard.fileName) {
  //     // lifecycle Discard = 2 in js
  //     gameState.pack[index].lifecycle = 2;
  //     console.log('found card and set lifecycle to 2');
  //   }
  // });

  window.discardFileName = myCard.fileName
  console.log('isValidDiscardFromLocalPlayer:');
  console.log(isValidDiscardFromLocalPlayer());
  if (isValidDiscardFromLocalPlayer()) {
    // prepare a second action after a delay
    //setTimeout(function(){alert('Yay');}, 750);
    setTimeout(function(){document.getElementById('btnEndTrick').click();}, 750);
    // dispatch the Discard action via a hidden key on the sidebar
    document.getElementById('btnDiscard').click();
  }
};

  // helper function for deciding which discard clicks are valid
  let isValidDiscardFromLocalPlayer = () => {
    // may return empty array
    let userPointOfCompassWrappedInArray = gameState.pointOfCompassAndPlayers.filter(
      x => x.player === userState.player
    );
    if (userPointOfCompassWrappedInArray.length === 0) {
      console.log('userPointOfCompassWrappedInArray is empty');
      return false;
    }
    let userPointOfCompass = userPointOfCompassWrappedInArray[0].pointOfCompass;
    //console.log('userPointOfCompass: ' + userPointOfCompass);
    // now we need to know cardPointOfCompass
    let cardPointOfCompass;
    let card = gameState.pack.find(obj => obj.fileName === window.discardFileName);
    if (card.shuffleIndex >= 0 && card.shuffleIndex <= 12 && card.lifecycle === 1) {
      cardPointOfCompass = 'North';
    } else if (card.shuffleIndex >= 13 && card.shuffleIndex <= 25 && card.lifecycle === 1) {
      cardPointOfCompass = 'East';
    } else if (card.shuffleIndex >= 26 && card.shuffleIndex <= 38 && card.lifecycle === 1) {
      cardPointOfCompass = 'South';
    } else if (card.shuffleIndex >= 39 && card.shuffleIndex <= 51 && card.lifecycle === 1) {
      cardPointOfCompass = 'West';
    } else {
      console.log('Unexpected shuffleIndex in window.discardFileName');
    }
    return userPointOfCompass === cardPointOfCompass && gameState.isBiddingCycle === false ? true : false;
  };


exports.mouseDecode = mouseDecode;