[%%raw {|
  const Online = require('../Online.bs');
|}];


[@react.component]
let make = () => {
  //  Js.log(Chicago.getScore(~level=7, ~denomination=NoTrumps, ~tricksTotal=13, 
  //    ~isVulnerable=true, ~isDoubled=true, ~isRedoubled=true));
  //let s2e = React.string;
  // 'dispatch' will not change between re-renders
  // useReducer expects to have passed in a reducer function and an initial state
  let (state, dispatch) = React.useReducer(Global.reducer, Global.initialState);
   Js.log("State as below:");
   Js.log(state);
  // if we ensure ALL changes to state go via actions, 
  // we can guarantee gameState below (for use by p5) will always be in sync
  // compiler warning 21 here unless we return unit specifically
  //let () = [%raw "!window.isLastActionSync ? window.gameState = match[0] : false"];
  // we ALWAYS want gameState to sync up to state
  let () = [%raw "window.gameState = match[0]"];
  // Js.log("gameState as below");
  // Js.log([%raw "window.gameState"]);
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
    console.log('Action-Sync: doMessage suppressed')
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
  // other utility functions
  let isFourSeatsOccupied = () => {
    let myShorterArray = Belt.Array.keep(state.pointOfCompassAndPlayers, x => {x.pointOfCompass != "" && x.pointOfCompass != "Observer"});
    Belt.Array.length(myShorterArray) == 4 ? true : false;
  };
  //Js.log("isFourSeatsOccupied:");
  //Js.log(isFourSeatsOccupied());
  let isDealButtonVisible = () => {
    let localPlayer: string = [%bs.raw "window.userState.player"];
    let userPointOfCompassWrappedInArray = Belt.Array.keep(state.pointOfCompassAndPlayers, obj => {
      obj.player === localPlayer && obj.pointOfCompass === Shuffle.pocAsString(state.dealer)
    });
    if (Array.length(userPointOfCompassWrappedInArray) === 0) {
      false;
    } else if (isFourSeatsOccupied()){
      true;
    } else {
      false;
    }
  };
  //Js.log("isDealButtonVisible");
  //Js.log(isDealButtonVisible());
  let isBiddingWindowVisible = () => {
    // only check when in BiddingCycle and at least 4 players (TO DO - strictly should exclude Observers)
    if  (
          (state.isBiddingCycle == true) && 
          (Array.length(state.pointOfCompassAndPlayers) >= 4)
        ) {
      let localPlayer: string = [%bs.raw "window.userState.player"];
      //Js.log("localPlayer=" ++ localPlayer);
      let userPointOfCompassWrappedInArray = Belt.Array.keep(state.pointOfCompassAndPlayers, obj => obj.player === localPlayer);
      if (Array.length(userPointOfCompassWrappedInArray) === 0) {
        false;
      } else {
        let userPointOfCompass = userPointOfCompassWrappedInArray[0].pointOfCompass;
        //Js.log("UserPointOfCompass=" ++ userPointOfCompass);
        state.activePointOfCompass == Some(userPointOfCompass) ? true : false;
      }
    } else {
      false;
    };
  };
  // fragment
  <>
  <div id="sidebar1">
    <br/>
    <SpanStd id="spn1" text="Me: " />
    <InputStd id="txtMyLoginName" />
    <SpanStd id="spn2" text=" " />
    <ButtonStdJsx id="btnLogin" label="Login" onClick=handlerBtnLogin/>
    <SpanStd id="spn2" text=" " />
    <ButtonStdJsx id="btnLogout" label="Logout" onClick=handlerBtnLogout/>
    <SpanStd id="spn2" text=" " />
    <ButtonStd dispatch action=NewGame label="Reboot" id="btnNewGame" isWasteOfSpace={!state.isRebootVisible}/>
    <br/>
    <TablePosition state dispatch />
    <br/>
    //<br/>
    <SpacerStd spacerWidth="1vh" />
    <ButtonStd dispatch action=Shuffle label="My Deal" id="btnShuffle" isWasteOfSpace={!isDealButtonVisible()}/>
    <SpacerStd spacerWidth="1vh" />
    <ButtonStdJsx id="btnRotateTable" label="Rotate my table" onClick=handlerBtnRotateTable isWasteOfSpace={!isFourSeatsOccupied()}/>
  </div>
  <div id="sidebar2">
    //(s2e("Sidebar2"))
    <br/>
    //<button id="btn1">(s2e("p5 click listener"))</button>
    <ButtonStd dispatch action=Discard label="Discard" id="btnDiscard" isVisible=false/>
    <ButtonStd dispatch action=Sync label="Sync state with gameState" id="btnSync" isVisible=false/>
    <ButtonStd dispatch action=LoginSync label="Login sync with server" id="btnLoginSync" isVisible=false/>
    <ChicagoScoreTable />
  </div>
  <div id="sidebar3">
    // (s2e("Sidebar3"))
    // <br/>
    // <span id="span1"></span>
    // <FlipHand dispatch/>
    <br/>
    <SpanStd id="spnRandomInt" text="Last action:" />
    <SpanStd id="spnRILA" text=" " />
    <SpanStd id="spnLastAction" text={state.lastAction} isWarning={state.lastAction == "Logout or Server Down" ? true : false}/>
  </div>
  <div 
    id="bidTable"
    style={ReactDOMRe.Style.make(
      ~padding={"1vh 0vh 0vh 0vh"},
      ~borderRadius={"5px"},
      ()
    )}> 
    <BidTable state />
  </div>
  <div 
    id="biddingWindow" 
    style={ReactDOMRe.Style.make(
      ~padding={"1vh 1vh 1vh 3vh"},
      ~borderRadius={"10px"},
      ~display={isBiddingWindowVisible() ? "inline" : "none"},
      ()
    )}> 
    <BiddingWindow dispatch state/>
  </div>
  </>
};