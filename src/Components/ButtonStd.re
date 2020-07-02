[@react.component]
let make = (
  ~dispatch: Global.action => unit, 
  ~action: Global.action, 
  ~label: string, 
  ~id: string, 
  ~isActive: bool=true,
  ~isVisible: bool=true,
  ~isWasteOfSpace: bool=false,
  ) => {
  <>
    <button 
    id=id
    onClick=((_e) => dispatch(action))//Js.log("Clicked shuffle"))//
    style=(
      ReactDOMRe.Style.make(
        ~color={"#26653B"}, 
        ~fontSize={"2.0vh"},
        ~fontFamily={"Trebuchet MS"},
        ~height={"5.0vh"},
        ~margin={"0vh 0.5vh 0vh 0vh"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #26653B"}, 
        ~borderRadius={"5px"},
        ~backgroundColor={isActive ? "#ffffff" : "#60806040"},
        ~display={isVisible ? "inline" : "none"},
        ~visibility={isWasteOfSpace ? "hidden" : "visible"},
        ()
      )
    )
    >
      (React.string(label))
    </button>
  </>
};
