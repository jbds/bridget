[@react.component]
let make = (~id: string) => {
  <>
    <input
      id
      //onClick=((_e) => Js.log("Clicked input element"))
      //onChange=((_e) => Js.log("Changed input element"))
      style={ReactDOMRe.Style.make(
        ~color=[@reason.preserve_braces] "#404040",
        ~fontSize=[@reason.preserve_braces] "1.9vh",
        ~height=[@reason.preserve_braces] "4.0vh",
        ~fontFamily=[@reason.preserve_braces] "Trebuchet MS",
        ~margin=[@reason.preserve_braces] "0vh",
        // bug - borderColor single attribute not recognised
        ~border=[@reason.preserve_braces] "1px solid #26653B",
        ~borderRadius=[@reason.preserve_braces] "5px",
        ~backgroundColor=[@reason.preserve_braces] "#FFFFFF",
        ~width=[@reason.preserve_braces] "8vh",
        ~textAlign=[@reason.preserve_braces] "center",
        (),
      )}
    />
  </>;
};
