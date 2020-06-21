[@react.component]
let make = (~state: Global.state, ~dispatch) => {
  Array.length(state.pointOfCompassAndPlayers) == 0
  ?
  React.null
  :
  <>
    <table
    style=(
      ReactDOMRe.Style.make(
        ~color={"#26653B"}, 
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"auto"},
        // bug - borderColor single attribute not recognised       
        //~border={"1px solid #26653B"}, 
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
              ~textAlign={"center"},
              ~whiteSpace={"nowrap"},
              ~backgroundColor={"#f8f8f8"},
              ()
            )
          )
        >
          (React.string("Table Seating"))
        </td>
      </tr>
      // ref RR examples
      {
        state.pointOfCompassAndPlayers
        -> Belt.Array.map(x =>
          <tr key={x.player}>
            <td>{React.string(x.player)}</td>
            <td>
              <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "North" ? "" : "North"}, player: x.player}) label="N" id={"btnN" ++ x.player} isActive={x.pointOfCompass == "North" ? true : false}/>
              <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "South" ? "" : "South"}, player: x.player}) label="S" id={"btnS" ++ x.player} isActive={x.pointOfCompass == "South" ? true : false}/>
              <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "West" ? "" : "West"}, player: x.player}) label="W" id={"btnW" ++ x.player} isActive={x.pointOfCompass == "West" ? true : false}/>
              <ButtonStd dispatch action=AssignPlayer({pointOfCompass: {x.pointOfCompass === "East" ? "" : "East"}, player: x.player}) label="E" id={"btnE" ++ x.player} isActive={x.pointOfCompass == "East" ? true : false}/>
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
