[@react.component]
let make = (
  ~state: Global.state
  ) => {
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
    <BidFlexbox textValue="West" textColor="#404040" denominationValue="" denominationColor="white" backgroundColor="#c0c0c0" state />
    <BidFlexbox 
      textValue="North" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#e8e8e8"
      state
    />
    <BidFlexbox 
      textValue="East" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#c0c0c0"
      state
    />
    <BidFlexbox 
      textValue="South" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#e8e8e8"
      state
    />
    // example empty flexbox
    <BidFlexbox 
      textValue="---" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#ffffff00"
      state
    />
    // example bid display NT
    <BidFlexbox 
      textValue="4NT" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="#404040" 
      backgroundColor="#ffffff"
      state
    />
    // example bid display 1D
    <BidFlexbox 
      textValue="1" 
      textColor="#404040" 
      denominationValue={js|\u2665|js}
      denominationColor="red" 
      backgroundColor="#ffffff"
      state
    />
    // example Pass
    <BidFlexbox 
      textValue="Pass" 
      textColor="#26653B" 
      denominationValue="" 
      denominationColor="#404040" 
      backgroundColor="#ffffff"
      state
    />
    // example X
    <BidFlexbox 
      textValue="X" 
      textColor="#E00000" 
      denominationValue="" 
      denominationColor="#404040" 
      backgroundColor="#ffffff"
      state
    />
    // example XX
    <BidFlexbox 
      textValue="XX" 
      textColor="blue" 
      denominationValue="" 
      denominationColor="#404040" 
      backgroundColor="#ffffff"
      state
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
