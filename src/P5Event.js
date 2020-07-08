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
  //console.log('isValidDiscardFromLocalPlayer:');
  //console.log(isValidDiscardFromLocalPlayer());
  if (isValidDiscardFromLocalPlayer() && isCardDiscardFollowingSuitWhenPossible()) {
    // prepare a second action after a delay if 3 cards are already discarded
    // because we are about to discard the 4th
    if (gameState.pack.filter(obj => {return (obj.lifecycle === 2)}).length === 3) {
      //setTimeout(function(){alert('Yay');}, 750);
      setTimeout(function(){document.getElementById('btnEndTrick').click();}, 750);
    }
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
    return (
      (
        userPointOfCompass === cardPointOfCompass 
        && 
        gameState.isBiddingCycle === false 
        // add extra constraint here to avoid multiple discards
        &&
        gameState.activePointOfCompass === userPointOfCompass
      )
      ||
      (
        // relax constraint to allow Dummy to be selected by Declarer
        gameState.activePointOfCompass === getDummyPocByDeclarer()
        &&
        userPointOfCompass === gameState.declarer
        &&
        gameState.isBiddingCycle === false
        // but ensure declarer cannot discard from their own hand
        &&
        cardPointOfCompass !== gameState.declarer
      )
      ? 
      true 
      : 
      false
    );
  };

// helper function for relaxed constraint on dummy when declarer & user coincide
let getDummyPocByDeclarer = () => {
  switch (gameState.declarer) {
    case "North":
      return "South";
      break;
    case "East":
      return "West";
      break;
    case "South":
      return "North";
      break;
    case "West":
      return "East";
      break;
    default: 
      return "Error";
  }
};

// we also need to check if user discard is following suit 
let isCardDiscardFollowingSuitWhenPossible = () => {
  let card = gameState.pack.find(obj => obj.fileName === window.discardFileName);
  // we always allow the first discard, whatever the suit
  if ((gameState.discardIndex + 1) % 4 === 0){
    return true;
  // if card follows suit, allow
  } else if (card.suit === gameState.discardSuit) {
    return true;
  // if card does not follow suit, only allow if countOfCardsInHandWithDiscardSuit = 0
  } else if (countOfCardsInHandWithDiscardSuit(card) === 0) {
    return true;
  } else {
    // disallow
    return false;
  }
};

let countOfCardsInHandWithDiscardSuit = (card) => {
  let index = card.shuffleIndex;
  //console.log('card shuffle index:');
  //console.log(index);
  let hand;
  if (index < 13) {
    hand = window.gameState.pack.filter(obj => {
      return (obj.shuffleIndex >= 0 && obj.shuffleIndex <= 12 && obj.lifecycle === 1)
    });
  } else if (index < 26) {
    hand = window.gameState.pack.filter(obj => {
      return (obj.shuffleIndex >= 13 && obj.shuffleIndex <= 25 && obj.lifecycle === 1)
    });
  } else if (index < 39) {
    hand = window.gameState.pack.filter(obj => {
      return (obj.shuffleIndex >= 26 && obj.shuffleIndex <=38 && obj.lifecycle === 1)
    });
  } else {
    hand = window.gameState.pack.filter(obj => {
      return (obj.shuffleIndex >= 39 && obj.shuffleIndex <= 51 && obj.lifecycle === 1)
    });
  }
  let handFilteredBySuit = hand.filter(obj => {return obj.suit === gameState.discardSuit});
  //console.log('handFilteredBySuit.length');
  //console.log(handFilteredBySuit.length);
  return handFilteredBySuit.length;
}

exports.mouseDecode = mouseDecode;