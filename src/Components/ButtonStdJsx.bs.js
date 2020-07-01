'use strict';

var React = require("react");

function ButtonStdJsx(Props) {
  var label = Props.label;
  var id = Props.id;
  var onClick = Props.onClick;
  var isVisibleOpt = Props.isVisible;
  var isVisible = isVisibleOpt !== undefined ? isVisibleOpt : true;
  return React.createElement(React.Fragment, undefined, React.createElement("button", {
                  id: id,
                  style: {
                    backgroundColor: "#FFFFFF",
                    border: "1px solid #26653B",
                    color: "#26653B",
                    display: isVisible ? "inline" : "none",
                    fontFamily: "Trebuchet MS",
                    fontSize: "2.0vh",
                    height: "5.0vh",
                    margin: "auto",
                    borderRadius: "5px"
                  },
                  onClick: onClick
                }, label));
}

var make = ButtonStdJsx;

exports.make = make;
/* react Not a pure module */
