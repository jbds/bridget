[@react.component]
let make =
    (
      ~id: string,
      ~text: string,
      ~isWarning: bool=false,
      ~fontSize: string="1.9vh",
    ) => {
  <>
    //onClick=((_e) => Js.log("Clicked span element"))
    <span
      id
      style={ReactDOMRe.Style.make(
        ~color={isWarning ? "#C00000" : "#404040"}, // non-warning was 26653B
        ~fontSize,
        ~fontFamily=[@reason.preserve_braces] "Trebuchet MS",
        ~margin=[@reason.preserve_braces] "0vh",
        // bug - borderColor single attribute not recognised
        //~border={"1px solid #26653B"},
        //~borderRadius={"5px"},
        //~backgroundColor={"#FFFFFF"},
        ~width=[@reason.preserve_braces] "10vh",
        ~textAlign=[@reason.preserve_braces] "center",
        (),
      )}>
      {React.string(text)}
    </span>
  </>;
};
