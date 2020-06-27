[@react.component]
let make = (
  ~textValue: string,
  ~textColor: string,
  ~denominationValue: string,
  ~denominationColor: string,
  ~backgroundColor: string,
  ~state: Global.state
) => {
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          // background transparent
          ~backgroundColor={backgroundColor},
          ~border={"1px solid #c0c0c0"}, 
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      <span
        style=(
          ReactDOMRe.Style.make(
            ~color={textColor},
            ()
          )
        )
      >
        (React.string({textValue}))
      </span>
      // unicode character requires a reduction in font size, reason unclear
      <span 
        style=(
          ReactDOMRe.Style.make(
            ~color={denominationColor},
            ~fontSize={"2.0vh"},
            ()
          )
        )
      >
        (React.string({denominationValue}))
      </span>
    </div>
};