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
    <BidFlexbox 
      textValue="West" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#c0c0c0" 
    />
    <BidFlexbox 
      textValue="North" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#e8e8e8"
    />
    <BidFlexbox 
      textValue="East" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#c0c0c0"
    />
    <BidFlexbox 
      textValue="South" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#e8e8e8"
    />
    // example empty flexbox
    <BidFlexbox 
      textValue="---" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#ffffff00"
    />
    // example empty flexbox
    <BidFlexbox 
      textValue="---" 
      textColor="#404040" 
      denominationValue="" 
      denominationColor="white" 
      backgroundColor="#ffffff00"
    />
    // example bid display NT
    // <BidFlexbox 
    //   textValue="4NT" 
    //   textColor="#404040" 
    //   denominationValue="" 
    //   denominationColor="#404040" 
    //   backgroundColor="#ffffff"
    //   state
    // />
    // example bid display 1D
    // <BidFlexbox 
    //   textValue="1" 
    //   textColor="#404040" 
    //   denominationValue={js|\u2665|js}
    //   denominationColor="red" 
    //   backgroundColor="#ffffff"
    //   state
    // />
    // example Pass
    // <BidFlexbox 
    //   textValue="Pass" 
    //   textColor="#26653B" 
    //   denominationValue="" 
    //   denominationColor="#404040" 
    //   backgroundColor="#ffffff"
    //   state
    // />
    // example X
    // <BidFlexbox 
    //   textValue="X" 
    //   textColor="#E00000" 
    //   denominationValue="" 
    //   denominationColor="#404040" 
    //   backgroundColor="#ffffff"
    //   state
    // />
    // example XX
    // <BidFlexbox 
    //   textValue="XX" 
    //   textColor="blue" 
    //   denominationValue="" 
    //   denominationColor="#404040" 
    //   backgroundColor="#ffffff"
    //   state
    // />
    // map over all the items in list(bid) aka bids
    // ref RR examples
    {
      Array.of_list(List.rev(state.bids))
      -> Belt.Array.map(x => {
        let getLevelIfNone: string = {
          if (x.isPass) {
            "Pass"
          } else if (x.isDoubled) {
            "X"
          } else if (x.isRedoubled) {
            "XX"
          } else {
            "Error"
          }
        };
        let getLevelPlusPossibleNT =  (n) => {
          if (x.contractSuit === Some("NoTrumps")) {
            string_of_int(n) ++ "NT"
          } else {
            string_of_int(n)
          }
        }
        let textValue = 
          switch (x.contractLevel) {
            | None => getLevelIfNone
            | Some(n) => getLevelPlusPossibleNT(n)
          };
        let denominationValue =
          switch(x.contractSuit) {
            | None => "" //{js|\u2669|js}  // dummy glyph
            | Some("Clubs") => {js|\u2663|js}
            | Some("Diamonds") => {js|\u2666|js}
            | Some("Hearts") => {js|\u2665|js}
            | Some("Spades") => {js|\u2660|js}
            | Some("NoTrumps") => ""
            | Some(_) => "Error"
          };
        let textColor =
          switch (textValue) {
            | "" => "white"
            | "Pass" => "#26653B"
            | "X" => "#E00000"
            | "XX" => "blue"
            | _ => "#404040"
          };
        let denominationColor = {
          switch (x.contractSuit) {
            | None => "white"
            | Some("Clubs") => "#404040"
            | Some("Diamonds") => "red"
            | Some("Hearts") => "red"
            | Some("Spades") => "#404040"
            | Some("NoTrumps") => "white"
            | Some(_) => "white"
          }
        };
        <BidFlexbox 
          // key is not used, but React expects it
          key={string_of_int(Random.int(1000000))}
          textValue=textValue
          textColor=textColor 
          denominationValue=denominationValue
          denominationColor=denominationColor
          backgroundColor="#ffffff"
        />
      }

        // <tr key={x.player}>
        //   <td>{React.string(x.player)}</td>
        //   <td>
        //     <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "North" ? "" : "North"}, player: x.player}) label="N" id={"btnN" ++ x.player} isActive={x.pointOfCompass == "North" ? true : false}/>
        //     <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "South" ? "" : "South"}, player: x.player}) label="S" id={"btnS" ++ x.player} isActive={x.pointOfCompass == "South" ? true : false}/>
        //     <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "West" ? "" : "West"}, player: x.player}) label="W" id={"btnW" ++ x.player} isActive={x.pointOfCompass == "West" ? true : false}/>
        //     <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "East" ? "" : "East"}, player: x.player}) label="E" id={"btnE" ++ x.player} isActive={x.pointOfCompass == "East" ? true : false}/>
        //     <ButtonObserver dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "Observer" ? "" : "Observer"}, player: x.player}) label="_" id={"btnO" ++ x.player} isActive={x.pointOfCompass == "Observer" ? true : false}/>
        //   </td>
        // </tr>
      )
      -> React.array
    }
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
