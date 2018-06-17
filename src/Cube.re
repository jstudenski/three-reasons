open Common;
open Three;

[@bs.module] external crate : string = "./textures/crate.gif";

type spin = {
  draw: unit => unit
};

type state = {
  spin: option(spin)
};

type action =
 | Spin(spin);

let component = ReasonReact.reducerComponent("Cube");

let animation = (mesh) => {
  let (rx, ry) = (5, 9);

  let draw = () => {
    let rotation = mesh |. rotation;
    rotation |. xSet((rotation |. x) +. float_of_int(rx) /. 1000.0);
    rotation |. ySet((rotation |. y) +. float_of_int(ry) /. 1000.0);
  };

  { draw: draw }
};

let make = (~gameControls: gameControls, _children) => {
  ...component,
  initialState: () => { spin: None },
  reducer: (action, _) =>
    switch(action) {
      | Spin(spin) => ReasonReact.Update({ spin: Some(spin) })
    },
  didMount: self => {
    let geo = boxGeo(200, 200, 200);
    let material = meshBasicMaterial(meshConfig(textureLoader() |. loadTexture(crate)));
    let mesh = mesh(geo, material);
    let spin = animation(mesh);
    gameControls.addChild({mesh, draw: spin.draw});
    self.send(Spin(spin));
  },
  render: _ => ReasonReact.null
}
