[@react.component]
let make = (~id: string, ~text: string) => {
  <>
    <span
    id=id
    onClick=((_e) => Js.log("Clicked span element"))
    style=(
      ReactDOMRe.Style.make(
        ~color={"#26653B"}, 
        ~fontSize={"2.0vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"0vh"},
        // bug - borderColor single attribute not recognised       
        //~border={"1px solid #26653B"}, 
        //~borderRadius={"5px"},
        //~backgroundColor={"#FFFFFF"},
        ~width={"10vh"},
        ~textAlign={"center"},
        ()
      )
    )
    >
    (React.string(text))
    </span>
  </>
};
