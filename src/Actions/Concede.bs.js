'use strict';


function doConcede(state) {
  return state;
}

function execute(state) {
  var bln = (window.confirm('Are you sure you want to CONCEDE remaining tricks to partnership with highest value cards?'));
  if (bln) {
    console.log("do concede action");
    return state;
  } else {
    console.log("abort concede action");
    return state;
  }
}

exports.doConcede = doConcede;
exports.execute = execute;
/* No side effect */
