[@react.component]
let make =
    (
      ~dispatch: Global.action => unit,
      ~action: Global.action,
      ~label: string,
      ~id: string,
      ~isActive: bool=true,
      ~isVisible: bool=true,
      ~isWasteOfSpace: bool=false,
      ~color: string="#26653B",
    ) => {
  <>
    <button
      id
      onClick={_e => dispatch(action)} //Js.log("Clicked shuffle"))
      style={ReactDOMRe.Style.make(
        ~{color},
        ~fontSize=[@reason.preserve_braces] "1.9vh",
        ~fontFamily=[@reason.preserve_braces] "Trebuchet MS",
        ~height=[@reason.preserve_braces] "5.0vh",
        ~margin=[@reason.preserve_braces] "0vh 0.5vh 0vh 0vh",
        // bug - borderColor single attribute not recognised
        ~border=[@reason.preserve_braces] "1px solid #26653B",
        ~borderRadius=[@reason.preserve_braces] "5px",
        // inactive background color was 60806040 but too greeney
        // try e0e0e0
        ~backgroundColor={isActive ? "#ffffff" : "#e0e0e0"},
        ~display={isVisible ? "inline" : "none"},
        ~visibility={isWasteOfSpace ? "hidden" : "visible"},
        (),
      )}>
      {React.string(label)}
    </button>
  </>;
};
