// original was playingCardRank
// had extra value NoRank - code smell
type rank =
  | Ace
  | King
  | Queen
  | Jack
  | Ten
  | Nine
  | Eight
  | Seven
  | Six
  | Five
  | Four
  | Three
  | Two;

// original was playingCardSuit
// also had dummy suit NoSuit - code smell
type suit =
  | Spades
  | Hearts
  | Diamonds
  | Clubs;

type compassPoint =
  | North
  | East
  | South
  | West;

type pointOfCompassAndPlayer = {
  pointOfCompass: string,
  player: string,
};

// all cards start in the dealers hand
// once shuffled they are in a hand defined by compass
// then they are thrown to discard pile
// winning hand takes the trick
type lifecycle =
  | Dealer
  | Hand
  | Discard
  | Trick;

// define an individual card as a record type, rather than tuple
// unique identifier is the noTrumpValue
type card = {
  noTrumpValue: int,
  handOrder: int,
  shuffleIndex: int,
  rank,
  suit,
  fileName: string,
  lifecycle,
};

//type pack = list(card);
type pack = array(card);

type handVisible = {
  north: bool,
  east: bool,
  south: bool,
  west: bool,
};

type transition = {
  northStartY: float,
  eastStartX: float,
  southStartY: float,
  westStartX: float,
  northEndY: float,
  eastEndX: float,
  southEndY: float,
  westEndX: float,
  northStartX: float,
  eastStartY: float,
  southStartX: float,
  westStartY: float,
  northStartXInv: float,
  eastStartYInv: float,
  southStartXInv: float,
  westStartYInv: float,
  northEndX: float,
  eastEndY: float,
  southEndX: float,
  westEndY: float,
};

/** VALUE DEFINITIONS */

//let myArrayOfIndices: array(int);

let initialPack: pack;

let initialHandVisible: handVisible;

let getShuffledPack: unit => pack;

//let impureGetTimeBasedSeedUpTo60k: unit => int;

//let shuffleArrayInPlace: (array('a), int) => unit;

let impureGetTimeBasedSeedUpTo60k: unit => int;

let getNextPointOfCompass: option(string) => string;

let getRandomCompassPoint: int => string;

let initialPoc: string;

let pocAsString: option(string) => string;

//let partnerPocAsString: (option(string)) => string;

let optionIntAsString: option(int) => string;

let getNextActivePointOfCompass: option(string) => option(string);

let getSuitAsOptionString: suit => option(string);

let optionIntAsInt: option(int) => int;
