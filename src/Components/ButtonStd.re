[@react.component]
let make = (~dispatch: Global.action => unit, ~action: Global.action, ~label: string, ~id: string) => {
  <>
    <button 
    id=id
    onClick=((_e) => dispatch(action))//Js.log("Clicked shuffle"))//
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
