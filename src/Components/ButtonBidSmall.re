[@react.component]
let make = (
  ~dispatch: Global.action => unit, 
  ~action: Global.action, 
  ~label: string, 
  ~id: string, 
  ~color: string,
  ~isActive: bool=true,
  ~isVisible: bool=true
  ) => {
  <>
    <button 
    id=id
    onClick=((_e) => dispatch(action)) //Js.log("Clicked shuffle"))
    style=(
      ReactDOMRe.Style.make(
        ~color=color, 
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~height={"6.25vh"},
        ~width={"calc(var(--vh, 1vh) * 6.25)"},
        ~margin={"1vh 0.25vh 0.25vh 0.25vh"},
        ~padding={"0vh"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #26653B"}, 
        ~borderRadius={"5px"},
        ~backgroundColor={isActive ? "#ffffff" : "#ffe0e0"},
        // removes element from doc - NOT what we want
        //~display={isVisible ? "inline" : "none"},
        ~visibility={isVisible ? "visible" : "hidden"},
        ()
      )
    )
    >
      (React.string(label))
    </button>
  </>
};
