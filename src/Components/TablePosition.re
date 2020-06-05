[@react.component]
let make = (~state: Shuffle.state, ~dispatch) => {
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
        <td
          style=(
            ReactDOMRe.Style.make(
              ~textAlign={"center"},
              ~whiteSpace={"nowrap"},
              ~backgroundColor={"#FFFFFF"},
              ()
            )
          )
        >
          (React.string("Table Position"))
        </td>
        <td
          style=(
            ReactDOMRe.Style.make(
              ~textAlign={"center"},
              ~backgroundColor={"#FFFFFF"},
              ()
            )
          )
        >
          (React.string("Player"))
        </td>
      </tr>
      // ref RR examples
      {
        state.pointOfCompassAndPlayers
        -> Belt.Array.map(x =>
          <tr key={x.player}>
            <td>
              <ButtonStd dispatch action=Test label="N" id={"btnN" ++ x.player}/>
              <ButtonStd dispatch action=Test label="S" id={"btnS" ++ x.player}/>
              <ButtonStd dispatch action=Test label="W" id={"btnW" ++ x.player}/>
              <ButtonStd dispatch action=Test label="E" id={"btnE" ++ x.player}/>
              <ButtonObserver dispatch action=Test label="X" id={"btnO" ++ x.player}/>
            </td>
            <td>{React.string(x.player)}</td>
          </tr>
        )
        -> React.array
      }
    </tbody>
    </table>
  </>
};
