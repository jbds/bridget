[@react.component]
let make = () => {
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
      // <tr style=(ReactDOMRe.Style.make(~backgroundColor={"#f8f8f8"}, ()))>
      //   <td style=(ReactDOMRe.Style.make(~fontFamily={"Arial Narrow"}, ()))>
      //     (React.string("Vulnerable"))
      //   </td>
      //   <td style=(ReactDOMRe.Style.make(~fontFamily={"Arial Narrow"}, ()))>
      //     (React.string("Declarer"))
      //   </td>
      //   <td style=(ReactDOMRe.Style.make(~fontFamily={"Arial Narrow"}, ()))>
      //     (React.string("Contract"))
      //   </td>
      //   <td style=(ReactDOMRe.Style.make(~fontFamily={"Arial Narrow"}, ()))>
      //     (React.string("Tricks"))
      //   </td>
      //   <td style=(ReactDOMRe.Style.make(~fontFamily={"Arial Narrow"}, ~padding={"1vh 2.5vh 1vh 2.5vh"}, ()))>
      //     (React.string("N-S"))
      //   </td>
      //   <td style=(ReactDOMRe.Style.make(~fontFamily={"Arial Narrow"}, ~padding={"1vh 2.5vh 1vh 2.5vh"}, ()))>
      //     (React.string("E-W"))</td>
      // </tr>
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
    </tbody>
    </table>
  </>
};