type action =
  | Shuffle
  //| DealerChange (string)
  | Flip (Shuffle.compassPoint)
  // | HideAllCards
  // | ShowAllCards
  // | Deal 
  | Discard
  | Sync
  | Test
  | AssignPlayer(Shuffle.pointOfCompassAndPlayer)
;

// force to type Shuffle.state
let initialState: Shuffle.state = {
    pack: Shuffle.initialPack,
    handVisible: Shuffle.initialHandVisible,
    //dealer: None,
    //cardsDealtCount: 0,
    pointOfCompassAndPlayers: [||],
    randomInt: 0
};

let reducer = (state: Shuffle.state, action) => {
    switch action {
      | Shuffle => {
        // Shuffle.rei is helpful here
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
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
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        switch (compassPoint) {
          | North => {...state, handVisible: {...state.handVisible, north: !state.handVisible.north} }
          | East => {...state, handVisible: {...state.handVisible, east: !state.handVisible.east} }
          | South => {...state, handVisible: {...state.handVisible, south: !state.handVisible.south} }
          | West => {...state, handVisible: {...state.handVisible, west: !state.handVisible.west} }
        }
      }
      | Discard => {
        Js.log("Action-Discard");
        // make sure doMessage IS called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        // replace existing state with gameState
        let myNewState: Shuffle.state = [%bs.raw {| window.gameState |}];   //state;
        myNewState;
      }
      | Sync => {
        // replace existing state with gameState
        let myNewState: Shuffle.state = [%bs.raw {| window.gameState |}];   //state;
        //Js.log("Action - Sync");
        // make sure doMessage is NOT called in sidebar component
        let () = [%raw "window.isLastActionSync = true"];
        myNewState;
      }
      | Test => {
        // make sure doMessage is NOT called in sidebar component
        let () = [%raw "window.isLastActionSync = true"];
        Js.log("benign action: 'Test'");
        state
      }
      | AssignPlayer(pOfCAndP) => {
        // make sure doMessage is called in sidebar component
        let () = [%raw "window.isLastActionSync = false"];
        //Js.log("action AssignPlayer " ++ pOfCAndP.player ++ " to " ++ pOfCAndP.pointOfCompass);
        //let myNewArray = state.pointOfCompassAndPlayers;
        //{...state, pointOfCompassAndPlayers: myNewArray}
        let myArray1 = Array.map(
          (pointOfCompassAndPlayer: Shuffle.pointOfCompassAndPlayer) => {
            pointOfCompassAndPlayer.pointOfCompass == pOfCAndP.pointOfCompass
            ?
            {...pointOfCompassAndPlayer, pointOfCompass: ""}
            :
            {pointOfCompassAndPlayer}
          },
          state.pointOfCompassAndPlayers
        );
        let myArray2 = Array.map(
          (pointOfCompassAndPlayer: Shuffle.pointOfCompassAndPlayer) => {
            pointOfCompassAndPlayer.player == pOfCAndP.player
            ?
            {...pointOfCompassAndPlayer, pointOfCompass: pOfCAndP.pointOfCompass}
            :
            {pointOfCompassAndPlayer}
          },
          myArray1
        );
        {...state, pointOfCompassAndPlayers: myArray2}
      }
    }
};
