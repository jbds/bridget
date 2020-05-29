// identical to ButtonStd except for the event handler which does NOT dispatch an action
// so inject the event handler
[@react.component]
let make = (~label: string, ~id: string, ~onClick) => {
  <>
    <button 
    id=id
    onClick=onClick //((_e) => Js.log("Clicked ButtonStdJsx"))
    style=(
      ReactDOMRe.Style.make(
        ~color={"#26653B"}, 
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"0vh"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #26653B"}, 
        ~borderRadius={"5px"},
        ~backgroundColor={"#FFFFFF"},
        ()
      )
    )
    >
      (React.string(label))
    </button>
  </>
};
