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
  let () = [%raw "!window.isLastActionSync ? Online.doMessage() : console.log('Action-Sync: doMessage suppressed')"];
  // force Sidebar to rerender on a discard
  Js.log(state.randomInt);
  // event handlers
  let handlerBtnRotateTable = (_e) => {
    //Js.log("btnRotateTable clicked");
    let () = [%raw "window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)"];
  };
  let handlerBtnLogin = (_e) => {
    //Js.log("btnLogin clicked");
    let () = [%raw "localStorage.setItem(
                      'myLoginName',
                      document.getElementById('txtMyLoginName').value
                    )"
             ];
    let () = [%raw "window.userState.player = document.getElementById('txtMyLoginName').value"];
    let () = [%raw "Online.doLogin(document.getElementById('txtMyLoginName').value)"];
  };
  let handlerBtnLogout = (_e) => {
    Js.log("btnLogout clicked");
    let () = [%raw "window.userState.player = '?'"];
    let () = [%raw "Online.doLogout(document.getElementById('txtMyLoginName').value)"];
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
    <ButtonStd dispatch action=Discard label="Discard" id="btnDiscard" isVisible=true/>
    <ButtonStd dispatch action=Sync label="Sync state with gameState" id="btnSync" isVisible=false/>
    <br/>
    <ButtonStd dispatch action=Shuffle label="Shuffle" id="btnShuffle"/>
    <div id="spnGS">
      (s2e(string_of_int(state.randomInt)))
    </div>
  </div>
  <div id="sidebar3">
    // (s2e("Sidebar3"))
    // <br/>
    // <span id="span1"></span>
    // <FlipHand dispatch/>
    <br/>
    <br/>
    <br/>
    <br/>
    <ButtonStdJsx id="btnRotateTable" label="Rotate table" onClick=handlerBtnRotateTable/>
    <br/>
  </div>
  <div id="biddingWindow"> 
    (s2e("TEST"))
  </div>
  </>
};