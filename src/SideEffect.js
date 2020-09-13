'use strict';
// p is p5 library, g is drawing global properties
let drawCards = (p, g, w, pointOfCompass) => {
  let clockPosition;
  p.push();
  // move the origin to table centre
  p.translate(g.canvasWidth / 2, g.canvasHeight / 2);
  // for debug, indicate this point
  p.stroke(255);
  p.strokeWeight(5);
  //p.point(0,0);
  // helper function for deciding which way up cards are
  let shouldHandBeUp = (poc) => {
    // may return empty array
    let userPointOfCompassWrappedInArray = gameState.pointOfCompassAndPlayers.filter(
      x => x.player === userState.player
    );
    if (userPointOfCompassWrappedInArray.length === 0) {
      return false;
    }
    let userPointOfCompass = userPointOfCompassWrappedInArray[0].pointOfCompass;
    return (
      // every player can see their own hand
      userPointOfCompass === poc
        ||
        // observers can see all hands
        userPointOfCompass === 'Observer'
        ||
        // every player can see Dummy once lead card has been played
        // check for poc equal to Dummy poc AND isDummyVisible
        (
          poc === getDummyPocByDeclarer(w.gameState.declarer)
          &&
          gameState.isDummyVisible === true
        )
        ||
        // the dummy can observe the declarer's hand for interest only
        (
          poc === w.gameState.declarer
          &&
          userPointOfCompass === getDummyPocByDeclarer(w.gameState.declarer)
        )
        ?
        true
        :
        false
    );
  };
  // helper function to see if this is the Dummy hand
  let isDummyHand =
    pointOfCompass === getDummyPocByDeclarer(w.gameState.declarer) ? true : false;
  // fetch 1/4 of the card pack or less
  switch (pointOfCompass) {
    case 'North':
      // handVisible is now used to show all cards on "ReviewDeal" message
      //g.isHandFaceUp = gameState.handVisible.north;
      g.isHandFaceUp = shouldHandBeUp('North') || gameState.handVisible.north;
      g.myHandArray = window.gameState.pack.filter(obj => {
        return (obj.shuffleIndex >= 0 && obj.shuffleIndex <= 12 && obj.lifecycle === 1)
      }
      );
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'North'
      );
      translateAndRotateByClockPosition(clockPosition, p, g, isDummyHand);
      break;
    case 'East':
      //g.isHandFaceUp = gameState.handVisible.east;
      g.isHandFaceUp = shouldHandBeUp('East') || gameState.handVisible.east;
      g.myHandArray = window.gameState.pack.filter(obj => {
        return (obj.shuffleIndex >= 13 && obj.shuffleIndex <= 25 && obj.lifecycle === 1)
      }
      );
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'East'
      );
      translateAndRotateByClockPosition(clockPosition, p, g, isDummyHand);
      break;
    case "South":
      //g.isHandFaceUp = gameState.handVisible.south;
      g.isHandFaceUp = shouldHandBeUp('South') || gameState.handVisible.south;
      g.myHandArray = window.gameState.pack.filter(obj => {
        return (obj.shuffleIndex >= 26 && obj.shuffleIndex <= 38 && obj.lifecycle == 1)
      }
      );
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'South'
      );
      translateAndRotateByClockPosition(clockPosition, p, g, isDummyHand);
      break;
    case 'West':
      //g.isHandFaceUp = gameState.handVisible.west;
      g.isHandFaceUp = shouldHandBeUp('West') || gameState.handVisible.west;
      g.myHandArray = window.gameState.pack.filter(obj => {
        return (obj.shuffleIndex >= 39 && obj.shuffleIndex <= 51 && obj.lifecycle == 1)
      }
      );
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'West'
      );
      translateAndRotateByClockPosition(clockPosition, p, g, isDummyHand);
      break;
    case 'Discard':
      g.myDiscardArray = window.gameState.pack.filter(obj => {
        return (obj.lifecycle === 2)
      });
      break;
    default:
      console.log('Unexpected pointOfCompass argument xx');
  }
  if (pointOfCompass != 'Discard') {
    paintHandArray(p, g);
  } else {
    paintDiscardArray(p, g, w);
  }
  p.pop();
}

