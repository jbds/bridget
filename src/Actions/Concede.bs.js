'use strict';

var Belt_Array = require("bs-platform/lib/js/belt_Array.js");

function doConcede(state) {
  var remainingCardsNS = Belt_Array.keep(state.pack, (function (x) {
          if (x.lifecycle === /* Hand */1) {
            if (x.shuffleIndex >= 0 && x.shuffleIndex <= 12) {
              return true;
            } else if (x.shuffleIndex >= 26) {
              return x.shuffleIndex <= 38;
            } else {
              return false;
            }
          } else {
            return false;
          }
        }));
  console.log(remainingCardsNS);
  var valueCardsArrayNS = Belt_Array.map(remainingCardsNS, (function (x) {
          return x.noTrumpValue;
        }));
  console.log(valueCardsArrayNS);
  var totalValueCardsNS = Belt_Array.reduce(valueCardsArrayNS, 0, (function (a, b) {
          return a + b | 0;
        }));
  console.log(totalValueCardsNS);
  Belt_Array.keep(state.pack, (function (x) {
          if (x.lifecycle === /* Hand */1) {
            if (x.shuffleIndex >= 13 && x.shuffleIndex <= 25) {
              return true;
            } else if (x.shuffleIndex >= 39) {
              return x.shuffleIndex <= 51;
            } else {
              return false;
            }
          } else {
            return false;
          }
        }));
  return state;
}

function execute(state) {
  var bln = (window.confirm('Are you sure you want to CONCEDE remaining tricks to partnership with highest value cards?'));
  if (bln) {
    console.log("do concede action");
    return doConcede(state);
  } else {
    console.log("abort concede action");
    return state;
  }
}

exports.doConcede = doConcede;
exports.execute = execute;
/* No side effect */
