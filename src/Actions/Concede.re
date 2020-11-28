let execute = (state: TopLevel.state) => {
  let bln: bool = [%raw
    "window.confirm('Are you sure you want to CONCEDE remaining tricks to partnership with highest value cards?')"
  ];
  let returnedState =
    bln
      ? {
        Js.log("do concede action");
        state;
      }
      : {
        Js.log("abort concede action");
        state;
      };
  returnedState;
};