let paintHandArray = (p, g) => {
  let cardWidth = g.canvasHeight * g.cardHeightToCanvasHeightRatio / g.cardAspectRatio;
  let cardHeight = g.canvasHeight * g.cardHeightToCanvasHeightRatio;
  // 37px max width before honour cards show pic border
  // NB visible segment has 20% added for overlap on all except last card
  let cardVisibleSegmentWidthToCardWidthRatio = 37 / 216;
  // 13 records or less - need to reorder by handOrder
  g.myHandArray.sort((a, b) => { return b.handOrder - a.handOrder });
  // offset the start of card drawing dependent upon qty cards in hand
  p.translate(-((g.myHandArray.length / 2.0)) * cardWidth * cardVisibleSegmentWidthToCardWidthRatio, 0);
  g.myHandArray.forEach((obj, i) => {
    // now we can draw a card using each fileName in myHandArray
    let p5img = g.isHandFaceUp ? g.imgMap.get(obj.fileName) : g.imgMap.get('1B');
    // last card in hand is a special case, as we do not want the overlap
    i !== g.myHandArray.length - 1
      ?
      p.image(
        p5img,
        0,
        -cardHeight * g.cardSegmentHeightToCardRatio,
        cardWidth * cardVisibleSegmentWidthToCardWidthRatio * 1.2,
        cardHeight * g.cardSegmentHeightToCardRatio,
        0,
        0,
        37 * 1.2,
        91
      )
      :
      p.image(
        p5img,
        0,
        -cardHeight * g.cardSegmentHeightToCardRatio,
        cardWidth * cardVisibleSegmentWidthToCardWidthRatio,
        cardHeight * g.cardSegmentHeightToCardRatio,
        0,
        0,
        37,
        91
      )
      ;
    // note that each rotation is cumulative
    //p.rotate(rotationDeltaRadians);
    // note that each translation is cumulative
    p.translate(cardWidth * cardVisibleSegmentWidthToCardWidthRatio, 0);
  });
};

let paintDiscardArray = (p, g, w) => {
  //console.log('discarding');
  // scale to be reviewed
  let m = 0.65; //0.55;
  let cardWidth = m * g.canvasHeight * g.cardHeightToCanvasHeightRatio / g.cardAspectRatio;
  let cardHeight = m * g.canvasHeight * g.cardHeightToCanvasHeightRatio;
  let cardHeightOffsetFraction = 0.275;
  let cardWidthOffsetFraction = 0.50;
  // we need to paint the discarded cards in a specific order
  // so sort in-place N, E, S, W for shuffleIndex <=12, <=25, <=38, <=51
  // the ordering here was corrected empirically!
  g.myDiscardArray.sort((a, b) => (a.shuffleIndex > b.shuffleIndex ? 1 : -1));
  // at this point, the ordering gives correct display of cards if discard starts from North
  //console.log(g.myDiscardArray);
  // now deep copy to avoid messing with myDiscardArray
  let arr = JSON.parse(JSON.stringify(g.myDiscardArray));
  //console.log(arr);
  let initialPoc = w.gameState.discardPointOfCompass; // 'North' etc
  let arrTemp = [];
  // arr can be any length between 0 and 4
  // any changes here must NOT mutate arr
  switch (arr.length) {
    case 0:
      // do nothing use arrTemp as is
      break;
    case 1:
      // first card will always be 'on top' (on bottom too!) which is what we want
      arrTemp.push(arr[0]);
      break;
    case 2:
      if (initialPoc === 'North') {
        // the order N then E is fine as-is
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
      } else if (initialPoc === 'East') {
        // the order E then S is fine as-is
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
      } else if (initialPoc === 'South') {
        // the order S then W is fine as-is
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
      } else if (initialPoc === 'West') {
        // the order W N needs adjust
        arrTemp.push(arr[1]);
        arrTemp.push(arr[0]);
      } else {
        // error
      }
      break;
    case 3:
      if (initialPoc === 'North') {
        // the order N E S is fine as-is
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
        arrTemp.push(arr[2]);
      } else if (initialPoc === 'East') {
        // the order E S W is fine as-is
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
        arrTemp.push(arr[2]);
      } else if (initialPoc === 'South') {
        // the order N S W needs adjusting..
        arrTemp.push(arr[1]);
        arrTemp.push(arr[2]);
        arrTemp.push(arr[0]);
      } else if (initialPoc === 'West') {
        // the order N E W needs adjusting..
        arrTemp.push(arr[2]);
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
      } else {
        // error
      }
      break;
    case 4:
      if (initialPoc === 'North') {
        // the order N E S W is fine as-is
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
        arrTemp.push(arr[2]);
        arrTemp.push(arr[3]);
      } else if (initialPoc === 'East') {
        // the order N E S W needs adjusting..
        // N needs to go last
        arrTemp.push(arr[1]);
        arrTemp.push(arr[2]);
        arrTemp.push(arr[3]);
        arrTemp.push(arr[0]);
      } else if (initialPoc === 'South') {
        // the order N E S W needs adjusting..
        arrTemp.push(arr[2]);
        arrTemp.push(arr[3]);
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
      } else if (initialPoc === 'West') {
        // the order N E S W needs adjusting..
        arrTemp.push(arr[3]);
        arrTemp.push(arr[0]);
        arrTemp.push(arr[1]);
        arrTemp.push(arr[2]);
      } else {
        // error
      }
      break;
  }
  // use i for explicit order
  //arr.forEach((obj, i) => {
  // reverse the array of objects first
  //arr.reverse();
  for (var i = 0; i < arrTemp.length; i++) {
    let obj = arrTemp[i];
    // now we can draw a card using each fileName in myDiscardArray
    // position of card depends on range of shuffleIndex and rotation
    // but these two variables are orthogonal
    p.push();
    switch (w.userState.tableRotationDegrees) {
      case 0:
        p.rotate(0);
        break;
      case 90:
        p.rotate(p.HALF_PI);
        break;
      case 180:
        p.rotate(p.HALF_PI * 2);
        break;
      case 270:
        p.rotate(p.HALF_PI * 3);
        break;
      default:
        console.log('Unexpected tableRotation argument ');
    }
    switch (true) {
      // N
      case (obj.shuffleIndex < 13):
        // good for all rotations, because x=x and y=y all angles
        //p.translate(0, -cardHeight * cardHeightOffsetFraction);
        //p.translate(0, g.northDiscardInitialY);
        w.gameState.transition.northDiscardY = p.lerp(w.gameState.transition.northDiscardY, -cardHeight * cardHeightOffsetFraction, 0.20);
        p.translate(0, w.gameState.transition.northDiscardY);
        break;
      // E
      case (obj.shuffleIndex < 26):
        //p.translate(cardWidth * cardWidthOffsetFraction, 0);
        w.gameState.transition.eastDiscardX = p.lerp(w.gameState.transition.eastDiscardX, cardWidth * cardWidthOffsetFraction, 0.20);
        p.translate(w.gameState.transition.eastDiscardX, 0);
        break;
      // S
      case (obj.shuffleIndex < 39):
        p.translate(0, cardHeight * cardHeightOffsetFraction);
        break;
      // W
      case (obj.shuffleIndex < 52):
        p.translate(-cardWidth * cardWidthOffsetFraction, 0);
        break;
      default:
        console.log('Unexpected shuffleIndex argument');
    }
    let p5img = g.imgMap.get(obj.fileName);
    p.image(p5img, -cardWidth / 2, -cardHeight / 2, cardWidth, cardHeight);
    p.pop();
  }
};

