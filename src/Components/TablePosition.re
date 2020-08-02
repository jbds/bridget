[@react.component]
let make = (~state: TopLevel.state, ~dispatch) => {
  Array.length(state.pointOfCompassAndPlayers) == 0
  ?
  React.null
  :
  <>
    <table
    style=(
      ReactDOMRe.Style.make(
        ~color={"#404040"}, // was 26653B
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"auto"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #800000"}, // was #26653B // suspect no effect
        ~borderCollapse={"collapse"},
        //~borderRadius={"5px"},
        //~backgroundColor={"#FFFFFF"},
        ~width={"30vh"},
        ~textAlign={"center"},
        ~padding={"0px"},
        ~whiteSpace={"nowrap"},
        ()
      )
    )
    >
    <tbody>
      <tr>
        // <td
        //   style=(
        //     ReactDOMRe.Style.make(
        //       ~textAlign={"center"},
        //       ~backgroundColor={"#f8f8f8"},
        //       ()
        //     )
        //   )
        // >
        //   (React.string(" "))
        // </td>
        <td
          colSpan={2}
          style=(
            ReactDOMRe.Style.make(
              ~fontSize={"2.0vh"},
              ~textAlign={"center"},
              ~whiteSpace={"nowrap"},
              ~border={"1px solid #f8f8f8"},
              ~borderCollapse={"collapse"},
              ~backgroundColor={"#f8f8f8"},
              ()
            )
          )
        >
          (React.string("---------- Table Seating ----------"))
        </td>
      </tr>
      // ref RR examples
      {
        state.pointOfCompassAndPlayers
        -> Belt.Array.map(x =>
          <tr key={x.player}>
            <td
              style=(
                ReactDOMRe.Style.make(
                  // bug - borderColor single attribute not recognised       
                  ~border={"1px solid #f8f8f8"}, // use #f8f8f8 to hide
                  ~borderCollapse={"collapse"},
                  ~textAlign={"right"},
                  ()
                )
              )
            >{React.string(x.player)}</td>
            <td
              style=(
                ReactDOMRe.Style.make(
                  // bug - borderColor single attribute not recognised       
                  ~border={"1px solid #f8f8f8"}, // was #26653B // suspect no effect
                  ~borderCollapse={"collapse"},
                  ()
                )
              )
            >
              <ButtonStd color="#404040" dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "West" ? "" : "West"}, player: x.player}) label="W" id={"btnW" ++ x.player} isActive={x.pointOfCompass == "West" ? true : false}/>
              <ButtonStd color="#404040" dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "North" ? "" : "North"}, player: x.player}) label="N" id={"btnN" ++ x.player} isActive={x.pointOfCompass == "North" ? true : false}/>
              <ButtonStd color="#404040" dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "East" ? "" : "East"}, player: x.player}) label="E" id={"btnE" ++ x.player} isActive={x.pointOfCompass == "East" ? true : false}/>
              <ButtonStd color="#404040" dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "South" ? "" : "South"}, player: x.player}) label="S" id={"btnS" ++ x.player} isActive={x.pointOfCompass == "South" ? true : false}/>
              <ButtonObserver dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "Observer" ? "" : "Observer"}, player: x.player}) label="_" id={"btnO" ++ x.player} isActive={x.pointOfCompass == "Observer" ? true : false}/>
            </td>
          </tr>
        )
        -> React.array
      }
    </tbody>
    </table>
  </>
};
