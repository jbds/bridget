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
    // we always want a header row
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
    {
      let emptyFlexbox = {
        <BidFlexbox 
          textValue="---" 
          textColor="#404040" 
          denominationValue="" 
          denominationColor="white" 
          backgroundColor="#ffffff00"
        />
      };
      let arrayOfFlexboxes = {
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
        )
        -> React.array
      };
      if (List.length(state.bids) === 0) {
        // if bids length is zero, render nothing else
        Js.log("Abort render on bids length zero");
        React.null;
      } else if ((List.hd(List.rev(state.bids))).contractPointOfCompass === Some("West")){
        arrayOfFlexboxes;
      } else if ((List.hd(List.rev(state.bids))).contractPointOfCompass === Some("North")){
        // wrap 2 react elements inside a fragment
        <>
        emptyFlexbox
        arrayOfFlexboxes
        </>
      } else if ((List.hd(List.rev(state.bids))).contractPointOfCompass === Some("East")){
        // wrap react elements inside a fragment
        <>
        emptyFlexbox
        emptyFlexbox
        arrayOfFlexboxes
        </>
      } else if ((List.hd(List.rev(state.bids))).contractPointOfCompass === Some("South")){
        // wrap react elements inside a fragment
        <>
        emptyFlexbox
        emptyFlexbox
        emptyFlexbox
        arrayOfFlexboxes
        </>
      } else {
        React.null;
      };
    }
    // // but then we want zero, 1, 2 or 3 empty boxes
    // // example empty flexbox
    // <BidFlexbox 
    //   textValue="---" 
    //   textColor="#404040" 
    //   denominationValue="" 
    //   denominationColor="white" 
    //   backgroundColor="#ffffff00"
    // />
    // // example empty flexbox
    // <BidFlexbox 
    //   textValue="---" 
    //   textColor="#404040" 
    //   denominationValue="" 
    //   denominationColor="white" 
    //   backgroundColor="#ffffff00"
    // />
    // // map over all the items in list(bid) aka bids
    // // ref RR examples
    // {
    //   Array.of_list(List.rev(state.bids))
    //   -> Belt.Array.map(x => {
    //     let getLevelIfNone: string = {
    //       if (x.isPass) {
    //         "Pass"
    //       } else if (x.isDoubled) {
    //         "X"
    //       } else if (x.isRedoubled) {
    //         "XX"
    //       } else {
    //         "Error"
    //       }
    //     };
    //     let getLevelPlusPossibleNT =  (n) => {
    //       if (x.contractSuit === Some("NoTrumps")) {
    //         string_of_int(n) ++ "NT"
    //       } else {
    //         string_of_int(n)
    //       }
    //     }
    //     let textValue = 
    //       switch (x.contractLevel) {
    //         | None => getLevelIfNone
    //         | Some(n) => getLevelPlusPossibleNT(n)
    //       };
    //     let denominationValue =
    //       switch(x.contractSuit) {
    //         | None => "" //{js|\u2669|js}  // dummy glyph
    //         | Some("Clubs") => {js|\u2663|js}
    //         | Some("Diamonds") => {js|\u2666|js}
    //         | Some("Hearts") => {js|\u2665|js}
    //         | Some("Spades") => {js|\u2660|js}
    //         | Some("NoTrumps") => ""
    //         | Some(_) => "Error"
    //       };
    //     let textColor =
    //       switch (textValue) {
    //         | "" => "white"
    //         | "Pass" => "#26653B"
    //         | "X" => "#E00000"
    //         | "XX" => "blue"
    //         | _ => "#404040"
    //       };
    //     let denominationColor = {
    //       switch (x.contractSuit) {
    //         | None => "white"
    //         | Some("Clubs") => "#404040"
    //         | Some("Diamonds") => "red"
    //         | Some("Hearts") => "red"
    //         | Some("Spades") => "#404040"
    //         | Some("NoTrumps") => "white"
    //         | Some(_) => "white"
    //       }
    //     };
    //     <BidFlexbox 
    //       // key is not used, but React expects it
    //       key={string_of_int(Random.int(1000000))}
    //       textValue=textValue
    //       textColor=textColor 
    //       denominationValue=denominationValue
    //       denominationColor=denominationColor
    //       backgroundColor="#ffffff"
    //     />
    //   }
    //   )
    //   -> React.array
    // }
  </div>
};

