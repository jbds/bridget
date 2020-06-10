[@react.component]
let make = (~dispatch: Global.action => unit, ~action: Global.action, ~label: string, ~id: string, ~isActive: bool) => {
  <>
    <button 
    id=id
    onClick=((_e) => dispatch(action))//Js.log("Clicked shuffle"))//
    style=(
      ReactDOMRe.Style.make(
        // hide the dummy underscore text
        ~color={isActive ? "#ffffff" : "#e0e0e0"}, 
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"0vh"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #26653B"}, 
        ~borderRadius={"5px"},
        ~backgroundColor={isActive ? "#ffffff" : "#ffe0e0"},
        ~backgroundImage={"url(assets/EyeSpikeyTransparent.png)"},
        ~backgroundSize={"100% 100%"},
        ()
      )
    )
    >
      (React.string(label))
    </button>
  </>
};