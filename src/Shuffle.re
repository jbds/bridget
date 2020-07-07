// TYPE DEFINITIONS *************************

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
  // consumed by js code, so use string rather than compassPoint
  pointOfCompass: string,
  player: string
};

// all cards start in the dealers hand
// once shuffled they are in a hand defined by compass
// then they are thrown to discard pile
// every 4th discard, discards move to trick
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
//   randomInt: int,
//   chicagoScoreSheet: array(Chicago.chicagoScoreSheetRecord)
// };

// keep for later move!
// not needed until after the bidding
// type gameDenomination =
//   | No_Trumps
//   | Suit(suit)


// VALUE DEFINITIONS

let initialPack = [|
  {noTrumpValue: 51, handOrder: 51, shuffleIndex: 51, rank: Ace, suit: Spades, fileName: "AS", lifecycle: Dealer},
  {noTrumpValue: 50, handOrder: 50, shuffleIndex: 50, rank: King, suit: Spades, fileName: "KS", lifecycle: Dealer},
  {noTrumpValue: 49, handOrder: 49, shuffleIndex: 49, rank: Queen, suit: Spades, fileName: "QS", lifecycle: Dealer},
  {noTrumpValue: 48, handOrder: 48, shuffleIndex: 48, rank: Jack, suit: Spades, fileName: "JS", lifecycle: Dealer},
  {noTrumpValue: 47, handOrder: 47, shuffleIndex: 47, rank: Ten, suit: Spades, fileName: "TS", lifecycle: Dealer},
  {noTrumpValue: 46, handOrder: 46, shuffleIndex: 46, rank: Nine, suit: Spades, fileName: "9S", lifecycle: Dealer},
  {noTrumpValue: 45, handOrder: 45, shuffleIndex: 45, rank: Eight, suit: Spades, fileName: "8S", lifecycle: Dealer},
  {noTrumpValue: 44, handOrder: 44, shuffleIndex: 44, rank: Seven, suit: Spades, fileName: "7S", lifecycle: Dealer},
  {noTrumpValue: 43, handOrder: 43, shuffleIndex: 43, rank: Six, suit: Spades, fileName: "6S", lifecycle: Dealer},
  {noTrumpValue: 42, handOrder: 42, shuffleIndex: 42, rank: Five, suit: Spades, fileName: "5S", lifecycle: Dealer},
  {noTrumpValue: 41, handOrder: 41, shuffleIndex: 41, rank: Four, suit: Spades, fileName: "4S", lifecycle: Dealer},
  {noTrumpValue: 40, handOrder: 40, shuffleIndex: 40, rank: Three, suit: Spades, fileName: "3S", lifecycle: Dealer},
  {noTrumpValue: 39, handOrder: 39, shuffleIndex: 39, rank: Two, suit: Spades, fileName: "2S", lifecycle: Dealer},
  {noTrumpValue: 38, handOrder: 38, shuffleIndex: 38, rank: Ace, suit: Hearts, fileName: "AH", lifecycle: Dealer},
  {noTrumpValue: 37, handOrder: 37, shuffleIndex: 37, rank: King, suit: Hearts, fileName: "KH", lifecycle: Dealer},
  {noTrumpValue: 36, handOrder: 36, shuffleIndex: 36, rank: Queen, suit: Hearts, fileName: "QH", lifecycle: Dealer},
  {noTrumpValue: 35, handOrder: 35, shuffleIndex: 35, rank: Jack, suit: Hearts, fileName: "JH", lifecycle: Dealer},
  {noTrumpValue: 34, handOrder: 34, shuffleIndex: 34, rank: Ten, suit: Hearts, fileName: "TH", lifecycle: Dealer},
  {noTrumpValue: 33, handOrder: 33, shuffleIndex: 33, rank: Nine, suit: Hearts, fileName: "9H", lifecycle: Dealer},
  {noTrumpValue: 32, handOrder: 32, shuffleIndex: 32, rank: Eight, suit: Hearts, fileName: "8H", lifecycle: Dealer},
  {noTrumpValue: 31, handOrder: 31, shuffleIndex: 31, rank: Seven, suit: Hearts, fileName: "7H", lifecycle: Dealer},
  {noTrumpValue: 30, handOrder: 30, shuffleIndex: 30, rank: Six, suit: Hearts, fileName: "6H", lifecycle: Dealer},
  {noTrumpValue: 29, handOrder: 29, shuffleIndex: 29, rank: Five, suit: Hearts, fileName: "5H", lifecycle: Dealer},
  {noTrumpValue: 28, handOrder: 28, shuffleIndex: 28, rank: Four, suit: Hearts, fileName: "4H", lifecycle: Dealer},
  {noTrumpValue: 27, handOrder: 27, shuffleIndex: 27, rank: Three, suit: Hearts, fileName: "3H", lifecycle: Dealer},
  {noTrumpValue: 26, handOrder: 26, shuffleIndex: 26, rank: Two, suit: Hearts, fileName: "2H", lifecycle: Dealer},
  {noTrumpValue: 25, handOrder: 12, shuffleIndex: 25, rank: Ace, suit: Diamonds, fileName: "AD", lifecycle: Dealer},
  {noTrumpValue: 24, handOrder: 11, shuffleIndex: 24, rank: King, suit: Diamonds, fileName: "KD", lifecycle: Dealer},
  {noTrumpValue: 23, handOrder: 10, shuffleIndex: 23, rank: Queen, suit: Diamonds, fileName: "QD", lifecycle: Dealer},
  {noTrumpValue: 22, handOrder: 9, shuffleIndex: 22, rank: Jack, suit: Diamonds, fileName: "JD", lifecycle: Dealer},
  {noTrumpValue: 21, handOrder: 8, shuffleIndex: 21, rank: Ten, suit: Diamonds, fileName: "TD", lifecycle: Dealer},
  {noTrumpValue: 20, handOrder: 7, shuffleIndex: 20, rank: Nine, suit: Diamonds, fileName: "9D", lifecycle: Dealer},
  {noTrumpValue: 19, handOrder: 6, shuffleIndex: 19, rank: Eight, suit: Diamonds, fileName: "8D", lifecycle: Dealer},
  {noTrumpValue: 18, handOrder: 5, shuffleIndex: 18, rank: Seven, suit: Diamonds, fileName: "7D", lifecycle: Dealer},
  {noTrumpValue: 17, handOrder: 4, shuffleIndex: 17, rank: Six, suit: Diamonds, fileName: "6D", lifecycle: Dealer},
  {noTrumpValue: 16, handOrder: 3, shuffleIndex: 16, rank: Five, suit: Diamonds, fileName: "5D", lifecycle: Dealer},
  {noTrumpValue: 15, handOrder: 2, shuffleIndex: 15, rank: Four, suit: Diamonds, fileName: "4D", lifecycle: Dealer},
  {noTrumpValue: 14, handOrder: 1, shuffleIndex: 14, rank: Three, suit: Diamonds, fileName: "3D", lifecycle: Dealer},
  {noTrumpValue: 13, handOrder: 0, shuffleIndex: 13, rank: Two, suit: Diamonds, fileName: "2D", lifecycle: Dealer},
  {noTrumpValue: 12, handOrder: 25, shuffleIndex: 12, rank: Ace, suit: Clubs, fileName: "AC", lifecycle: Dealer},
  {noTrumpValue: 11, handOrder: 24, shuffleIndex: 11, rank: King, suit: Clubs, fileName: "KC", lifecycle: Dealer},
  {noTrumpValue: 10, handOrder: 23, shuffleIndex: 10, rank: Queen, suit: Clubs, fileName: "QC", lifecycle: Dealer},
  {noTrumpValue: 9, handOrder: 22, shuffleIndex: 9, rank: Jack, suit: Clubs, fileName: "JC", lifecycle: Dealer},
  {noTrumpValue: 8, handOrder: 21, shuffleIndex: 8, rank: Ten, suit: Clubs, fileName: "TC", lifecycle: Dealer},
  {noTrumpValue: 7, handOrder: 20, shuffleIndex: 7, rank: Nine, suit: Clubs, fileName: "9C", lifecycle: Dealer},
  {noTrumpValue: 6, handOrder: 19, shuffleIndex: 6, rank: Eight, suit: Clubs, fileName: "8C", lifecycle: Dealer},
  {noTrumpValue: 5, handOrder: 18, shuffleIndex: 5, rank: Seven, suit: Clubs, fileName: "7C", lifecycle: Dealer},
  {noTrumpValue: 4, handOrder: 17, shuffleIndex: 4, rank: Six, suit: Clubs, fileName: "6C", lifecycle: Dealer},
  {noTrumpValue: 3, handOrder: 16, shuffleIndex: 3, rank: Five, suit: Clubs, fileName: "5C", lifecycle: Dealer},
  {noTrumpValue: 2, handOrder: 15, shuffleIndex: 2, rank: Four, suit: Clubs, fileName: "4C", lifecycle: Dealer},
  {noTrumpValue: 1, handOrder: 14, shuffleIndex: 1, rank: Three, suit: Clubs, fileName: "3C", lifecycle: Dealer},
  {noTrumpValue: 0, handOrder: 13, shuffleIndex: 0, rank: Two, suit: Clubs, fileName: "2C", lifecycle: Dealer},
|];

