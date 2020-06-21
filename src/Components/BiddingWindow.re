[@react.component]
let make = (
  ~dispatch: Global.action => unit, 
  ) => {
  <>
    //<span>(React.string("BiddingWindowComp"))</span>
    //(s2e("TEST"))
    // unicode for Spades, Hearts, Diamonds and Clubs and hair space glyphs */
    // Js.log({js|\u2660 A|js});
    // Js.log({js|\u2665 K|js});
    // Js.log({js|\u2666 3|js});
    // Js.log({js|\u2663 2|js});
    // Js.log({js|\u200A|js})
    <ButtonBidSmall dispatch action=Test label="1" id="btnBid1" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="2" id="btnBid2" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="3" id="btnBid3" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="4" id="btnBid4" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="5" id="btnBid5" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="6" id="btnBid6" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="7" id="btnBid7" color="#606060"/>
    <ButtonBidLarge dispatch action=Test label="Pass" id="btnBidPass" backgroundColor="#26653B"/>
    <br/>
    <ButtonBidSmall dispatch action=Test label={js|\u2663|js} id="btnBidC" color="black"/>
    <ButtonBidSmall dispatch action=Test label={js|\u2666|js} id="btnBidD" color="red"/>
    <ButtonBidSmall dispatch action=Test label={js|\u2665|js} id="btnBidH" color="red"/>
    <ButtonBidSmall dispatch action=Test label={js|\u2660|js} id="btnBidS" color="black"/>
    <ButtonBidSmall dispatch action=Test label="NT" id="btnBidNT" color="#606060"/>
    <SpacerStd spacerWidth="4vh" />
    <ButtonBidLarge dispatch action=Test label="X" id="btnBidX" backgroundColor="#E00000"/>
    <ButtonBidLarge dispatch action=Test label="XX" id="btnBidXX" backgroundColor="#000080"/>
  </>
};
