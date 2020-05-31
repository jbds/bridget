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
  p.point(0,0);
  // fetch 1/4 of the card pack or less, and move origin 
  // based on pointOfCompass
  switch (pointOfCompass) {
    case 'North':
      g.isHandVisible = gameState.handVisible.north;
      g.myHandArray = window.gameState.pack.filter(obj => {
          return (obj.shuffleIndex >= 0 && obj.shuffleIndex <=12 && obj.lifecycle === 1)
        }
      ); 
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'North'
        );
      // translate and rotate by clock position
      //console.log(clockPosition);
      switch(clockPosition) {
        case '12PM':
          p.translate(0, -(g.canvasHeight / 2));
          p.rotate(p.HALF_PI * 2); 
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
    break;
    case 'East':
      g.isHandVisible = gameState.handVisible.east;
      g.myHandArray = window.gameState.pack.filter(obj => {
          return (obj.shuffleIndex >= 13 && obj.shuffleIndex <=25 && obj.lifecycle === 1)
        }
      ); 
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'East'
        );
      // translate and rotate by clock position
      //console.log(clockPosition);
      switch(clockPosition) {
        case '12PM':
          p.translate(0, -(g.canvasHeight / 2));
          p.rotate(p.HALF_PI * 2); 
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
    break;
    case "South":
      g.isHandVisible = gameState.handVisible.south;
      g.myHandArray = window.gameState.pack.filter(obj => {
          return (obj.shuffleIndex >= 26 && obj.shuffleIndex <=38 && obj.lifecycle == 1)
        }
      );
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'South'
        );
      // translate and rotate by clock position
      //console.log(clockPosition);
      switch(clockPosition) {
        case '12PM':
          p.translate(0, -(g.canvasHeight / 2));
          p.rotate(p.HALF_PI * 2); 
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
    break;
    case 'West':
      g.isHandVisible = gameState.handVisible.west;
      g.myHandArray = window.gameState.pack.filter(obj => {
          return (obj.shuffleIndex >= 39 && obj.shuffleIndex <=51 && obj.lifecycle == 1)
        }
      ); 
      clockPosition = rotationPlusPointOfCompassToClockPosition(
        w.userState.tableRotationDegrees,
        'West'
        );
      // translate and rotate by clock position
      //console.log(clockPosition);
      switch(clockPosition) {
        case '12PM':
          p.translate(0, -(g.canvasHeight / 2));
          p.rotate(p.HALF_PI * 2); 
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
    break;
    case 'Discard':
      g.myDiscardArray = window.gameState.pack.filter(obj => {
          return (obj.lifecycle === 2 )
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
  g.myHandArray.sort((a, b) => {return b.handOrder - a.handOrder});
  // offset the start of card drawing dependent upon qty cards in hand
  p.translate(-((g.myHandArray.length / 2.0))* cardWidth * cardVisibleSegmentWidthToCardWidthRatio, 0);
  g.myHandArray.forEach((obj, i) => {
    // now we can draw a card using each fileName in myHandArray
    let p5img = g.isHandVisible ? g.imgMap.get(obj.fileName) : g.imgMap.get('1B');
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
  // scale to be reviewed
  let m = 0.55;
  let cardWidth = m * g.canvasHeight * g.cardHeightToCanvasHeightRatio / g.cardAspectRatio;
  let cardHeight = m * g.canvasHeight * g.cardHeightToCanvasHeightRatio;
  let cardHeightOffsetFraction = 0.275;
  let cardWidthOffsetFraction = 0.275;
  g.myDiscardArray.forEach((obj, i) => {
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
          p.translate(0, -cardHeight * cardHeightOffsetFraction);
          break;
        // E
        case (obj.shuffleIndex < 26):
          p.translate(cardWidth * cardWidthOffsetFraction, 0);
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
  });
};

let drawLabels = (p, g, w) => {
  let textHeightToCanvasHeightRatio = g.canvasHeight / 30;
  let cardSegmentHeight = g.canvasHeight * g.cardHeightToCanvasHeightRatio * g.cardSegmentHeightToCardRatio;
  p.textSize(textHeightToCanvasHeightRatio);
  p.textFont('Trebuchet MS');
  p.textAlign(p.CENTER, p.CENTER);
  // white, 50% transparent
  p.fill(255, 128);
  // move the origin to table centre
  p.translate(g.canvasWidth / 2, g.canvasHeight / 2);
  w.gameState.locationAndPlayers.forEach((obj, i) => {
    let clockPosition = rotationPlusPointOfCompassToClockPosition(
      w.userState.tableRotationDegrees,
      obj.location
      );
    p.push();
    // translate and rotate by clock position
    switch(clockPosition) {
      case '12PM':
        p.translate(0, -(g.canvasHeight / 2)  + cardSegmentHeight + (textHeightToCanvasHeightRatio * 0.75));
        //p.rotate(p.HALF_PI * 2); 
      break;
      case '3PM':
        p.translate((g.canvasWidth / 2) - cardSegmentHeight - (textHeightToCanvasHeightRatio * 0.75), 0);
        p.rotate(p.HALF_PI * 3);
      break;
      case '6PM':
        p.translate(0, (g.canvasHeight / 2)  - cardSegmentHeight - (textHeightToCanvasHeightRatio * 0.75));
        p.rotate(0); 
      break;
      case '9PM':
        p.translate((-g.canvasWidth / 2) + cardSegmentHeight + (textHeightToCanvasHeightRatio * 0.75), 0);
        p.rotate(p.HALF_PI);
      break;
      default:
        console.log('Unexpected clockPosition argument');
    };
    p.text(
      obj.location + ': ' + obj.player, 
      -g.canvasWidth / 4, 
      -textHeightToCanvasHeightRatio,
      g.canvasWidth / 2,
      textHeightToCanvasHeightRatio * 2 
    );
    p.pop();
  });
};

// HELPER FUNCTION TO CALCULATE CLOCK POSITION
// (tableRotationDegrees (0, 90 etc), pointOfCompass ('North' etc)) =>
// clockPosition ('12PM' etc)
let rotationPlusPointOfCompassToClockPosition = 
  (tableRotationDegrees, pointOfCompass) => {
  let pointOfCompassDegrees = () => {
    switch(pointOfCompass) {
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
        console.log('Unexpected pointOfCompass argument');
        return null;
    };
  };
  let degrees = (tableRotationDegrees + pointOfCompassDegrees()) % 360;
  //console.log(degrees);
  let clockPosition = () => {
    switch (degrees){
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
        console.log('Unexoected degrees argument');
        return null;
    };
  };
  //console.log(clockPosition());
  return clockPosition();
};

exports.drawCards = drawCards;
exports.drawLabels = drawLabels;
