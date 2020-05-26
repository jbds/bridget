/** TYPE DEFINITIONS */

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

// all cards start in the dealers hand
// once shuffled they are in a hand defined by compass
// then they are thrown to discard pile
// winning hand takes the trick
type lifecycle =
  | Dealer
  | Hand(compassPoint)
  | Discard
  | Trick(compassPoint)
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
type state = {
  pack: pack,
  handVisible: handVisible,
  dealer: option(compassPoint),
  cardsDealtCount: int,
};



/** VALUE DEFINITIONS */

//let myArrayOfIndices: array(int);

let initialHandVisible: handVisible;

let shufflePack: unit => state;

//let impureGetTimeBasedSeedUpTo60k: unit => int;

//let shuffleArrayInPlace: (array('a), int) => unit;
