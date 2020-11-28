// identical to ButtonStd except for the event handler which does NOT dispatch an action
// so inject the event handler
[@react.component]
let make =
    (
      ~label: string,
      ~id: string,
      ~onClick,
      ~isVisible: bool=true,
      ~isWasteOfSpace: bool=false,
    ) => {
  <>
    //((_e) => Js.log("Clicked ButtonStdJsx"))
    <button
      id
      onClick
      style={ReactDOMRe.Style.make(
        ~color=[@reason.preserve_braces] "#26653B",
        ~fontSize=[@reason.preserve_braces] "1.9vh",
        ~height=[@reason.preserve_braces] "5.0vh",
        ~fontFamily=[@reason.preserve_braces] "Trebuchet MS",
        ~margin=[@reason.preserve_braces] "0vh 0.5vh 0vh 0vh",
        // bug - borderColor single attribute not recognised
        //~border={"1px solid #26653B"},
        ~borderRadius=[@reason.preserve_braces] "5px",
        ~backgroundColor=[@reason.preserve_braces] "#FFFFFF",
        ~display={isVisible ? "inline" : "none"},
        ~visibility={isWasteOfSpace ? "hidden" : "visible"},
        (),
      )}>
      {React.string(label)}
    </button>
  </>;
};
