[@react.component]
// based loosely on BidFlexbox.re
let make = (
  ~textValue: string,
  // ~textColor: string,
  ~denominationValue: string,
  ~denominationColor: string,
  // ~backgroundColor: string,
  ~suffixTextValue: string
) => {
    <div
      // style=(
      //   ReactDOMRe.Style.make(
      //     // flex child attributes
      //     // background transparent
      //     ~backgroundColor={backgroundColor},
      //     ~border={"1px solid #c0c0c0"}, 
      //     // right and bottom on child
      //     ~borderWidth={"0px 1px 1px 0"},
      //     ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
      //     // force height otherwise glyphs require more height than plain ascii characters, reason unknown
      //     ~height={"4.5vh"},
      //     // tweak padding dependent on whether glyph is rendered
      //     //~padding={denominationValue === "" ? "0 0 0 0" : "0 0 0 0"},
      //     ~padding={denominationValue === "" ? "0.5vh 0 0 0" : "0 0 0.5vh 0"},
      //     ()
      //   )
      // )
    >
      <span
        style=(
          ReactDOMRe.Style.make(
            //~color={textColor},
            ~color={"#606060"},
            ()
          )
        )
      >
        (React.string({textValue}))
        //(React.string("7"))
      </span>
      // unicode character requires a reduction in font size, reason unclear
      // better to leave at full size and always render a dummy invisible denomination
      <span 
        style=(
          ReactDOMRe.Style.make(
            ~color={denominationColor},
            //~color={"#C00000"},
            //~fontSize={"2.0vh"},
            ()
          )
        )
      >
        (React.string({denominationValue}))
        //(React.string({js|\u2665|js}))
      </span>
      <span
        style=(
          ReactDOMRe.Style.make(
            //~color={textColor},
            ~color={"#606060"},
            ()
          )
        )
      >
        (React.string({suffixTextValue}))
      </span>
    </div>
};