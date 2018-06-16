open Common;

let component = ReasonReact.statelessComponent("Cube");

let make = (~gameControls: gameControls, _) => {
  ...component,
  render: _ => ReasonReact.null
}
