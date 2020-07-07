'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Random = require("bs-platform/lib/js/random.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");

var initialPack = [
  {
    noTrumpValue: 51,
    handOrder: 51,
    shuffleIndex: 51,
    rank: /* Ace */0,
    suit: /* Spades */0,
    fileName: "AS",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 50,
    handOrder: 50,
    shuffleIndex: 50,
    rank: /* King */1,
    suit: /* Spades */0,
    fileName: "KS",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 49,
    handOrder: 49,
    shuffleIndex: 49,
    rank: /* Queen */2,
    suit: /* Spades */0,
    fileName: "QS",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 48,
    handOrder: 48,
    shuffleIndex: 48,
    rank: /* Jack */3,
    suit: /* Spades */0,
    fileName: "JS",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 47,
    handOrder: 47,
    shuffleIndex: 47,
    rank: /* Ten */4,
    suit: /* Spades */0,
    fileName: "TS",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 46,
    handOrder: 46,
    shuffleIndex: 46,
    rank: /* Nine */5,
    suit: /* Spades */0,
    fileName: "9S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 45,
    handOrder: 45,
    shuffleIndex: 45,
    rank: /* Eight */6,
    suit: /* Spades */0,
    fileName: "8S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 44,
    handOrder: 44,
    shuffleIndex: 44,
    rank: /* Seven */7,
    suit: /* Spades */0,
    fileName: "7S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 43,
    handOrder: 43,
    shuffleIndex: 43,
    rank: /* Six */8,
    suit: /* Spades */0,
    fileName: "6S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 42,
    handOrder: 42,
    shuffleIndex: 42,
    rank: /* Five */9,
    suit: /* Spades */0,
    fileName: "5S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 41,
    handOrder: 41,
    shuffleIndex: 41,
    rank: /* Four */10,
    suit: /* Spades */0,
    fileName: "4S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 40,
    handOrder: 40,
    shuffleIndex: 40,
    rank: /* Three */11,
    suit: /* Spades */0,
    fileName: "3S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 39,
    handOrder: 39,
    shuffleIndex: 39,
    rank: /* Two */12,
    suit: /* Spades */0,
    fileName: "2S",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 38,
    handOrder: 38,
    shuffleIndex: 38,
    rank: /* Ace */0,
    suit: /* Hearts */1,
    fileName: "AH",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 37,
    handOrder: 37,
    shuffleIndex: 37,
    rank: /* King */1,
    suit: /* Hearts */1,
    fileName: "KH",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 36,
    handOrder: 36,
    shuffleIndex: 36,
    rank: /* Queen */2,
    suit: /* Hearts */1,
    fileName: "QH",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 35,
    handOrder: 35,
    shuffleIndex: 35,
    rank: /* Jack */3,
    suit: /* Hearts */1,
    fileName: "JH",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 34,
    handOrder: 34,
    shuffleIndex: 34,
    rank: /* Ten */4,
    suit: /* Hearts */1,
    fileName: "TH",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 33,
    handOrder: 33,
    shuffleIndex: 33,
    rank: /* Nine */5,
    suit: /* Hearts */1,
    fileName: "9H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 32,
    handOrder: 32,
    shuffleIndex: 32,
    rank: /* Eight */6,
    suit: /* Hearts */1,
    fileName: "8H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 31,
    handOrder: 31,
    shuffleIndex: 31,
    rank: /* Seven */7,
    suit: /* Hearts */1,
    fileName: "7H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 30,
    handOrder: 30,
    shuffleIndex: 30,
    rank: /* Six */8,
    suit: /* Hearts */1,
    fileName: "6H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 29,
    handOrder: 29,
    shuffleIndex: 29,
    rank: /* Five */9,
    suit: /* Hearts */1,
    fileName: "5H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 28,
    handOrder: 28,
    shuffleIndex: 28,
    rank: /* Four */10,
    suit: /* Hearts */1,
    fileName: "4H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 27,
    handOrder: 27,
    shuffleIndex: 27,
    rank: /* Three */11,
    suit: /* Hearts */1,
    fileName: "3H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 26,
    handOrder: 26,
    shuffleIndex: 26,
    rank: /* Two */12,
    suit: /* Hearts */1,
    fileName: "2H",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 25,
    handOrder: 12,
    shuffleIndex: 25,
    rank: /* Ace */0,
    suit: /* Diamonds */2,
    fileName: "AD",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 24,
    handOrder: 11,
    shuffleIndex: 24,
    rank: /* King */1,
    suit: /* Diamonds */2,
    fileName: "KD",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 23,
    handOrder: 10,
    shuffleIndex: 23,
    rank: /* Queen */2,
    suit: /* Diamonds */2,
    fileName: "QD",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 22,
    handOrder: 9,
    shuffleIndex: 22,
    rank: /* Jack */3,
    suit: /* Diamonds */2,
    fileName: "JD",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 21,
    handOrder: 8,
    shuffleIndex: 21,
    rank: /* Ten */4,
    suit: /* Diamonds */2,
    fileName: "TD",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 20,
    handOrder: 7,
    shuffleIndex: 20,
    rank: /* Nine */5,
    suit: /* Diamonds */2,
    fileName: "9D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 19,
    handOrder: 6,
    shuffleIndex: 19,
    rank: /* Eight */6,
    suit: /* Diamonds */2,
    fileName: "8D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 18,
    handOrder: 5,
    shuffleIndex: 18,
    rank: /* Seven */7,
    suit: /* Diamonds */2,
    fileName: "7D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 17,
    handOrder: 4,
    shuffleIndex: 17,
    rank: /* Six */8,
    suit: /* Diamonds */2,
    fileName: "6D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 16,
    handOrder: 3,
    shuffleIndex: 16,
    rank: /* Five */9,
    suit: /* Diamonds */2,
    fileName: "5D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 15,
    handOrder: 2,
    shuffleIndex: 15,
    rank: /* Four */10,
    suit: /* Diamonds */2,
    fileName: "4D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 14,
    handOrder: 1,
    shuffleIndex: 14,
    rank: /* Three */11,
    suit: /* Diamonds */2,
    fileName: "3D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 13,
    handOrder: 0,
    shuffleIndex: 13,
    rank: /* Two */12,
    suit: /* Diamonds */2,
    fileName: "2D",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 12,
    handOrder: 25,
    shuffleIndex: 12,
    rank: /* Ace */0,
    suit: /* Clubs */3,
    fileName: "AC",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 11,
    handOrder: 24,
    shuffleIndex: 11,
    rank: /* King */1,
    suit: /* Clubs */3,
    fileName: "KC",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 10,
    handOrder: 23,
    shuffleIndex: 10,
    rank: /* Queen */2,
    suit: /* Clubs */3,
    fileName: "QC",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 9,
    handOrder: 22,
    shuffleIndex: 9,
    rank: /* Jack */3,
    suit: /* Clubs */3,
    fileName: "JC",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 8,
    handOrder: 21,
    shuffleIndex: 8,
    rank: /* Ten */4,
    suit: /* Clubs */3,
    fileName: "TC",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 7,
    handOrder: 20,
    shuffleIndex: 7,
    rank: /* Nine */5,
    suit: /* Clubs */3,
    fileName: "9C",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 6,
    handOrder: 19,
    shuffleIndex: 6,
    rank: /* Eight */6,
    suit: /* Clubs */3,
    fileName: "8C",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 5,
    handOrder: 18,
    shuffleIndex: 5,
    rank: /* Seven */7,
    suit: /* Clubs */3,
    fileName: "7C",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 4,
    handOrder: 17,
    shuffleIndex: 4,
    rank: /* Six */8,
    suit: /* Clubs */3,
    fileName: "6C",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 3,
    handOrder: 16,
    shuffleIndex: 3,
    rank: /* Five */9,
    suit: /* Clubs */3,
    fileName: "5C",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 2,
    handOrder: 15,
    shuffleIndex: 2,
    rank: /* Four */10,
    suit: /* Clubs */3,
    fileName: "4C",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 1,
    handOrder: 14,
    shuffleIndex: 1,
    rank: /* Three */11,
    suit: /* Clubs */3,
    fileName: "3C",
    lifecycle: /* Dealer */0
  },
  {
    noTrumpValue: 0,
    handOrder: 13,
    shuffleIndex: 0,
    rank: /* Two */12,
    suit: /* Clubs */3,
    fileName: "2C",
    lifecycle: /* Dealer */0
  }
];

