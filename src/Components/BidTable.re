[@react.component]
let make = () => {
  <div
    style=(
      ReactDOMRe.Style.make(
        ~fontSize={"3.25vh"},
        ~fontFamily={"Trebuchet MS"},
        ~color={"#404040"},
        ~margin={"auto"},
        ~width={"calc(var(--vh, 1vh) * 46)"},
        ~textAlign={"center"},
        // flex parent specific additions
        // background transparent
        ~backgroundColor={"#f8f8f800"},
        // top and left on parent, right and bottom on child
        ~border={"1px solid #c0c0c0"}, 
        ~borderWidth={"1px 0 0 1px"},
        ~display={"flex"},
        ~flexDirection={"row"},
        ~flexWrap={"wrap"},
        ~justifyContent={"flex-start"},
        ~alignItems={"flex-start"},
        ~alignContent={"flex-start"},
        ()
      )
    )
  >
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          ~backgroundColor={"#c0c0c0"},
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~border={"1px solid #c0c0c0"}, 
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      (React.string("West"))
    </div>
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          ~backgroundColor={"#e8e8e8"},
          ~border={"1px solid #c0c0c0"}, 
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      (React.string("North"))
    </div>
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          ~backgroundColor={"#c0c0c0"},
          ~border={"1px solid #c0c0c0"}, 
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      (React.string("East"))
    </div>
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          ~backgroundColor={"#e8e8e8"},
          ~border={"1px solid #c0c0c0"}, 
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      (React.string("South"))
    </div>
    // example bid display
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          // background transparent
          ~backgroundColor={"#f8f8f800"},
          ~border={"1px solid #c0c0c0"}, 
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      <span>(React.string("1"))</span>
      // unicode character requires a reduction in font size, reason unclear
      <span 
        style=(
          ReactDOMRe.Style.make(
            ~color={"red"},
            ~fontSize={"2.0vh"},
            ()
          )
        )
      >
        (React.string({js|\u2665|js}))
      </span>
    </div>
    // example Pass
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          // background transparent
          ~backgroundColor={"#f8f8f800"},
          ~border={"1px solid #c0c0c0"}, 
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      //<span>(React.string("1"))</span>
      <span 
        style=(
          ReactDOMRe.Style.make(
            ~color={"#26653B"},
            ()
          )
        )
      >
        (React.string("Pass"))
      </span>
    </div>
    // example X
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          // background transparent
          ~backgroundColor={"#f8f8f800"},
          ~border={"1px solid #c0c0c0"}, 
          // right and bottom on child
          ~borderWidth={"0px 1px 1px 0"},
          ~flex={"0 0 calc(var(--vh, 1vh) * 11)"},
          ()
        )
      )
    >
      //<span>(React.string("1"))</span>
      <span 
        style=(
          ReactDOMRe.Style.make(
            ~color={"#E00000"},
            ()
          )
        )
      >
        (React.string("X"))
      </span>
    </div>
    // example XX
    <div
      style=(
        ReactDOMRe.Style.make(
          // flex child attributes
          // background transparent
          ~backgroundColor={"#f8f8f800"},
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
            ~color={"#000080"},
            ()
          )
        )
      >
        (React.string("XX"))
      </span>
    </div>
    <BidFlexbox 
      textValue="2" 
      textColor="blue" 
      denominationValue={js|\u2666|js} 
      denominationColor="silver" 
      backgroundColor="#ffffffff"
    />
  </div>
};


  // <>
  //   <table 
  //   style=(
  //     ReactDOMRe.Style.make(
  //       ~fontSize={"3.25vh"},
  //       ~fontFamily={"Trebuchet MS"},
  //       ~color={"#404040"},
  //       ~margin={"auto"},
  //       ~width={"calc(var(--vh, 1vh) * 45)"},
  //       ~textAlign={"center"},
  //       ()
  //     )
  //   )
  //   >
  //   <thead>
  //     <tr>
  //       <th
  //       style=(
  //         ReactDOMRe.Style.make(
  //           ~width={"25%"},
  //           ()
  //         )
  //       )
  //       >(React.string("West"))</th>
  //       <th>(React.string("North"))</th>
  //       <th
  //       style=(
  //         ReactDOMRe.Style.make(
  //           ~width={"25%"},
  //           ()
  //         )
  //       )
  //       >(React.string("East"))</th>
  //       <th>(React.string("South"))</th>
  //     </tr>
  //   </thead>
  //   <tbody>
  //     <tr>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //     </tr>
  //     <tr>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //     </tr>
  //     <tr>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //     </tr>
  //     <tr>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //     </tr>
  //     <tr>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //     </tr>
  //     <tr>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //     </tr>
  //     <tr>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //       <td>(React.string("Pass"))</td>
  //     </tr>
  //   </tbody>
  //   </table>
  // </>
