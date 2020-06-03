[@react.component]
let make = (~arr: array(Shuffle.pointOfCompassAndPlayer), ~dispatch) => {
  Js.log(arr);
  <>
    <table
    style=(
      ReactDOMRe.Style.make(
        ~color={"#26653B"}, 
        ~fontSize={"2.5vh"},
        ~fontFamily={"Trebuchet MS"},
        ~margin={"auto"},
        // bug - borderColor single attribute not recognised       
        ~border={"1px solid #26653B"}, 
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
              ()
            )
          )
        >
          (React.string("Player"))
        </td>
      </tr>
      // ref RR examples
      {
        arr
        -> Belt.Array.map(x =>
          <tr key={x.player}>
            <td>
              <ButtonStd dispatch action=Test label="N" id={"btnN" ++ x.player}/>
              <ButtonStd dispatch action=Test label="S" id={"btnS" ++ x.player}/>
              <ButtonStd dispatch action=Test label="W" id={"btnW" ++ x.player}/>
              <ButtonStd dispatch action=Test label="E" id={"btnE" ++ x.player}/>
            </td>
            <td>{React.string("x" ++ x.player)}</td>
          </tr>
        )
        -> React.array
      }
    </tbody>
    </table>
  </>
};