function impureGetTimeBasedSeedUpTo60k(param) {
  var now = new Date();
  return now.getSeconds() * 1000.0 + now.getMilliseconds() | 0;
}

var myArrayOfIndices = [
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20,
  21,
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
  31,
  32,
  33,
  34,
  35,
  36,
  37,
  38,
  39,
  40,
  41,
  42,
  43,
  44,
  45,
  46,
  47,
  48,
  49,
  50,
  51
];

function shuffleArrayInPlace(arr, seed) {
  Random.init(seed);
  for(var n = arr.length - 1 | 0; n >= 1; --n){
    var k = Random.$$int(n + 1 | 0);
    var temp = Caml_array.caml_array_get(arr, n);
    Caml_array.caml_array_set(arr, n, Caml_array.caml_array_get(arr, k));
    Caml_array.caml_array_set(arr, k, temp);
  }
  
}

function getShuffledPack(param) {
  shuffleArrayInPlace(myArrayOfIndices, impureGetTimeBasedSeedUpTo60k(undefined));
  return $$Array.map((function (card) {
                return {
                        noTrumpValue: card.noTrumpValue,
                        handOrder: card.handOrder,
                        shuffleIndex: Caml_array.caml_array_get(myArrayOfIndices, card.noTrumpValue),
                        rank: card.rank,
                        suit: card.suit,
                        fileName: card.fileName,
                        lifecycle: /* Hand */1
                      };
              }), initialPack);
}

