[@react.component]
let make = (~state: Global.state) => {
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
      <tr style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ()))>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 1vh 1vh 1vh"}, ()))>
          (React.string("Vuln"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 1vh 1vh 1vh"}, ()))>
          (React.string("Decl"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 2vh 1vh 2vh"}, ()))>
          (React.string("Bid"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 1vh 1vh 1vh"}, ()))>
          (React.string("Tricks"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 2vh 1vh 2vh"}, ()))>
          (React.string("N-S"))
        </td>
        <td style=(ReactDOMRe.Style.make(~padding={"1vh 2vh 1vh 2vh"}, ()))>
          (React.string("E-W"))</td>
      </tr>
      // some example rows
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("None"))</td>
      //   <td>(React.string("W"))</td>
      //   <td>(React.string("1C"))</td>
      //   <td>(React.string("13"))</td>
      //   <td>(React.string("9999"))</td>
      //   <td>(React.string(""))</td>
      // </tr>
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("W"))</td>
      //   <td>(React.string("N"))</td>
      //   <td>(React.string("6NT"))</td>
      //   <td>(React.string("8"))</td>
      //   <td>(React.string(""))</td>
      //   <td>(React.string("-777"))</td>
      // </tr>
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("N"))</td>
      //   <td>(React.string("N"))</td>
      //   <td>(React.string("3H"))</td>
      //   <td>(React.string("6"))</td>
      //   <td>(React.string("-25"))</td>
      //   <td>(React.string(""))</td>
      // </tr>
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("All"))</td>
      //   <td>(React.string("E"))</td>
      //   <td>(React.string("1NT"))</td>
      //   <td>(React.string("7"))</td>
      //   <td>(React.string("50"))</td>
      //   <td>(React.string(""))</td>
      // </tr>
      // a subtotal row
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string("."))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ~color={"#f8f8f8"}, ()))>(React.string(""))</td>
      //   <td>(React.string("1000"))</td>
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
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("W"))</td>
      //   <td>(React.string("N"))</td>
      //   <td>(React.string("6NT"))</td>
      //   <td>(React.string("8"))</td>
      //   <td>(React.string(""))</td>
      //   <td>(React.string("-777"))</td>
      // </tr>
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("N"))</td>
      //   <td>(React.string("N"))</td>
      //   <td>(React.string("3H"))</td>
      //   <td>(React.string("6"))</td>
      //   <td>(React.string("-25"))</td>
      //   <td>(React.string(""))</td>
      // </tr>
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
      //   <td>(React.string("All"))</td>
      //   <td>(React.string("E"))</td>
      //   <td>(React.string("1NT"))</td>
      //   <td>(React.string("7"))</td>
      //   <td>(React.string("50"))</td>
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
              | Some("Clubs") => "#404040"
              | Some("Diamonds") => "red"
              | Some("Hearts") => "red"
              | Some("Spades") => "#404040"
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
              | None => "X"
              | Some(n) => getLevelPlusPossibleNT(n)
            };
          <tr key={string_of_int(Random.int(1000000))} style=(ReactDOMRe.Style.make(~backgroundColor={"white"}, ()))>
            <td>{React.string(x.vulnerable)}</td>
            <td>{React.string(String.sub(Shuffle.pocAsString(x.contractDeclarer), 0, 1))}</td>
            //<td>{React.string(Shuffle.optionIntAsString(x.contractLevel))}</td>
            <td>
              <ChicagoBidTableCell 
                textValue=textValue
                denominationValue=denominationValue
                denominationColor=denominationColor
              />
            </td>
            <td>{React.string(string_of_int(x.totalTricks))}</td>
            <td>{React.string(Shuffle.optionIntAsString(x.scoreNorthSouth))}</td>
            <td>{React.string(Shuffle.optionIntAsString(x.scoreWestEast))}</td>
          </tr>
        })
        -> React.array
      }
    </tbody>
    </table>
  </>
};