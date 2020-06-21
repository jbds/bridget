[@react.component]
let make = (~spacerWidth: string) => {
  <>
    <div
    style=(
      ReactDOMRe.Style.make(
        ~display={"inline"},
        ~color={"#000000"}, 
        ~fontSize={"2.0vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"0.0vh " ++ spacerWidth ++ " 0.0vh 0.0vh"},
        ~width={"0px"},
        ~textAlign={"center"},
        ()
      )
    )
    >
    (React.string(""))
    </div>
  </>
};
