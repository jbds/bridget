let doConcede = (state: TopLevel.state) => {
  let remainingCardsNS =
    Belt.Array.keep(state.pack, x => {
      x.lifecycle === Hand
      && (
        x.shuffleIndex >= 0
        && x.shuffleIndex <= 12
        || x.shuffleIndex >= 26
        && x.shuffleIndex <= 38
      )
    });
  Js.log(remainingCardsNS);
  state;
};

let execute = (state: TopLevel.state) => {
  let bln: bool = [%raw
    "window.confirm('Are you sure you want to CONCEDE remaining tricks to partnership with highest value cards?')"
  ];
  let returnedState =
    bln
      ? {
        Js.log("do concede action");
        doConcede(state);
      }
      : {
        Js.log("abort concede action");
        state;
      };
  returnedState;
};
