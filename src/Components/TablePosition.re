[@react.component]
let make = (~state: TopLevel.state, ~dispatch) => {
  Array.length(state.pointOfCompassAndPlayers) == 0
    ? React.null
    : <>
        <table
          style={ReactDOMRe.Style.make(
            ~color=[@reason.preserve_braces] "#404040", // was 26653B
            ~fontSize=[@reason.preserve_braces] "1.9vh",
            ~fontFamily=[@reason.preserve_braces] "Trebuchet MS",
            ~margin=[@reason.preserve_braces] "auto",
            // bug - borderColor single attribute not recognised
            ~border=[@reason.preserve_braces] "1px solid #800000", // was #26653B // suspect no effect
            ~borderCollapse=[@reason.preserve_braces] "collapse",
            //~borderRadius={"5px"},
            //~backgroundColor={"#FFFFFF"},
            ~width=[@reason.preserve_braces] "30vh",
            ~textAlign=[@reason.preserve_braces] "center",
            ~padding=[@reason.preserve_braces] "0px",
            ~whiteSpace=[@reason.preserve_braces] "nowrap",
            (),
          )}>
          <tbody>
            <tr>

                <td
                  colSpan=2
                  style={ReactDOMRe.Style.make(
                    ~fontSize=[@reason.preserve_braces] "1.5vh",
                    ~textAlign=[@reason.preserve_braces] "center",
                    ~whiteSpace=[@reason.preserve_braces] "nowrap",
                    ~border=[@reason.preserve_braces] "1px solid #f8f8f8",
                    ~borderCollapse=[@reason.preserve_braces] "collapse",
                    ~backgroundColor=[@reason.preserve_braces] "#f8f8f8",
                    (),
                  )}>
                  {React.string("-------------- Table Seating --------------")}
                </td>
              </tr>
              // </td>
              //   (React.string(" "))
              // >
              //   )
              //     )
              //       ()
              //       ~backgroundColor={"#f8f8f8"},
              //       ~textAlign={"center"},
              //     ReactDOMRe.Style.make(
              //   style=(
              // <td
            // ref RR examples
            {state.pointOfCompassAndPlayers
             ->Belt.Array.map(x =>
                 <tr key={x.player}>
                   <td
                     style={ReactDOMRe.Style.make(
                       // bug - borderColor single attribute not recognised
                       ~border=[@reason.preserve_braces] "1px solid #f8f8f8", // use #f8f8f8 to hide
                       ~borderCollapse=[@reason.preserve_braces] "collapse",
                       ~textAlign=[@reason.preserve_braces] "right",
                       (),
                     )}>
                     {React.string(x.player)}
                   </td>
                   <td
                     style={ReactDOMRe.Style.make(
                       // bug - borderColor single attribute not recognised
                       ~border=[@reason.preserve_braces] "1px solid #f8f8f8", // was #26653B // suspect no effect
                       ~borderCollapse=[@reason.preserve_braces] "collapse",
                       (),
                     )}>
                     <ButtonStd
                       color="#404040"
                       dispatch
                       action={
                         AssignPlayer({
                           pointOfCompass: {
                             x.pointOfCompass === "West" ? "" : "West";
                           },
                           player: x.player,
                         })
                       }
                       label="W"
                       id={"btnW" ++ x.player}
                       isActive={x.pointOfCompass == "West" ? true : false}
                     />
                     <ButtonStd
                       color="#404040"
                       dispatch
                       action={
                         AssignPlayer({
                           pointOfCompass: {
                             x.pointOfCompass === "North" ? "" : "North";
                           },
                           player: x.player,
                         })
                       }
                       label="N"
                       id={"btnN" ++ x.player}
                       isActive={x.pointOfCompass == "North" ? true : false}
                     />
                     <ButtonStd
                       color="#404040"
                       dispatch
                       action={
                         AssignPlayer({
                           pointOfCompass: {
                             x.pointOfCompass === "East" ? "" : "East";
                           },
                           player: x.player,
                         })
                       }
                       label="E"
                       id={"btnE" ++ x.player}
                       isActive={x.pointOfCompass == "East" ? true : false}
                     />
                     <ButtonStd
                       color="#404040"
                       dispatch
                       action={
                         AssignPlayer({
                           pointOfCompass: {
                             x.pointOfCompass === "South" ? "" : "South";
                           },
                           player: x.player,
                         })
                       }
                       label="S"
                       id={"btnS" ++ x.player}
                       isActive={x.pointOfCompass == "South" ? true : false}
                     />
                     <ButtonObserver
                       dispatch
                       action={
                         AssignPlayer({
                           pointOfCompass: {
                             x.pointOfCompass === "Observer" ? "" : "Observer";
                           },
                           player: x.player,
                         })
                       }
                       label="_"
                       id={"btnO" ++ x.player}
                       isActive={x.pointOfCompass == "Observer" ? true : false}
                     />
                   </td>
                 </tr>
               )
             ->React.array}
          </tbody>
        </table>
      </>;
};
