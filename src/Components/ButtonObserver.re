[@react.component]
let make = (~dispatch: Global.action => unit, ~action: Global.action, ~label: string, ~id: string) => {
  <>
    <button 
    id=id
    className={"btnObserver"}
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
        //~backgroundColor={"#FFFFFF"},
        ~backgroundImage={"url(assets/EyeForObserver000.png)"},
        ~width={"50px"},
        ~height={"50px"},
        ()
      )
    )
    >
      (React.string(label))
    </button>
  </>
};