let initialHandVisible = {north: true, east: true, south: true, west: true};

//let initialPointOfCompassAndPlayers = [|
  // {pointOfCompass: "North", player: "1?" },
  // {pointOfCompass: "South", player: "2?"},
  // {pointOfCompass: "West", player: "3?"},
  // {pointOfCompass: "East", player: "4?"},
  // {pointOfCompass: "", player: "5?"},
  // {pointOfCompass: "", player: "6?"}
//|];


let impureGetTimeBasedSeedUpTo60k = () => {
  let now = Js.Date.make();
  int_of_float((Js.Date.getSeconds(now) *. 1000.0) +. Js.Date.getMilliseconds(now));
};

let myArrayOfIndices = [|
  0,1,2,3,4,5,6,7,8,9,
  10,11,12,13,14,15,16,17,18,19,
  20,21,22,23,24,25,26,27,28,29,
  30,31,32,33,34,35,36,37,38,39,
  40,41,42,43,44,45,46,47,48,49,
  50,51
|];

/* Fisher–Yates shuffle */
/* polymorphic function */
let shuffleArrayInPlace = (arr, seed) => {
  Random.init(seed);
  for (n in Array.length(arr) - 1 downto 1) {
    let k = Random.int(n + 1);
    let temp = arr[n];
    arr[n] = arr[k];
    arr[k] = temp;
  };
};

