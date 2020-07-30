let execute = (state: TopLevel.state) => {
      // aka "New Deal" aka "My Deal"
      //Js.log("Action-Shuffle");
      // make sure doMessage is called in sidebar component
      let () = [%raw "window.isLastActionSync = false"];
      // prepare another message alerting server to store the pack as dealt
      //let () = [%raw "setTimeout(function(){alert('StoreDeal');}, 750)"];
      let () = [%raw "setTimeout(function(){Online.doMessage('StoreDeal');}, 750)"];
      // dealer becomes activePointOfCompass too, because he starts the bidding
      // do change of dealer at end of deal ie 52 cards out 
      // also set BiddingCycle to true here
      // not sure dealIndex is needed?
      // force activePointOfCompass to be dealer
      // hide Dummy hand
      // set handVisible all to false in case previous deal has been Reviewed
      {
        ...state, 
        activePointOfCompass: state.dealer,
        bids: [],
        //dealer: poc,
        //dealIndex: state.dealIndex + 1,
        declarer: None,
        discardIndex: -1,
        handVisible: Shuffle.initialHandVisible,
        isBiddingCycle: true,
        isBiddingHideDenominationButtons: true,
        isDummyVisible: false,
        isReviewDealVisible: false,
        lastAction: "Deal",
        pack: Shuffle.getShuffledPack(), 
        randomInt: Shuffle.impureGetTimeBasedSeedUpTo60k(),
      }
};