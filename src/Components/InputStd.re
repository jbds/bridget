[@react.component]
let make = (~id: string) => {
  <>
    <input 
    id=id
    //onClick=((_e) => Js.log("Clicked input element"))
    //onChange=((_e) => Js.log("Changed input element"))
    style=(
      ReactDOMRe.Style.make(
        ~color={"#808080"},
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"0vh"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #26653B"}, 
        //~borderRadius={"5px"},
        ~backgroundColor={"#FFFFFF"},
        ~width={"10vh"},
        ~textAlign={"center"},
        ()
      )
    )
    />
  </>
};
