type action =
  | Shuffle
  //| DealerChange (string)
  | Flip (Shuffle.compassPoint)
  // | HideAllCards
  // | ShowAllCards
  // | Deal 
  | Discard
  | Sync
;

// force to type Shuffle.state
let initialState: Shuffle.state = {
    pack: Shuffle.initialPack,
    handVisible: Shuffle.initialHandVisible,
    //dealer: None,
    //cardsDealtCount: 0,
    pointOfCompassAndPlayers: [||]
};

let reducer = (state: Shuffle.state, action) => {
    switch action {
      | Shuffle => {
        // Shuffle.rei is helpful here
        // returns an entirely new state, no need to use existing state passed in
        let result = Shuffle.shufflePack();
        //Js.log(result);
        result;

      }
      // | DealerChange (shortLoc) => {
      //   switch (shortLoc) {
      //     | "N" => {...state, dealer: Some(North)}
      //     | "E" => {...state, dealer: Some(East)}
      //     | "S" => {...state, dealer: Some(South)}
      //     | "W" => {...state, dealer: Some(West)}
      //     | _ => {...state, dealer: None}
      //   }
      // }
      | Flip (compassPoint) => {
        switch (compassPoint) {
          | North => {...state, handVisible: {...state.handVisible, north: !state.handVisible.north} }
          | East => {...state, handVisible: {...state.handVisible, east: !state.handVisible.east} }
          | South => {...state, handVisible: {...state.handVisible, south: !state.handVisible.south} }
          | West => {...state, handVisible: {...state.handVisible, west: !state.handVisible.west} }
        }
      }
      | Discard => {
        // help with card type, inc (), otherwise lifecycle is unbound
        // test using shuffleIndex = 0
        let myPack = Array.map(
          (card: Shuffle.card) => {
                  card.shuffleIndex === 13
                  ?
                  {...card, lifecycle: Discard} 
                  :
                  {card}
                },
          state.pack
        );
        {...state, pack: myPack}
      }
      | Sync => {
        // replace existing state with gameState
        let myNewState: Shuffle.state = [%bs.raw {| window.gameState |}]   //state;
        //Js.log(myNewState);
        myNewState;
      }
    }
};
