%raw
{|
  const Online = require('../Online.bs');
|};

[@react.component]
let make = () => {
  //  Js.log(Chicago.getScore(~level=7, ~denomination=NoTrumps, ~tricksTotal=13,
  //    ~isVulnerable=true, ~isDoubled=true, ~isRedoubled=true));
  //let s2e = React.string;
  // 'dispatch' will not change between re-renders
  // useReducer expects to have passed in a reducer function and an initial state
  let (state, dispatch) =
    React.useReducer(Global.reducer, Global.initialState);
  // Js.log("App.re react component re-render with state as below:");
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
  let () = [%raw
    {|
    !window.isLastActionSync
    ?
    Online.doMessage(gameState)
    :
    //console.log('Action-Sync: doMessage suppressed')
    null
  |}
  ];
  // event handlers
  let handlerBtnRotateTable = _e => {
    //Js.log("btnRotateTable clicked");
    let () = [%raw
      "window.userState.tableRotationDegrees = ((window.userState.tableRotationDegrees + 90) % 360)"
    ];
    ();
  };
  let handlerBtnLogin = _e => {
    //Js.log("btnLogin clicked");
    let () = [%raw
      "userState.player = (document.getElementById('txtMyLoginName').value).toUpperCase()"
    ];
    let () = [%raw
      "localStorage.setItem(
                      'myLoginName',
                      userState.player
                    )"
    ];
    // prepare to rotate board if necessary
    let () = [%raw
      "setTimeout(function(){
        //alert('rotate?');
        // after the delay, we can be certain that the player has been added
        // but we do not know if a poc has been previously assigned and remembered
        let arrObj = gameState.pointOfCompassAndPlayers.find(el => el.player === userState.player);
        // force the player to be at 6PM
        if (arrObj.pointOfCompass === 'South') {
          window.userState.tableRotationDegrees = 0;
        } else if (arrObj.pointOfCompass === 'East') {
          window.userState.tableRotationDegrees = 90;
        } else if (arrObj.pointOfCompass === 'North') {
          window.userState.tableRotationDegrees = 180;
        } else if (arrObj.pointOfCompass === 'West') {
          window.userState.tableRotationDegrees = 270;
        } else {
          // do nothing
        }
      }, 1500)"
    ];
    let () = [%raw "Online.doLogin(userState.player)"];
    ();
  };
  let handlerBtnLogout = _e => {
    //Js.log("btnLogout clicked");
    // NO! - this causes a low level react js error re index out of bounds
    //let () = [%raw "window.userState.player = '?'"];
    let () = [%raw
      "Online.doLogout((document.getElementById('txtMyLoginName').value).toUpperCase())"
    ];
    // nothing more expected from server, so clean up locally
    // crude way would be just to reload the app from scratch
    //let () = [%raw "alert('time to reload!')"]();
    let () = [%raw "location.reload()"];
    ();
  };
  let handlerBtnUndo = _e => {
    //Js.log("btnUndo clicked");
    let () = [%raw "Online.doMessage('Undo')"];
    ();
  };
  let handlerBtnReboot2 = _e => {
    Js.log("btnReboot2 clicked");
    let bln: bool = [%raw
      "window.confirm('Are you sure you want to DELETE ALL SCORES and start afresh?')"
    ];

    let () = bln ? [%raw "Online.doMessage('Reboot')"] : ();
    ();
  };
  let handlerBtnReviewDeal = _e => {
    Js.log("btnReviewDeal clicked");
    let () = [%raw "Online.doMessage('ReviewDeal')"];
    ();
  };
  // other utility functions
  let isFourSeatsOccupied = () => {
    let myShorterArray =
      Belt.Array.keep(state.pointOfCompassAndPlayers, x => {
        x.pointOfCompass != "" && x.pointOfCompass != "Observer"
      });
    Belt.Array.length(myShorterArray) == 4 ? true : false;
  };
  //Js.log("isFourSeatsOccupied:");
  //Js.log(isFourSeatsOccupied());
  let isDealButtonVisible = () => {
    let localPlayer: string = [%bs.raw "window.userState.player"];
    let userPointOfCompassWrappedInArray =
      Belt.Array.keep(state.pointOfCompassAndPlayers, obj => {
        obj.player === localPlayer
        && obj.pointOfCompass === Shuffle.pocAsString(state.dealer)
      });
    if (Array.length(userPointOfCompassWrappedInArray) === 0) {
      false;
    } else if (isFourSeatsOccupied()
               && state.lastAction !== "4 Passes - so fresh cards dealt"
               && (
                 Array.length(state.pack) === 0 || state.discardIndex === 51
               )) {
      true;
    } else {
      false;
    };
  };
  let isUndoVisible = () => {
    let localPlayer: string = [%bs.raw "window.userState.player"];
    let userPointOfCompassWrappedInArray =
      Belt.Array.keep(state.pointOfCompassAndPlayers, obj => {
        // for debug, better to always allow undo whether player is seated or not
        //obj.player === localPlayer && obj.pointOfCompass !== ""
        obj.player === localPlayer
      });
    Array.length(userPointOfCompassWrappedInArray) === 0 ? false : true;
  };
  //Js.log("isDealButtonVisible");
  //Js.log(isDealButtonVisible());
  let isBiddingWindowVisible = () =>
    // only check when in BiddingCycle and at least 4 players (TO DO - strictly should exclude Observers)
    if (state.isBiddingCycle == true
        && Array.length(state.pointOfCompassAndPlayers) >= 4) {
      let localPlayer: string = [%bs.raw "window.userState.player"];
      //Js.log("localPlayer=" ++ localPlayer);
      let userPointOfCompassWrappedInArray =
        Belt.Array.keep(state.pointOfCompassAndPlayers, obj =>
          obj.player === localPlayer
        );
      if (Array.length(userPointOfCompassWrappedInArray) === 0) {
        false;
      } else {
        let userPointOfCompass =
          userPointOfCompassWrappedInArray[0].pointOfCompass;
        //Js.log("UserPointOfCompass=" ++ userPointOfCompass);
        state.activePointOfCompass == Some(userPointOfCompass) ? true : false;
      };
    } else {
      false;
    };
  // helpers to decide if we want to show the Concede button aka Jump to Finish
  let isQtyCardsInHandsDivFour = () => {
    let lifecycleHandCardsArray =
      Belt.Array.keep(state.pack, x => {x.lifecycle === Hand});
    Belt.Array.length(lifecycleHandCardsArray) mod 4 == 0;
  };
  let isQtyCardsInDiscardZero = () => {
    let lifecycleDiscardCardsArray =
      Belt.Array.keep(state.pack, x => {x.lifecycle === Discard});
    Belt.Array.length(lifecycleDiscardCardsArray) === 0;
  };
  let isQtyCardsInHandGT0LTE16 = () => {
    let lifecycleHandCardsArray =
      Belt.Array.keep(state.pack, x => {x.lifecycle === Hand});
    Belt.Array.length(lifecycleHandCardsArray) <= 16
    && Belt.Array.length(lifecycleHandCardsArray) > 0;
  };
  // fragment
  <>
    <div id="sidebar1">
      <br />
      <SpanStd id="spn1" text="Me: " />
      <InputStd id="txtMyLoginName" />
      <SpanStd id="spn2" text=" " />
      <ButtonStdJsx id="btnLogin" label="Join" onClick=handlerBtnLogin />
      <SpanStd id="spn3" text=" " />
      <ButtonStdJsx id="btnLogout" label="Leave" onClick=handlerBtnLogout />
      <SpanStd id="spn4" text=" " />
      //<ButtonStd dispatch action=NewGame label="Reboot" id="btnNewGame" isWasteOfSpace={!state.isRebootVisible}/>
      <ButtonStdJsx
        id="btnReboot2"
        label="Restart"
        onClick=handlerBtnReboot2
        isWasteOfSpace={!state.isRebootVisible}
      />
      <br />
      <TablePosition state dispatch />
      <br />
      //<br/>
      <ButtonStd
        dispatch
        action={Shuffle(true)}
        label="My Deal"
        id="btnShuffle"
        isWasteOfSpace={!isDealButtonVisible()}
      />
      //<SpacerStd spacerWidth="1vh" />
      <SpanStd id="spn5" text={js|\u200A|js} />
      <ButtonStdJsx
        id="btnRotateTable"
        label={js|\u27F3|js}
        onClick=handlerBtnRotateTable
        isWasteOfSpace={!isFourSeatsOccupied()}
      />
      //<SpacerStd spacerWidth="1.5vh" />
      <SpanStd id="spn6" text={js|\u200A|js} />
      <ButtonStdJsx
        id="btnUndo"
        label="Undo"
        onClick=handlerBtnUndo
        isWasteOfSpace={!isUndoVisible()}
      />
      <SpanStd id="spn7" text={js|\u200A|js} />
      <ButtonStd
        dispatch
        action=Concede
        label={js|\uD83C\uDFC1|js}
        id="btnConcede"
        isVisible={
          isQtyCardsInHandsDivFour()
          && isQtyCardsInDiscardZero()
          && isQtyCardsInHandGT0LTE16()
          && isFourSeatsOccupied()
        }
      />
      <SpanStd id="spn8" text={js|\u200A|js} />
      <ButtonStdJsx
        id="btnReviewDeal"
        label="Review"
        onClick=handlerBtnReviewDeal
        isWasteOfSpace={!isDealButtonVisible() || !state.isReviewDealVisible}
      />
      <SpanStd id="spn8" text={js|\u200A|js} />
      <ButtonStd
        dispatch
        action={Shuffle(false)}
        label="Replay"
        id="btnReplay"
        isWasteOfSpace={!isDealButtonVisible() || state.isReviewDealVisible}
      />
    </div>
    <div id="sidebar2">
      //(s2e("Sidebar2"))

        <br />
        //<button id="btn1">(s2e("p5 click listener"))</button>
        <ButtonStd
          dispatch
          action=EndOneTrick
          label="End One Trick"
          id="btnEndTrick"
          isVisible=false
        />
        <ButtonStd
          dispatch
          action=PostDiscard
          label="Post Discard"
          id="btnPostDiscard"
          isVisible=false
        />
        <ButtonStd
          dispatch
          action=Discard
          label="Discard"
          id="btnDiscard"
          isVisible=false
        />
        <ButtonStd
          dispatch
          action=Sync
          label="Sync state with gameState"
          id="btnSync"
          isVisible=false
        />
        <ButtonStd
          dispatch
          action=LoginSync
          label="Login sync with server"
          id="btnLoginSync"
          isVisible=false
        />
        <ButtonStd
          dispatch
          action=PostBid
          label="Post Bid"
          id="btnPostBid"
          isVisible=false
        />
        <ButtonStd
          dispatch
          action=Post4Passes
          label="Post 4 Passes"
          id="btnPost4Passes"
          isVisible=false
        />
        <ChicagoScoreTable state />
      </div>
    <div id="sidebar3">
      <SpanStd id="spnRandomInt" fontSize="1.5vh" text="Last action:" />
      <SpanStd id="spnRILA" fontSize="1.5vh" text=" " />
      <SpanStd
        id="spnLastAction"
        fontSize="1.5vh"
        text={state.lastAction}
        isWarning={state.lastAction == "Logout or Server Down" ? true : false}
      />
    </div>
    <div
      id="bidTable"
      style={ReactDOMRe.Style.make(
        ~padding=[@reason.preserve_braces] "1vh 0vh 0vh 0vh",
        ~borderRadius=[@reason.preserve_braces] "5px",
        (),
      )}>
      <BidTable state />
    </div>
    <div
      id="biddingWindow"
      style={ReactDOMRe.Style.make(
        ~padding=[@reason.preserve_braces] "1vh 1vh 1vh 3vh",
        ~borderRadius=[@reason.preserve_braces] "10px",
        ~display={isBiddingWindowVisible() ? "inline" : "none"},
        (),
      )}>
      <BiddingWindow dispatch state />
    </div>
  </>;
};