let drawLabels = (p, g, w) => {
  // avoid error 
  if (!w.gameState.pointOfCompassAndPlayers) {
    //console.log('No labels defined, abort drawLabels');
    return;
  }
  let textHeightToCanvasHeightRatio = g.canvasHeight / 30;
  let cardSegmentHeight = g.canvasHeight * g.cardHeightToCanvasHeightRatio * g.cardSegmentHeightToCardRatio;
  p.textSize(textHeightToCanvasHeightRatio);
  p.textFont('Trebuchet MS');
  p.textAlign(p.CENTER, p.CENTER);
  // white, 50% transparent
  p.fill(255, 128);
  // move the origin to table centre
  p.translate(g.canvasWidth / 2, g.canvasHeight / 2);
  w.gameState.pointOfCompassAndPlayers.forEach((obj, i) => {
    // ignore Observer
    if (obj.pointOfCompass !== 'Observer') {
      let clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        obj.pointOfCompass
      );
      p.push();
      // translate and rotate by clock position
      switch (clockPosition) {
        case '12PM':
          p.translate(0, -(g.canvasHeight / 2) + cardSegmentHeight + (textHeightToCanvasHeightRatio * 0.75));
          //p.rotate(p.HALF_PI * 2); 
          break;
        case '3PM':
          p.translate((g.canvasWidth / 2) - cardSegmentHeight - (textHeightToCanvasHeightRatio * 0.75), 0);
          p.rotate(p.HALF_PI * 3);
          break;
        case '6PM':
          p.translate(0, (g.canvasHeight / 2) - cardSegmentHeight - (textHeightToCanvasHeightRatio * 0.75));
          p.rotate(0);
          break;
        case '9PM':
          p.translate((-g.canvasWidth / 2) + cardSegmentHeight + (textHeightToCanvasHeightRatio * 0.75), 0);
          p.rotate(p.HALF_PI);
          break;
        default:
          console.log('Unexpected clockPosition argument');
      };
      // do not draw label if pointOfCompass is not known
      // add dealer if appropriate
      let positionPlayerDealer;
      if (w.gameState.dealer === obj.pointOfCompass && w.gameState.declarer === obj.pointOfCompass) {
        positionPlayerDealer = 'Dealer + Declarer ' + obj.pointOfCompass + ' ' + obj.player
      } else if (w.gameState.dealer === obj.pointOfCompass && getDummyPocByDeclarer(w.gameState.declarer) === obj.pointOfCompass) {
        positionPlayerDealer = 'Dealer + Dummy ' + obj.pointOfCompass + ' ' + obj.player
      } else if (w.gameState.dealer === obj.pointOfCompass) {
        positionPlayerDealer = 'Dealer ' + obj.pointOfCompass + ' ' + obj.player
      } else if (w.gameState.declarer === obj.pointOfCompass) {
        positionPlayerDealer = 'Declarer ' + obj.pointOfCompass + ' ' + obj.player
      } else if (getDummyPocByDeclarer(w.gameState.declarer) === obj.pointOfCompass) {
        positionPlayerDealer = 'Dummy ' + obj.pointOfCompass + ' ' + obj.player
      } else {
        positionPlayerDealer = obj.pointOfCompass + ' ' + obj.player;
      }
      if (w.gameState.activePointOfCompass === obj.pointOfCompass) {
        // was white, 12% transparent p.fill(255, 240)
        // now yellow, 0% transparent (ref Jill)
        p.fill(255, 255, 0, 255);
      } else {
        // white, 62% transparent
        p.fill(255, 96);
      }
      if (obj.pointOfCompass != '') {
        p.text(
          positionPlayerDealer,
          -g.canvasWidth / 4,
          -textHeightToCanvasHeightRatio,
          g.canvasWidth / 2,
          textHeightToCanvasHeightRatio * 2
        );
      } else {
        // skip
      }
      p.pop();
    }
  });
};

