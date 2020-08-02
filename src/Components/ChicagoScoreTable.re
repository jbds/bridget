[@react.component]
let make = (~state: TopLevel.state) => {
  List.length(state.chicagoScoreSheet) == 0
  ?
  React.null
  :
  <>
    <table 
    style=(
      ReactDOMRe.Style.make(
        ~fontSize={"2.0vh"},
        ~fontFamily={"Trebuchet MS"},
        ~color={"#26653B"},
        ~margin={"auto"},
        //~width={"calc(var(--vh, 1vh) * 45)"},
        ~textAlign={"center"},
        ()
      )
    )
    >
    <thead>
    </thead>
    <tbody>
      <tr style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#000000"}, ()))>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 1vh 1vh 1vh"}, ()))>
          (React.string("Vuln"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 0.5vh 1vh 0.5vh"}, ()))>
          (React.string("Decl"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 1.5vh 1vh 1.5vh"}, ()))>
          (React.string("Bid"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 0vh 1vh 0vh"}, ~width={"6.5vh"}, ()))>
          (React.string("NS Tricks"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 0vh 1vh 0vh"}, ~width={"6.5vh"}, ()))>
          (React.string("NS Score"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 0vh 1vh 0vh"}, ~width={"6.5vh"}, ()))>
          (React.string("EW Tricks"))
        </td>
        <td 
          style=(ReactDOMRe.Style.make(~padding={"1vh 0vh 1vh 0vh"}, ~width={"6.5vh"}, ()))
        >
          //(React.string("E-W" ++ {js|\u0026\u006c\u0074\u003b\u0062\u0072\u002f\u0026\u0067\u0074\u003b|js} ++"Score"))
          (React.string("EW Score"))
        </td>
      </tr>
      // some example rows
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("All"))</td>
      //   <td>(React.string("E"))</td>
      //   <td>(React.string("1NT"))</td>
      //   <td>(React.string("7"))</td>
      //   <td>(React.string("50"))</td>
      //   <td>(React.string("6"))</td>
      //   <td>(React.string(""))</td>
      // </tr>
      // a subtotal row
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string("."))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td>(React.string("1000"))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td>(React.string("500"))</td>
      // </tr>
      // // some example rows
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("None"))</td>
      //   <td>(React.string("W"))</td>
      //   <td>(React.string("1C"))</td>
      //   <td>(React.string("13"))</td>
      //   <td>(React.string("9999"))</td>
      //   <td>(React.string(""))</td>
      // </tr>
      // // a subtotal row
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string("."))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td>(React.string("1000"))</td>
      //   <td>(React.string("500"))</td>
      // </tr>
      // ref RR examples
      {
        // let contractSuitAsString = (contractSuit) = {

        // };
        Belt.List.toArray(Belt.List.reverse(state.chicagoScoreSheet))
        -> Belt.Array.map(x => {
          // need some helper funcs here like those in BidTable.re
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
          let denominationColor = {
            switch (x.contractSuit) {
              | None => "white"
              | Some("Clubs") => "#606060"
              | Some("Diamonds") => "#FF0000A0"
              | Some("Hearts") => "#FF0000A0"
              | Some("Spades") => "#606060"
              | Some("NoTrumps") => "white"
              | Some(_) => "white"
            }
          };
          let getLevelPlusPossibleNT =  (n) => {
            if (x.contractSuit === Some("NoTrumps")) {
              string_of_int(n) ++ "NT"
            } else {
              string_of_int(n)
            }
          };
          let textValue = 
            switch (x.contractLevel) {
              | None => ""
              | Some(n) => getLevelPlusPossibleNT(n)
            };
          <tr key={string_of_int(Random.int(1000000))} style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ~color="#606060", ()))>
            <td
              style=(ReactDOMRe.Style.make(~backgroundColor={
                (x.vulnerable !== "") 
                ? 
                "white" 
                : 
                "#f0f0f0"}, ()))            
            >
              {React.string(x.vulnerable)}
            </td>
            <td
              style=(ReactDOMRe.Style.make(~backgroundColor={
                (x.vulnerable !== "") 
                ? 
                "white" 
                : 
                "#f0f0f0"}, ()))            
            >
              {
                x.contractDeclarer === None 
                ? 
                React.string("") 
                : 
                React.string(String.sub(Shuffle.pocAsString(x.contractDeclarer), 0, 1))
              }
            </td>
            <td
              style=(ReactDOMRe.Style.make(~backgroundColor={
                (x.vulnerable !== "") 
                ? 
                "white" 
                : 
                "#f0f0f0"}, ()))            
            >
              <ChicagoBidTableCell 
                textValue=textValue
                denominationValue=denominationValue
                denominationColor=denominationColor
                suffixTextValue={x.isDoubled ? "x" : (x.isRedoubled ? "xx" : "")}
              />
            </td>
            <td
              style=(ReactDOMRe.Style.make(~backgroundColor={
                (x.vulnerable !== "") 
                ? 
                "white" 
                : 
                "#f0f0f0"}, ()))            
            >
              {
                switch (x.totalTricksNorthSouth) {
                  | None => React.string("")
                  | Some(n) => React.string(string_of_int(n))
                }
              }
            </td>
            <td
              // style=(ReactDOMRe.Style.make(~backgroundColor={
              //   (x.contractDeclarer === Some("North")) 
              //   || 
              //   (x.contractDeclarer === Some("South")) 
              //   ||
              //   (x.scoreWestEast === None)
              //   ? 
              //   "white" 
              //   : 
              //   "#f0f0f0"}, ()))    
              style=(ReactDOMRe.Style.make(
                ~textAlign={"right"}, 
                ~paddingRight={"1vh"}, 
                ~color={x.vulnerable !== "" ? "#606060" : "#000000"},
                ()
                )
              )   
            >
              {React.string(Shuffle.optionIntAsString(x.scoreNorthSouth))}
            </td>
            <td
              style=(ReactDOMRe.Style.make(~backgroundColor={
                (x.vulnerable !== "") 
                ? 
                "white" 
                : 
                "#f0f0f0"}, ()))            
            >
              {
                switch (x.totalTricksWestEast) {
                  | None => React.string("")
                  | Some(n) => React.string(string_of_int(n))
                }
              }
            </td>
            <td
              style=(ReactDOMRe.Style.make(
                ~textAlign={"right"}, 
                ~paddingRight={"1vh"}, 
                ~color={x.vulnerable !== "" ? "#606060" : "#000000"},
                ()
                )
              )   
            >
              {React.string(Shuffle.optionIntAsString(x.scoreWestEast))}
            </td>
          </tr>
        })
        -> React.array
      }
    </tbody>
    </table>
  </>
};