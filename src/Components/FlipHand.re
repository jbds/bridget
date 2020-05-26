[@react.component]
let make = (~dispatch: Global.action => unit) => {
  <>
  <table
    style=(
      ReactDOMRe.Style.make(
        ~color={"#404040"}, 
        ~fontSize={"2.5vh"},
        ~padding={"0px"},
        ~borderCollapse={"collapse"},
        ~margin={"auto"},
        ()
      )
    )
  >
  <tbody>
    <tr>
      <td>
          (React.string(" "))
      </td>
      <td>
        <ButtonStd dispatch action=Flip(North) label="North" />
      </td>
      <td>
        (React.string(" "))
      </td>
    </tr>
    <tr>
      <td>
        <ButtonStd dispatch action=Flip(West) label="West" />
      </td>
      <td
      >
        (React.string("< Flip >"))
      </td>
      <td>
        <ButtonStd dispatch action=Flip(East) label="East" />
      </td>
    </tr>
    <tr>
      <td>
          (React.string(" "))
      </td>
      <td>
        <ButtonStd dispatch action=Flip(South) label="South" />
      </td>
      <td>
        (React.string(" "))
      </td>
    </tr>
  </tbody>
  </table>
  </>
};