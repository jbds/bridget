
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
  | Two
;

// original was playingCardSuit
// also had dummy suit NoSuit - code smell
type suit = 
  | Spades
  | Hearts
  | Diamonds
  | Clubs
;

type compassPoint =
  | North
  | East
  | South
  | West
;

type pointOfCompassAndPlayer = {
  pointOfCompass: string,
  player: string
};

// all cards start in the dealers hand
// once shuffled they are in a hand defined by compass
// then they are thrown to discard pile
// winning hand takes the trick
type lifecycle =
  | Dealer
  | Hand
  | Discard
  | Trick
;


// define an individual card as a record type, rather than tuple
// unique identifier is the noTrumpValue
type card = {
  noTrumpValue: int, 
  handOrder: int,
  shuffleIndex: int,
  rank: rank,
  suit: suit, 
  fileName: string,
  lifecycle: lifecycle
};

//type pack = list(card);
type pack = array(card);


type handVisible = {north: bool, east: bool, south: bool, west: bool};

// this is the game state that we will share amongst all users who are registered at the server
// it is a single record which will be passed to and broadcast from the server
// type state = {
//   pack: pack,
//   handVisible: handVisible,
//   dealer: option(compassPoint),
//   //cardsDealtCount: int,
//   pointOfCompassAndPlayers: array(pointOfCompassAndPlayer),
//   randomInt: int
// };



/** VALUE DEFINITIONS */

//let myArrayOfIndices: array(int);

let initialPack: pack;

let initialHandVisible: handVisible;

let getShuffledPack: unit => pack;

//let impureGetTimeBasedSeedUpTo60k: unit => int;

//let shuffleArrayInPlace: (array('a), int) => unit;

let impureGetTimeBasedSeedUpTo60k: unit => int;

let getNextPointOfCompass: (option(string)) => string;

let getRandomCompassPoint: int => string;

let initialPoc: string;

let pocAsString: (option(string)) => string;

//let partnerPocAsString: (option(string)) => string;

let optionIntAsString: (option(int)) => string;

let getNextActivePointOfCompass: (option(string)) => option(string);

let getSuitAsOptionString: (suit) => option(string);
