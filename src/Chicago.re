// type defs for bidding cycle
type bid = {
  contractLevel: option(int),
  contractSuit: option(string),
  contractPointOfCompass: option(string),
  isDoubled: bool,
  isRedoubled: bool,
  isPass: bool
};

type bids = list(bid);


// type defs for score sheet
type chicagoScoreSheetRecord = {
  vulnerable: string,               // "None", "Dealer", "Dealer", "All" modulo 4
  contractLevel: option(int),       // None | Some (1,2,3,4,5,6,7)
  contractSuit: option(string),     // None | Some("Clubs", "Diamonds", "Hearts", "Spades", "NoTrumps")
  contractDeclarer: option(string), // None | Some("North", "East", "South", "West")
  totalTricks: option(int),         // None | 0 thru 13
  scoreNorthSouth: option(int),     // calculated using Chicago.getScore if Declarer "North" or "South"
  scoreWestEast: option(int)        // calculated using Chicago.getScore if Declarer "West" or "East"
};

type chicagoScoreSheet = list(chicagoScoreSheetRecord);

// values for Chicago Score Sheet

let initialChicagoScoreSheet: chicagoScoreSheet = [
  // first row created at end of bidding?
  // {
  //   vulnerable: "None",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "All",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "None",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "All",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "None",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "All",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "None",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "All",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "None",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "Dealer",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // },
  // {
  //   vulnerable: "All",
  //   contractLevel: None,
  //   contractSuit: None,
  //   contractDeclarer: None,
  //   totalTricks: None,
  //   scoreNorthSouth: None,
  //   scoreWestEast: None
  // }
];


// type defs for scoring lookup table
type denomination =
  | Minor
  | Major
  | NoTrumps
;

type scoreRecord = {
  level : int,
  denomination: denomination,
  tricksTotal: int,
  isVulnerable: bool,
  isDoubled: bool,
  isRedoubled: bool,
  score: int
};

