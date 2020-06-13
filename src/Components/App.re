[%%raw {|
  const Online = require('../Online.bs');
|}];


[@react.component]
let make = () => {
  let s2e = React.string;
  // 'dispatch' will not change between re-renders
  // useReducer expects to have passed in a reducer function and an initial state
  let (state, dispatch) = React.useReducer(Global.reducer, Global.initialState);
  //Js.log(state);
  // if we ensure ALL changes to state go via actions, 
  // we can guarantee gameState below (for use by p5) will always be in sync
  // compiler warning 21 here unless we return unit specifically
  let () = [%raw "!window.isLastActionSync ? window.gameState = match[0] : false"];
  // any change to gameState must be messaged to the server too
  // so that it can be re-broadcst to all
  // potential for race condition here?
  // but not as long as the new gameState does NOT trigger a state change
  // aha, but if HAS to change the state on all except the initiator
  // we can get round this by re-broadcasting to all EXCEPT the initiator
  // ALSO we do not want to send a message when the initiating action is Sync
  let () = [%raw {|
    !window.isLastActionSync 
    ? 
    Online.doMessage() 
    : 
    //console.log('Action-Sync: doMessage suppressed')
    false
  |}];
  // event handlers
  let handlerBtnRotateTable = (_e) => {
    //Js.log("btnRotateTable clicked");
    let () = [%raw "window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)"];
  };
  let handlerBtnLogin = (_e) => {
    //Js.log("btnLogin clicked");
    let () = [%raw "userState.player = (document.getElementById('txtMyLoginName').value).toUpperCase()"];
    let () = [%raw "localStorage.setItem(
                      'myLoginName',
                      userState.player
                    )"
             ];
    let () = [%raw "Online.doLogin(userState.player)"];
  };
  let handlerBtnLogout = (_e) => {
    //Js.log("btnLogout clicked");
    let () = [%raw "window.userState.player = '?'"];
    let () = [%raw "Online.doLogout((document.getElementById('txtMyLoginName').value).toUpperCase())"];
  };
  // fragment
  <>
  <div id="sidebar1">
    <br/>
    <SpanStd id="spn1" text="Player: " />
    <InputStd id="txtMyLoginName" />
    <SpanStd id="spn2" text=" " />
    <ButtonStdJsx id="btnLogin" label="Login" onClick=handlerBtnLogin/>
    <SpanStd id="spn2" text=" " />
    <ButtonStdJsx id="btnLogout" label="Logout" onClick=handlerBtnLogout/>
    <br/>
    //<SpanStd id="spnOnline" text="Online:" />
    <br/>
    <TablePosition state dispatch />
  </div>
  <div id="sidebar2">
    //(s2e("Sidebar2"))
    <br/>
    //<button id="btn1">(s2e("p5 click listener"))</button>
    <ButtonStd dispatch action=Discard label="Discard" id="btnDiscard" isVisible=false/>
    <ButtonStd dispatch action=Sync label="Sync state with gameState" id="btnSync" isVisible=false/>
    <br/>
    <ButtonStd dispatch action=Shuffle label="Start Game" id="btnShuffle"/>
  </div>
  <div id="sidebar3">
    // (s2e("Sidebar3"))
    // <br/>
    // <span id="span1"></span>
    // <FlipHand dispatch/>
    <br/>
    <ButtonStdJsx id="btnRotateTable" label="Rotate table" onClick=handlerBtnRotateTable/>
    <br/>
    <div id="spnGS">
      // useful way of checking that re-render is occuring when expected
      (s2e(string_of_int(state.randomInt)))
    </div>
  </div>
  <div 
    id="bidTable"
    style={ReactDOMRe.Style.make(
      ~padding={"1vh 0vh 0vh 0vh"},
      ~borderRadius={"5px"},
      ()
    )}> 
    <BidTable />
  </div>
  <div 
    id="biddingWindow" 
    style={ReactDOMRe.Style.make(
      ~padding={"1vh 1vh 1vh 3vh"},
      ~borderRadius={"10px"},
      ()
    )}> 
    //(s2e("TEST"))
    // unicode for Spades, Hearts, Diamonds and Clubs and hair space glyphs */
    // Js.log({js|\u2660 A|js});
    // Js.log({js|\u2665 K|js});
    // Js.log({js|\u2666 3|js});
    // Js.log({js|\u2663 2|js});
    // Js.log({js|\u200A|js})
    <ButtonBidLarge dispatch action=Test label="Pass" id="btnBidPass" backgroundColor="#26653B"/>
    <ButtonBidSmall dispatch action=Test label="1" id="btnBid1" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="2" id="btnBid2" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="3" id="btnBid3" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="4" id="btnBid4" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="5" id="btnBid5" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="6" id="btnBid6" color="#606060"/>
    <ButtonBidSmall dispatch action=Test label="7" id="btnBid7" color="#606060"/>
    <br/>
    <ButtonBidLarge dispatch action=Test label="X" id="btnBidX" backgroundColor="#E00000"/>
    <ButtonBidLarge dispatch action=Test label="XX" id="btnBidXX" backgroundColor="#000080"/>
    <ButtonBidSmall dispatch action=Test label={js|\u2663|js} id="btnBidC" color="black"/>
    <ButtonBidSmall dispatch action=Test label={js|\u2666|js} id="btnBidD" color="red"/>
    <ButtonBidSmall dispatch action=Test label={js|\u2665|js} id="btnBidH" color="red"/>
    <ButtonBidSmall dispatch action=Test label={js|\u2660|js} id="btnBidS" color="black"/>
    <ButtonBidSmall dispatch action=Test label="NT" id="btnBidNT" color="#606060"/>
  </div>
  </>
};