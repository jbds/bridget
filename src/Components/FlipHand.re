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
        <ButtonStd dispatch action=Flip(North) label="North" id="btnNorth" isActive=true/>
      </td>
      <td>
        (React.string(" "))
      </td>
    </tr>
    <tr>
      <td>
        <ButtonStd dispatch action=Flip(West) label="West" id="btnWest" isActive=true/>
      </td>
      <td
      >
        (React.string("< Flip >"))
      </td>
      <td>
        <ButtonStd dispatch action=Flip(East) label="East" id="btnEast" isActive=true/>
      </td>
    </tr>
    <tr>
      <td>
          (React.string(" "))
      </td>
      <td>
        <ButtonStd dispatch action=Flip(South) label="South" id="btnSouth" isActive=true/>
      </td>
      <td>
        (React.string(" "))
      </td>
    </tr>
  </tbody>
  </table>
  </>
};