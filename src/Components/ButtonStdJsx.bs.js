'use strict';

var React = require("react");

function ButtonStdJsx(Props) {
  var label = Props.label;
  var id = Props.id;
  var onClick = Props.onClick;
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: "#FFFFFF",
                    border: "1px solid #26653B",
                    color: "#26653B",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.5vh",
                    margin: "0vh",
                    borderRadius: "5px"
                  },
                  onClick: onClick
                }, label));
}

var make = ButtonStdJsx;

exports.make = make;
/* react Not a pure module */
