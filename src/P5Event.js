'use strict';

let mouseDecode = (p, g) => {
  // x and y ranges define 4 regions of interest
  // NB 13 segments means lower bound 0 and upper bound 13
  let cardSegmentHeightToCanvasHeightRatio =
    g.cardSegmentHeightToCardRatio * g.cardHeightToCanvasHeightRatio;
  let cardSegmentIndex;
  let myHandArray;
  let cardSegmentIndexAdjusted;
  //console.log('mouse decode');
  switch (true) {
    // top (N?)
    case (p.mouseY <= cardSegmentHeightToCanvasHeightRatio * g.canvasHeight &&
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
    myHandArray = window.gameState.pack.filter(obj => {
      return (obj.shuffleIndex >= 0 && obj.shuffleIndex <= 12 && obj.lifecycle === 1)
    });
    cardSegmentIndexAdjusted = Math.floor(cardSegmentIndex - ((13 - myHandArray.length) / 2));
    if (cardSegmentIndexAdjusted < 0 || cardSegmentIndexAdjusted > (myHandArray.length - 1)) {
      // do nothing
    } else {
      //console.log('top area, indexAdjustedAndConstrained=' + cardSegmentIndexAdjusted);
      convertAdjustedIndexToCardKey(cardSegmentIndexAdjusted, myHandArray);
    }
    break;
    // right (E?)
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
      myHandArray = window.gameState.pack.filter(obj => {
        return (obj.shuffleIndex >= 13 && obj.shuffleIndex <= 25 && obj.lifecycle === 1)
      });
      cardSegmentIndexAdjusted = Math.floor(cardSegmentIndex - ((13 - myHandArray.length) / 2));
      if (cardSegmentIndexAdjusted < 0 || cardSegmentIndexAdjusted > (myHandArray.length - 1)) {
        // do nothing
      } else {
        //console.log('right area, indexAdjustedAndConstrained=' + cardSegmentIndexAdjusted);
        convertAdjustedIndexToCardKey(cardSegmentIndexAdjusted, myHandArray);
      }
      break;
    // bottom (S?)
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
      myHandArray = window.gameState.pack.filter(obj => {
        return (obj.shuffleIndex >= 26 && obj.shuffleIndex <=38 && obj.lifecycle === 1)
      });
      cardSegmentIndexAdjusted = Math.floor(cardSegmentIndex - ((13 - myHandArray.length) / 2));
      if (cardSegmentIndexAdjusted < 0 || cardSegmentIndexAdjusted > (myHandArray.length - 1)) {
        // do nothing
      } else {
        //console.log('bottom area, indexAdjustedAndConstrained=' + cardSegmentIndexAdjusted);
        convertAdjustedIndexToCardKey(cardSegmentIndexAdjusted, myHandArray);
      }
    break;
    // left (W?)
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
      myHandArray = window.gameState.pack.filter(obj => {
        return (obj.shuffleIndex >= 39 && obj.shuffleIndex <= 51 && obj.lifecycle === 1)
      });
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
  //console.log(myCard.fileName);
  // at this point we know which card was clicked
  // so we can update the (mutable) js gameState object
  let pack = gameState.pack;
  pack.find((value, index) => {
    if (value.fileName === myCard.fileName) {
      // lifecycle Discard = 2 in js
      gameState.pack[index].lifecycle = 2;
    }
  });
  //console.log(gameState.pack.filter(x => x.fileName === myCard.fileName));
  // and then dispatch the Sync action via a hidden key on the sidebar
  document.getElementById('btnSync').click();
}

exports.mouseDecode = mouseDecode;