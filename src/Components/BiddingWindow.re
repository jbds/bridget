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
  //Js.log("isShowXAndXX");
  //Js.log(isShowXAndXX);
  // helper to decide highest bid level
  let bidsListFilteredByContractLevel = Belt.List.keep(state.bids, x => {x.contractLevel !== None});
  let optionCurrentContractLevelBid = Belt.List.head(bidsListFilteredByContractLevel);
  let optionCurrentContractLevel =
    switch (optionCurrentContractLevelBid) {
      | None => None
      | Some(x) => x.contractLevel
    };
  let currentContractLevel =
    switch (optionCurrentContractLevel) {
      | None => 0
      | Some(n) => n
    };
  Js.log("currentContractLevel:");
  Js.log(currentContractLevel);
  // we need currentContractSuit too
  let optionCurrentContractSuit =
    switch (optionCurrentContractLevelBid) {
      | None => None
      | Some(x) => x.contractSuit
    };
  let currentContractSuitAsString = 
    switch (optionCurrentContractSuit) {
      | None => ""
      | Some(x) => x
    };
  let currentContractSuitAsRank =
    switch(currentContractSuitAsString) {
      | "Clubs" => 0
      | "Diamonds" => 1
      | "Hearts" => 2
      | "Spades" => 3
      | "NoTrumps" => 4
      | _ => -1
    };
  Js.log("currentContractSuitAsRank:");
  Js.log(currentContractSuitAsRank);
  // helper to decide highest denomination - we have to look at a previous bid record
  let optionBidListTail = Belt.List.tail(bidsListFilteredByContractLevel);
  let bidListTail =
    switch (optionBidListTail) {
      | None => []
      | Some(x) => x
    };
  let optionPreviousBid = Belt.List.head(bidListTail);
  let optionPreviousContractSuit =
    switch (optionPreviousBid) {
      | None => None
      | Some(x) => x.contractSuit
    };
  let previousContractSuitAsString =
    switch (optionPreviousContractSuit) {
      | None => ""
      | Some(x) => x
    };
  //Js.log("previousContractSuitAsString:");
  //Js.log(previousContractSuitAsString);
  let previousContractSuitAsRank =
    switch(previousContractSuitAsString) {
      | "Clubs" => 0
      | "Diamonds" => 1
      | "Hearts" => 2
      | "Spades" => 3
      | "NoTrumps" => 4
      | _ => -1
    };
  Js.log("previousContractSuitAsRank:");
  Js.log(previousContractSuitAsRank);

  <>
    //<span>(React.string("BiddingWindowComp"))</span>
    //(s2e("TEST"))
    // unicode for Spades, Hearts, Diamonds and Clubs and hair space glyphs */
    // Js.log({js|\u2660 A|js});
    // Js.log({js|\u2665 K|js});
    // Js.log({js|\u2666 3|js});
    // Js.log({js|\u2663 2|js});
    // Js.log({js|\u200A|js})
    <ButtonBidSmall isVisible={
      state.isBiddingHideDenominationButtons 
      && 
      (
        (currentContractLevel <= 1 && currentContractSuitAsRank !== 4)
        ||
        (currentContractLevel < 1 && currentContractSuitAsRank === 4)
      )
    } dispatch action=BidAdd(Some(1)) label="1" id="btnBid1" color="#606060"/>
    <ButtonBidSmall isVisible={
      state.isBiddingHideDenominationButtons 
      && 
      (
        (currentContractLevel <= 2 && currentContractSuitAsRank !== 4)
        ||
        (currentContractLevel < 2 && currentContractSuitAsRank === 4)
      )
    } dispatch action=BidAdd(Some(2)) label="2" id="btnBid2" color="#606060"/>
    <ButtonBidSmall isVisible={
      state.isBiddingHideDenominationButtons 
      && 
      (
        (currentContractLevel <= 3 && currentContractSuitAsRank !== 4)
        ||
        (currentContractLevel < 3 && currentContractSuitAsRank === 4)
      )
    } dispatch action=BidAdd(Some(3)) label="3" id="btnBid3" color="#606060"/>
    <ButtonBidSmall isVisible={
      state.isBiddingHideDenominationButtons 
      && 
      (
        (currentContractLevel <= 4 && currentContractSuitAsRank !== 4)
        ||
        (currentContractLevel < 4 && currentContractSuitAsRank === 4)
      )
    } dispatch action=BidAdd(Some(4)) label="4" id="btnBid4" color="#606060"/>
    <ButtonBidSmall isVisible={
      state.isBiddingHideDenominationButtons 
      && 
      (
        (currentContractLevel <= 5 && currentContractSuitAsRank !== 4)
        ||
        (currentContractLevel < 5 && currentContractSuitAsRank === 4)
      )
    } dispatch action=BidAdd(Some(5)) label="5" id="btnBid5" color="#606060"/>
    <ButtonBidSmall isVisible={
      state.isBiddingHideDenominationButtons 
      && 
      (
        (currentContractLevel <= 6 && currentContractSuitAsRank !== 4)
        ||
        (currentContractLevel < 6 && currentContractSuitAsRank === 4)
      )
    } dispatch action=BidAdd(Some(6)) label="6" id="btnBid6" color="#606060"/>
    <ButtonBidSmall isVisible={
      state.isBiddingHideDenominationButtons 
      && 
      (
        (currentContractLevel <= 7 && currentContractSuitAsRank !== 4)
        ||
        (currentContractLevel < 7 && currentContractSuitAsRank === 4)
      )
    } dispatch action=BidAdd(Some(7)) label="7" id="btnBid7" color="#606060"/>
    <ButtonBidLarge isVisible={state.isBiddingHideDenominationButtons} dispatch action=BidAddSpecial(Some("Pass")) label="Pass" id="btnBidPass" backgroundColor="#26653B"/>
    <br/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 0 || previousContractSuitAsRank === 4)} dispatch action=BidUpdate(Some("Clubs")) label={js|\u2663|js} id="btnBidC" color="black"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 1 || previousContractSuitAsRank === 4)} dispatch action=BidUpdate(Some("Diamonds")) label={js|\u2666|js} id="btnBidD" color="red"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 2 || previousContractSuitAsRank === 4)} dispatch action=BidUpdate(Some("Hearts")) label={js|\u2665|js} id="btnBidH" color="red"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 3 || previousContractSuitAsRank === 4)} dispatch action=BidUpdate(Some("Spades")) label={js|\u2660|js} id="btnBidS" color="black"/>
    <ButtonBidSmall isVisible={!state.isBiddingHideDenominationButtons && (previousContractSuitAsRank < 4 || previousContractSuitAsRank === 4)} dispatch action=BidUpdate(Some("NoTrumps")) label="NT" id="btnBidNT" color="#606060"/>
    <SpacerStd spacerWidth="4vh" />
    <ButtonBidLarge isVisible=isShowXAndXX dispatch action=BidAddSpecial(Some("X")) label="X" id="btnBidX" backgroundColor="#E00000"/>
    <ButtonBidLarge isVisible=isShowXAndXX dispatch action=BidAddSpecial(Some("XX")) label="XX" id="btnBidXX" backgroundColor="#000080"/>
  </>
};
