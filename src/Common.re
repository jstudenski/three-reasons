type gameObject = {
  mesh: Three.mesh,
  draw: unit => unit
};

type gameControls = {
  addChild: gameObject => unit,
  resize: unit => unit
};
