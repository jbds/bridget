
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
  let () = [%raw "window.gameState = match[0]"];
  // event handler
  let handlerBtnRotateTable = (_e) => {
    Js.log("btnRotateTable clicked");
    let () = [%raw "window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)"];
  };
  // fragment
  <>
  <div id="sidebar1">
    (s2e("Sidebar1"))
    <br/>
    <button id="btn1">(s2e("Test P5"))</button>
    <br/>
    <ButtonStd dispatch action=Shuffle label="Shuffle" id="btnShuffle"/>
  </div>
  <div id="sidebar2">
    (s2e("Sidebar2"))
    <br/>
    <button id="btn2">(s2e("Test ReasonML"))</button>
    <ButtonStd dispatch action=Discard label="Discard" id="btnDiscard"/>
    <ButtonStd dispatch action=Sync label="Sync state with gameState" id="btnSync" />
  </div>
  <div id="sidebar3">
    (s2e("Sidebar3"))
    <br/>
    <span id="span1"></span>
    <FlipHand dispatch/>
    <br/>
    <ButtonStdJsx id="btnRotateTable" label="Rotate table" onClick=handlerBtnRotateTable/>
  </div>
  </>
};