let getShuffledPack = () => {
  // IMPURE!
  let () = shuffleArrayInPlace(myArrayOfIndices, impureGetTimeBasedSeedUpTo60k());
  // randomize the shuffleIndex to return the "shuffled" pack, and move lifecycle to Hand
  let shuffledPack = Array.map(card => {...card, shuffleIndex: myArrayOfIndices[card.noTrumpValue], lifecycle: Hand}, initialPack);
  // {
  //   pack: shuffledPack,
  //   handVisible: initialHandVisible,
  //   //dealer: None,
  //   //cardsDealtCount: 0,
  //   pointOfCompassAndPlayers: initialPointOfCompassAndPlayers,
  //   randomInt: impureGetTimeBasedSeedUpTo60k()
  // }
  shuffledPack;
}

let getRandomCompassPoint = (seed) => {
  Random.init(seed);
  let n = Random.int(4);
  switch (n) {
    | 0 => "North"
    | 1 => "East"
    | 2 => "South"
    | _ => "West"
  }
}

let getNextPointOfCompass = (poc) => {
  switch (poc) {
    | None => {
      // used on New Game only
      getRandomCompassPoint(impureGetTimeBasedSeedUpTo60k());
    }
    | Some("North") => "East"
    | Some("East") => "South"
    | Some("South") => "West"
    | Some("West") => "North"
    | _ => "East"
  }
};

// added later
let initialPoc = getNextPointOfCompass(None);

let pocAsString = (poc) => {
  switch (poc) {
    | None => ""
    | Some("North") => "North"
    | Some("East") => "East"
    | Some("South") => "South"
    | Some("West") => "West"
    | _ => "East"
  }
};

// added for finding declarer
// let partnerPocAsString = (poc) => {
//   switch (poc) {
//     | None => "Error"
//     | Some("North") => "South"
//     | Some("South") => "North"
//     | Some("West") => "East"
//     | Some("East") => "West"
//     | _ => "Error"
//   }
// };

let optionIntAsString = (level) => {
  switch (level) {
    | None => ""
    | Some(1) => "1"
    | Some(2) => "2"
    | Some(3) => "3"
    | Some(4) => "4"
    | Some(5) => "5"
    | Some(6) => "6"
    | Some(7) => "7"
    | Some(8) => "8"
    | Some(9) => "9"
    | Some(10) => "10"
    | Some(11) => "11"
    | Some(12) => "12"
    | Some(13) => "13"
    | _ => "X"
  }
};

let getNextActivePointOfCompass = (poc) => {
  switch (poc) {
    | Some("North") => Some("East")
    | Some("East") => Some("South")
    | Some("South") => Some("West")
    | Some("West") => Some("North")
    | _ => Some("East")
  }
};

let getSuitAsOptionString = (suit: suit) => {
  switch (suit) {
    | Spades => Some("Spades")
    | Hearts => Some("Hearts")
    | Diamonds => Some("Diamonds")
    | Clubs => Some("Clubs")
  }
}