function getRandomCompassPoint(seed) {
  Random.init(seed);
  var n = Random.$$int(4);
  switch (n) {
    case 0 :
        return "North";
    case 1 :
        return "East";
    case 2 :
        return "South";
    default:
      return "West";
  }
}

function getNextPointOfCompass(poc) {
  if (poc === undefined) {
    return getRandomCompassPoint(impureGetTimeBasedSeedUpTo60k(undefined));
  }
  switch (poc) {
    case "East" :
        return "South";
    case "North" :
        return "East";
    case "South" :
        return "West";
    case "West" :
        return "North";
    default:
      return "East";
  }
}

var initialPoc = getNextPointOfCompass(undefined);

function pocAsString(poc) {
  if (poc === undefined) {
    return "";
  }
  switch (poc) {
    case "East" :
        return "East";
    case "North" :
        return "North";
    case "South" :
        return "South";
    case "West" :
        return "West";
    default:
      return "East";
  }
}

function optionIntAsString(level) {
  if (level === undefined) {
    return "";
  }
  switch (level) {
    case 1 :
        return "1";
    case 2 :
        return "2";
    case 3 :
        return "3";
    case 4 :
        return "4";
    case 5 :
        return "5";
    case 6 :
        return "6";
    case 7 :
        return "7";
    case 8 :
        return "8";
    case 9 :
        return "9";
    case 10 :
        return "10";
    case 11 :
        return "11";
    case 12 :
        return "12";
    case 13 :
        return "13";
    default:
      return "X";
  }
}

function getNextActivePointOfCompass(poc) {
  if (poc === undefined) {
    return "East";
  }
  switch (poc) {
    case "East" :
        return "South";
    case "North" :
        return "East";
    case "South" :
        return "West";
    case "West" :
        return "North";
    default:
      return "East";
  }
}

function getSuitAsOptionString(suit) {
  switch (suit) {
    case /* Spades */0 :
        return "Spades";
    case /* Hearts */1 :
        return "Hearts";
    case /* Diamonds */2 :
        return "Diamonds";
    case /* Clubs */3 :
        return "Clubs";
    
  }
}

var initialHandVisible = {
  north: true,
  east: true,
  south: true,
  west: true
};

exports.initialPack = initialPack;
exports.initialHandVisible = initialHandVisible;
exports.getShuffledPack = getShuffledPack;
exports.impureGetTimeBasedSeedUpTo60k = impureGetTimeBasedSeedUpTo60k;
exports.getNextPointOfCompass = getNextPointOfCompass;
exports.getRandomCompassPoint = getRandomCompassPoint;
exports.initialPoc = initialPoc;
exports.pocAsString = pocAsString;
exports.optionIntAsString = optionIntAsString;
exports.getNextActivePointOfCompass = getNextActivePointOfCompass;
exports.getSuitAsOptionString = getSuitAsOptionString;
/* initialPoc Not a pure module */
