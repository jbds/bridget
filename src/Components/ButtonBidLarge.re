[@react.component]
let make = (
  ~dispatch: Global.action => unit, 
  ~action: Global.action, 
  ~label: string, 
  ~id: string, 
  ~backgroundColor: string,
  ~isActive: bool=true,
  ~isVisible: bool=true
  ) => {
  <>
    <button 
    id=id
    onClick=((_e) => dispatch(action))//Js.log("Clicked shuffle"))//
    style=(
      ReactDOMRe.Style.make(
        ~color={"white"}, 
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~height={"6.0vh"},
        ~width={"11.5vh"},
        ~margin={"0.25vh"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #26653B"}, 
        ~borderRadius={"5px"},
        ~backgroundColor=backgroundColor, //{isActive ? "#ffffff" : "#ffe0e0"},
        ~display={isVisible ? "inline" : "none"},
        ()
      )
    )
    >
      (React.string(label))
    </button>
  </>
};
