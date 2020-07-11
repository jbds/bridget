[@react.component]
let make = (
  ~dispatch: Global.action => unit, 
  ~state: Global.state
  ) => {
  // need helper to decide visibility of X and XX buttons
  let bidListHead = Belt.List.head(state.bids);
  let isShowXAndXX =
    switch (bidListHead) {
      | None => false
      | Some(x) => x.contractSuit !== Some("") ? true : false
    }
  ;
  Js.log("isShowXAndXX");
  Js.log(isShowXAndXX);

  <>
    //<span>(React.string("BiddingWindowComp"))</span>
    //(s2e("TEST"))
    // unicode for Spades, Hearts, Diamonds and Clubs and hair space glyphs */
    // Js.log({js|\u2660 A|js});
    // Js.log({js|\u2665 K|js});
    // Js.log({js|\u2666 3|js});
    // Js.log({js|\u2663 2|js});
    // Js.log({js|\u200A|js})
    <ButtonBidSmall isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAdd(Some(1)) label="1" id="btnBid1" color="#606060"/>
    <ButtonBidSmall isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAdd(Some(2)) label="2" id="btnBid2" color="#606060"/>
    <ButtonBidSmall isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAdd(Some(3)) label="3" id="btnBid3" color="#606060"/>
    <ButtonBidSmall isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAdd(Some(4)) label="4" id="btnBid4" color="#606060"/>
    <ButtonBidSmall isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAdd(Some(5)) label="5" id="btnBid5" color="#606060"/>
    <ButtonBidSmall isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAdd(Some(6)) label="6" id="btnBid6" color="#606060"/>
    <ButtonBidSmall isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAdd(Some(7)) label="7" id="btnBid7" color="#606060"/>
    <ButtonBidLarge isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAddSpecial(Some("Pass")) label="Pass" id="btnBidPass" backgroundColor="#26653B"/>
    <br/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons} dispatch action=BidUpdate(Some("Clubs")) label={js|\u2663|js} id="btnBidC" color="black"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons} dispatch action=BidUpdate(Some("Diamonds")) label={js|\u2666|js} id="btnBidD" color="red"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons} dispatch action=BidUpdate(Some("Hearts")) label={js|\u2665|js} id="btnBidH" color="red"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons} dispatch action=BidUpdate(Some("Spades")) label={js|\u2660|js} id="btnBidS" color="black"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons} dispatch action=BidUpdate(Some("NoTrumps")) label="NT" id="btnBidNT" color="#606060"/>
    <SpacerStd spacerWidth="4vh" />
    <ButtonBidLarge isVisible=isShowXAndXX dispatch action=BidAddSpecial(Some("X")) label="X" id="btnBidX" backgroundColor="#E00000"/>
    <ButtonBidLarge isVisible=isShowXAndXX dispatch action=BidAddSpecial(Some("XX")) label="XX" id="btnBidXX" backgroundColor="#000080"/>
  </>
};