// values for scoring lookup table
// we want to access this structure by a composite key
// Reason ml list is best because it supports filter and find
// whereas array does not
// NO! the list causes a webpack stack overflow,
// so use an array and convert it as needed to a list which can be filtered
let scoreTable: array(scoreRecord)  =
[|
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 70
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 90
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 80
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 140
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 230
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 260
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 90
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 120
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 180
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 210
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 240
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 270
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 90
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 140
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 230
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 260
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 120
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 180
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 210
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 240
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 270
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 140
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 230
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 260
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 430
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 460
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 490
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 520
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 420
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 450
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 480
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 510
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 430
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 460
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 490
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 520
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 420
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 440
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 450
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 480
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 510
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 460
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 490
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 520
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 920
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 940
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 980
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 1010
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 990
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 1020
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -650
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 1440
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -650
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 1510
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -650
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -550
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -450
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -350
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -250
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -150
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: -50
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: false,
   isRedoubled: false,
   score: 1520
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 70
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 90
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 80
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 140
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 230
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 260
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 90
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 120
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 180
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 210
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 240
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 270
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 90
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 140
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 230
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 260
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 120
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 180
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 210
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 240
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 270
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 110
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 140
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 230
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 260
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 130
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 150
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 170
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 190
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 630
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 660
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 690
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 720
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 620
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 650
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 680
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 710
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 630
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 660
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 690
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 720
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 620
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 640
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 650
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 680
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 710
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 660
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 690
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 720
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 1370
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 1390
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 1430
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 1460
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 1440
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 1470
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1300
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 2140
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1300
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 2210
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1300
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -1000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -900
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -700
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: false,
   isRedoubled: false,
   score: 2220
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 140
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 240
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 340
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 440
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 540
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 640
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 740
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 160
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 260
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 360
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 460
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 560
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 660
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 760
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 180
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 280
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 380
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 480
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 580
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 680
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 780
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 180
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 280
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 380
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 480
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 580
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 680
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 470
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 570
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 670
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 770
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 870
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 970
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 490
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 590
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 690
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 790
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 890
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 990
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 470
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 570
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 670
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 770
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 870
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 530
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 630
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 730
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 830
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 930
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 510
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 610
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 710
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 810
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 550
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 650
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 750
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 850
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 950
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 590
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 690
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 790
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 890
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 610
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 710
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 810
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 910
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 550
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 650
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 750
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 650
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 750
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 850
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 670
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 770
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 870
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1090
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1190
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1210
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1310
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1230
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1330
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1630
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1770
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -300
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: -100
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: false,
   score: 1790
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 140
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 340
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 540
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 740
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 940
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1140
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1340
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 160
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 360
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 560
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 760
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 960
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1160
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1360
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 180
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 380
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 580
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 780
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 980
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1180
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1380
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 180
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 380
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 580
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 780
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 980
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1180
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 670
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 870
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1070
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1270
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1470
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1670
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 690
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 890
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1090
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1290
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1490
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1690
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 670
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 870
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1070
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1270
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1470
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 730
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 930
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1130
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1330
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1530
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 710
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 910
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1110
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1310
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 750
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 950
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1150
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1350
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1550
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 790
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 990
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1190
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1390
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 810
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1010
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1210
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1410
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 750
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 950
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1150
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 850
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1050
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1250
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 870
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1070
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1270
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1540
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1740
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1660
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1860
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1680
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 1880
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 2330
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 2470
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3500
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -3200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2900
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2300
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -2000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1700
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -1100
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -500
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: -200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: false,
   score: 2490
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 230
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 430
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 630
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 830
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1030
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1230
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1430
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 520
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 720
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 920
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1120
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1320
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1520
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1720
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 560
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 760
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 960
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1160
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1360
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1560
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1760
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 560
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 760
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 960
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1160
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1360
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1560
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 640
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 840
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1040
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1240
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1440
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1640
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 680
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 880
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1080
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1280
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1480
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1680
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 640
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 840
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1040
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1240
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1440
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 760
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 960
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1160
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1360
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1560
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 720
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 920
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1120
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1320
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 800
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 880
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1080
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1280
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1480
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 920
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1120
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1320
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1520
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1040
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1240
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1440
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1380
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1580
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1620
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1820
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1660
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1860
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 1960
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 2240
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: -200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: false,
   isDoubled: true,
   isRedoubled: true,
   score: 2280
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 230
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 630
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1030
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1430
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1830
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2230
 },
 {
   level: 1,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2630
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 720
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1120
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1520
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1920
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2320
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2720
 },
 {
   level: 1,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 3120
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 760
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1160
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1560
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1960
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2360
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2760
 },
 {
   level: 1,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 3160
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 760
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1160
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1560
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1960
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2360
 },
 {
   level: 2,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2760
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 840
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1240
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1640
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2040
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2440
 },
 {
   level: 2,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2840
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 880
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1280
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1680
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2080
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2480
 },
 {
   level: 2,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2880
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 840
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1240
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1640
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2040
 },
 {
   level: 3,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2440
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 960
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1360
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1760
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2160
 },
 {
   level: 3,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2560
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 920
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1320
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1720
 },
 {
   level: 4,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2120
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1000
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1400
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1800
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2200
 },
 {
   level: 3,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1080
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1480
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1880
 },
 {
   level: 4,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2280
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1120
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1520
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1920
 },
 {
   level: 4,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2320
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1000
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1400
 },
 {
   level: 5,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1200
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1600
 },
 {
   level: 5,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1240
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1640
 },
 {
   level: 5,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2040
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 1830
 },
 {
   level: 6,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2230
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2070
 },
 {
   level: 6,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2470
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2110
 },
 {
   level: 6,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2510
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 7,
   denomination: Minor,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2660
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 7,
   denomination: Major,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2940
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 0,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 1,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -7000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 2,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -6400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 3,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 4,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -5200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 5,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 6,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -4000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 7,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -3400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 8,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2800
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 9,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -2200
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 10,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1600
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 11,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -1000
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 12,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: -400
 },
 {
   level: 7,
   denomination: NoTrumps,
   tricksTotal: 13,
   isVulnerable: true,
   isDoubled: true,
   isRedoubled: true,
   score: 2980
 }
|];

let getScore = (
  ~level, ~denomination, ~tricksTotal, ~isVulnerable,
  ~isDoubled, ~isRedoubled) => {
  let record = List.find(x => {
    x.level === level &&
    x.denomination === denomination &&
    x.tricksTotal === tricksTotal &&
    x.isVulnerable === isVulnerable &&
    x.isDoubled == isDoubled &&
    x.isRedoubled === isRedoubled
  },
  Array.to_list(scoreTable)
  )
  record.score;
};

