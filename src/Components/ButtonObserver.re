[@react.component]
let make =
    (
      ~dispatch: Global.action => unit,
      ~action: Global.action,
      ~label: string,
      ~id: string,
      ~isActive: bool,
    ) => {
  <>
    <button
      id
      onClick={_e => dispatch(action)} //Js.log("Clicked shuffle"))
      style={ReactDOMRe.Style.make(
        // hide the dummy underscore text
        ~color={isActive ? "#ffffff" : "#e0e0e0"},
        ~fontSize=[@reason.preserve_braces] "1.9vh",
        ~fontFamily=[@reason.preserve_braces] "Trebuchet MS",
        ~height=[@reason.preserve_braces] "5.0vh",
        ~margin=[@reason.preserve_braces] "0vh",
        // bug - borderColor single attribute not recognised
        ~border=[@reason.preserve_braces] "1px solid #26653B",
        ~borderRadius=[@reason.preserve_braces] "5px",
        // green "#60806040" changed to #e0e0e0
        ~backgroundColor={isActive ? "#ffffff" : "#e0e0e0"},
        ~backgroundImage=
          [@reason.preserve_braces] "url(assets/EyeSpikeyTransparent.png)",
        ~backgroundRepeat=[@reason.preserve_braces] "no-repeat",
        ~backgroundSize=[@reason.preserve_braces] "100% 100%",
        (),
      )}>
      {React.string(label)}
    </button>
  </>;
};
