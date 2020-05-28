'use strict';
// p is p5 library, g is drawing global properties
let drawCards = (p, g, w, pointOfCompass) => {
  // std playing card is 3.5in x 2.25in and svg is 336px x 216px
  g.cardAspectRatio = 3.5 / 2.25;
  // For card segments on periphery to just meet without overlap
  // we need cardHeightToCanvasHeightRatio of 336 / (2 * 91 + 13 * 37) or approx 0.507
  g.cardHeightToCanvasHeightRatio = 336 / 663;
  let rotationOriginXPercent;
  let rotationOriginYPercent;
  // 91px min height that allows visibility of rank and suit
  g.cardSegmentHeightToCardRatio = 91 / 336;
  let myDiscardArray;
  p.push();
  // origin is pointOfCompass dependent, Dummy (N?) is special case
  // we want to use a common starting point (50%, 50%) or (canvasWidth /2, canvasHeight / 2)
  // switch (pointOfCompass) {
  //   case 'North':
  //     rotationOriginXPercent = 50; 
  //     // offset by height of cardsegment 91px
  //     rotationOriginYPercent = 0 + 
  //       100 * g.cardSegmentHeightToCardRatio * g.cardHeightToCanvasHeightRatio; 
  //     break;
  //   case 'East':
  //     rotationOriginXPercent = 100; 
  //     rotationOriginYPercent = 50; 
  //     break;
  //   case "South":
  //     rotationOriginXPercent = 50; 
  //     rotationOriginYPercent = 100; 
  //     break;
  //   case 'West':
  //     rotationOriginXPercent = 0; 
  //     rotationOriginYPercent = 50; 
  //     break;
  //   case 'Centre':
  //     rotationOriginXPercent = 50;
  //     rotationOriginYPercent = 50;
  //     break;
  //   default:
  //     console.log('Unexpected pointOfCompass argument');
  // }
  // let rotationOriginXPixels = rotationOriginXPercent * g.canvasWidth / 100;
  // let rotationOriginYPixels = rotationOriginYPercent * g.canvasHeight / 100;
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
      switch (w.userState.tableRotationDegrees) {
        case 0: 
          p.translate(0, -g.canvasHeight / 2)
          p.rotate(2 * p.HALF_PI); 
          break;
        case 90: 
          p.translate(g.canvasWidth / 2, 0);
          p.rotate(3 * p.HALF_PI);
          break;
        case 180:
          p.translate(0, g.canvasHeight / 2);
          p.rotate(0);
          break;
        case 270:
          p.translate(-g.canvasWidth / 2, 0);
          p.rotate(p.HALF_PI);
          break;
        default:
          console.log('Unexpected tableRotation argument ');
      }
      break;
    case 'East':
      g.isHandVisible = gameState.handVisible.east;
      g.myHandArray = window.gameState.pack.filter(obj => {
          return (obj.shuffleIndex >= 13 && obj.shuffleIndex <=25 && obj.lifecycle === 1)
        }
      ); 
      switch (w.userState.tableRotationDegrees) {
        case 0: 
          p.translate(g.canvasWidth / 2, 0)
          p.rotate(-p.HALF_PI); 
          break;
        case 90: 
          p.translate(0, g.canvasHeight / 2);
          p.rotate(0);
          break;
        case 180:
          p.translate(-g.canvasWidth / 2, 0);
          p.rotate(p.HALF_PI);
          break;
        case 270:
          p.translate(0, -g.canvasHeight / 2);
          p.rotate(2 * p.HALF_PI);
          break;
        default:
          console.log('Unexpected tableRotation argument ');
      }
      break;
    case "South":
      g.isHandVisible = gameState.handVisible.south;
      g.myHandArray = window.gameState.pack.filter(obj => {
          return (obj.shuffleIndex >= 26 && obj.shuffleIndex <=38 && obj.lifecycle == 1)
        }
      );
      switch (w.userState.tableRotationDegrees) {
        case 0: 
          p.translate(0, g.canvasHeight / 2)
          p.rotate(0); 
          break;
        case 90: 
          p.translate(-g.canvasWidth / 2, 0);
          p.rotate(p.HALF_PI);
          break;
        case 180:
          p.translate(0, -g.canvasHeight / 2);
          p.rotate(2 * p.HALF_PI);
          break;
        case 270:
          p.translate(g.canvasWidth / 2, 0);
          p.rotate(3 * p.HALF_PI);
          break;
        default:
          console.log('Unexpected tableRotation argument ');
      }
      break;
    case 'West':
      g.isHandVisible = gameState.handVisible.west;
      g.myHandArray = window.gameState.pack.filter(obj => {
          return (obj.shuffleIndex >= 39 && obj.shuffleIndex <=51 && obj.lifecycle == 1)
        }
      ); 
      switch (w.userState.tableRotationDegrees) {
        case 0: 
          p.translate(-g.canvasWidth / 2, 0)
          p.rotate(p.HALF_PI); 
          break;
        case 90: 
          p.translate(0, -g.canvasHeight / 2);
          p.rotate(p.PI);
          break;
        case 180:
          p.translate(g.canvasWidth / 2, 0);
          p.rotate(-p.HALF_PI);
          break;
        case 270:
          p.translate(0, g.canvasHeight / 2);
          p.rotate(0);
          break;
        default:
          console.log('Unexpected tableRotation argument ');
      }
      break;
    case 'Discard':
      g.myDiscardArray = window.gameState.pack.filter(obj => {
          return (obj.lifecycle === 2 )
      });
      //console.log(g.myDiscardArray);
      // switch(true) {
      //   case g.myDiscardArray[0]:
      //     switch (w.userState.tableRotationDegrees) {
      //       case 0: 
      //         p.translate(0, 0)
      //         p.rotate(0); 
      //         break;
      //       case 90: 
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 180:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 270:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       default:
      //         console.log('Unexpected tableRotation argument ');
      //     }
      //   break;
      //   case 'East':
      //     switch (w.userState.tableRotationDegrees) {
      //       case 0: 
      //         p.translate(0, 0)
      //         p.rotate(0); 
      //         break;
      //       case 90: 
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 180:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 270:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       default:
      //         console.log('Unexpected tableRotation argument ');
      //     }
      //   break;
      //   case 'South':
      //     switch (w.userState.tableRotationDegrees) {
      //       case 0: 
      //         p.translate(0, 0)
      //         p.rotate(0); 
      //         break;
      //       case 90: 
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 180:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 270:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       default:
      //         console.log('Unexpected tableRotation argument ');
      //     }
      //   break;
      //   case 'West':
      //     switch (w.userState.tableRotationDegrees) {
      //       case 0: 
      //         p.translate(0, 0)
      //         p.rotate(0); 
      //         break;
      //       case 90: 
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 180:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       case 270:
      //         p.translate(0, 0);
      //         p.rotate(0);
      //         break;
      //       default:
      //         console.log('Unexpected tableRotation argument ');
      //     }
      //   break;
      //   default:
      //     console.log('Unexpected pointOfCompass argument');
      // }
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
  g.myDiscardArray.forEach((obj, i) => {
      // now we can draw a card using each fileName in myDiscardArray
      let p5img = g.imgMap.get(obj.fileName);
      // // position of card depends on range of shuffleIndex and rotation
      p.push();
      switch (true) {
        // N
        case (obj.shuffleIndex < 13):
          switch (w.userState.tableRotationDegrees) {
            case 0: 
              p.translate(-cardWidth / 2, -cardHeight * 0.8)
              p.rotate(0); 
              break;
            case 90: 
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(p.HALF_PI);
              break;
            case 180:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            case 270:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            default:
              console.log('Unexpected tableRotation argument ');
          }
        break;
        // E
        case (obj.shuffleIndex < 26):
          switch (w.userState.tableRotationDegrees) {
            case 0: 
              p.translate(-cardWidth * 0.2, -cardHeight / 2)
              p.rotate(0); 
              break;
            case 90: 
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            case 180:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            case 270:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            default:
              console.log('Unexpected tableRotation argument ');
          }
        break;
        // S
        case (obj.shuffleIndex < 39):
          switch (w.userState.tableRotationDegrees) {
            case 0: 
              p.translate(-cardWidth / 2, -cardHeight * 0.2)
              p.rotate(0); 
              break;
            case 90: 
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            case 180:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            case 270:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            default:
              console.log('Unexpected tableRotation argument ');
          }
        break;
        // W
        case (obj.shuffleIndex < 52):
          switch (w.userState.tableRotationDegrees) {
            case 0: 
              p.translate(-cardWidth * 0.8, -cardHeight / 2)
              p.rotate(0); 
              break;
            case 90: 
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            case 180:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            case 270:
              p.translate(-cardWidth / 2, -cardHeight / 2);
              p.rotate(0);
              break;
            default:
              console.log('Unexpected tableRotation argument ');
          }
          break;
        default:
        console.log('Unexpected shuffleIndex argument');
      }
      p.image(p5img, 0, 0, cardWidth, cardHeight);
      p.pop();
  });
};

exports.drawCards = drawCards;