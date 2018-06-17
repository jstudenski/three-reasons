open Common;
open Three;

[@bs.module] external crate : string = "./textures/crate.gif";

type spin = {
  draw: unit => unit,
  updateTexture: texture => unit,
  changeRotation: (int, int) => unit
};

type state = {
  texture: texture,
  rotateX: int,
  rotateY: int,
  spin: option(spin)
};

type action =
 | Spin(spin);

let component = ReasonReact.reducerComponent("Cube");

let animation = (mesh, rotateX, rotateY) => {
  let (rx, ry) = (ref(rotateX), ref(rotateY));

  let draw = () => {
    let rotation = mesh |. rotation;
    rotation |. xSet((rotation |. x) +. float_of_int(rx^) /. 1000.0);
    rotation |. ySet((rotation |. y) +. float_of_int(ry^) /. 1000.0);
  };

  {
    draw: draw,
    changeRotation: (rotateX, rotateY) => {
      rx := rotateX;
      ry := rotateY;
    },
    updateTexture: texture => {
      mesh |. materialSet(meshConfig(~map=texture) |. meshBasicMaterial);
    }
  }
};

let make = (~gameControls: gameControls, ~rotateX, ~rotateY, ~texture: texture, _children) => {
  ...component,
  initialState: () => { spin: None, rotateX, rotateY, texture },
  reducer: (action, state) =>
    switch(action) {
      | Spin(spin) => ReasonReact.Update({ ...state, spin: Some(spin) })
    },
  didMount: self => {
    let geo = boxGeo(200, 200, 200);
    let material = meshBasicMaterial(meshConfig(texture));
    let mesh = mesh(geo, material);
    let spin = animation(mesh, rotateX, rotateY);
    gameControls.addChild({mesh, draw: spin.draw});
    self.send(Spin(spin));
  },
  willReceiveProps: self => {
    switch (self.state.spin) {
      | None => ()
      | Some(s) => {
        if (rotateX != self.state.rotateX || rotateY != self.state.rotateY) {
          s.changeRotation(rotateX, rotateY);
        };

        if (self.state.texture != texture) {
          s.updateTexture(texture);
        };
      }
    };

    { ...self.state, rotateX, rotateY };
  },
  render: _ => ReasonReact.null
}