// HELPER FUNCTION TO CALCULATE CLOCK POSITION
// (tableRotationDegrees (0, 90 etc), pointOfCompass ('North' etc)) =>
// clockPosition ('12PM' etc)
let rotationPlusPointOfCompassToClockPosition =
  (tableRotationDegrees, pointOfCompass) => {
    let pointOfCompassDegrees = () => {
      switch (pointOfCompass) {
        case 'North':
          return 0;
          break;
        case 'East':
          return 90;
          break;
        case 'South':
          return 180;
          break;
        case 'West':
          return 270
          break;
        default:
          // this can occur by design before players are assigned
          //console.log('Unexpected pointOfCompass argument');
          return null;
      };
    };
    let degrees = (tableRotationDegrees + pointOfCompassDegrees()) % 360;
    //console.log(degrees);
    let clockPosition = () => {
      switch (degrees) {
        case 0:
          return '12PM';
          break;
        case 90:
          return '3PM';
          break;
        case 180:
          return '6PM';
          break;
        case 270:
          return '9PM';
          break;
        default:
          console.log('Unexpected degrees argument');
          return null;
      };
    };
    //console.log(clockPosition());
    return clockPosition();
  };

// HELPER FUNCTION FOR drawCards
let translateAndRotateByClockPosition = (clockPosition, p, g, isDummyHand) => {
  switch (clockPosition) {
    case '12PM':
      // isDummyHand 
      // ? 
      // p.translate(0, -(g.canvasHeight / 2) + (g.canvasHeight * g.cardHeightToCanvasHeightRatio * g.cardSegmentHeightToCardRatio)) 
      // : 
      // p.translate(0, -(g.canvasHeight / 2));
      // isDummyHand 
      // ? 
      // p.rotate(p.HALF_PI * 4) 
      // : 
      // p.rotate(p.HALF_PI * 2); 
      // we always want cards at 12PM to be inverted!
      // tweak offset appropriately
      p.translate(0, -(g.canvasHeight / 2) + (g.canvasHeight * g.cardHeightToCanvasHeightRatio * g.cardSegmentHeightToCardRatio));
      // no rotation!
      break;
    case '3PM':
      p.translate((g.canvasWidth / 2), 0);
      p.rotate(p.HALF_PI * 3);
      break;
    case '6PM':
      p.translate(0, (g.canvasHeight / 2));
      p.rotate(0);
      break;
    case '9PM':
      p.translate((-g.canvasWidth / 2), 0);
      p.rotate(p.HALF_PI);
      break;
    default:
      console.log('Unexpected clockPosition argument');
  };
};

// HELPER FUNC FOR drawLabels
let getDummyPocByDeclarer = (poc) => {
  switch (poc) {
    case 'West':
      return 'East';
      break;
    case 'North':
      return 'South';
      break;
    case 'East':
      return 'West';
      break;
    case 'South':
      return 'North';
      break;
    default:
      return 'X'
  }
};

// HELPER FUNC FOR drawCards
let getLeadPointOfCompassFromDeclarer = (poc) => {
  switch (poc) {
    case 'West':
      return 'North';
      break;
    case 'North':
      return 'East';
      break;
    case 'East':
      return 'South';
      break;
    case 'South':
      return 'West';
      break;
    default:
      return 'X'
  }
};

exports.drawCards = drawCards;
exports.drawLabels = drawLabels;
