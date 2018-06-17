open Three;

[%bs.raw {|require('./App.css')|}];
[@bs.module] external crate : string = "./textures/crate.gif";
[@bs.module] external brick : string = "./textures/rock-wall.jpg";
[@bs.module] external manicube : string = "./textures/manicube.png";

let textures = [|crate, brick, manicube|];

type state = {
  texture: texture,
  rotationX: int,
  rotationY: int
};

type axis =
 | X
 | Y;

type action =
  | Skin(string)
  | Rotate(axis, int);

let component = ReasonReact.reducerComponent("App");

let skin = texture => textureLoader() |. loadTexture(texture);

let make = (_children) => {
  ...component,
  initialState: () => { rotationX: 5, rotationY: 9, texture: skin(crate) },
  reducer: (action, state: state) => {
    switch(action) {
      | Skin(tx) => ReasonReact.Update({ ...state, texture: skin(tx) })
      | Rotate(axis, rotation) => {
        switch(axis) {
          | X => ReasonReact.Update({ ...state, rotationX: rotation })
          | Y => ReasonReact.Update({ ...state, rotationY: rotation })
        }
      }
    }
  },
  render: self =>
    <div className="container">
      <div className="controls">
        <h2> (ReasonReact.string("Rotation")) </h2>
        <div className="control">
          <label className="control-label">
            (ReasonReact.string("X: "))
          </label>
          <IntegerInput value={self.state.rotationX} change={x => self.send(Rotate(X, x))} />
        </div>
        <div className="control">
          <label className="control-label">
            (ReasonReact.string("Y: "))
          </label>
          <IntegerInput value={self.state.rotationY} change={y => self.send(Rotate(Y, y))} />
        </div>
        <h2> (ReasonReact.string("Texture")) </h2>
        <Fragment>
          (Array.map(t => (
            <img key={t} src={t} height="128" width="128" onClick={_ => self.send(Skin(t))} />
          ), textures))
        </Fragment>
        </div>
      <Scene>
        ...(
          gameControls => {
            switch(gameControls) {
              | None => ReasonReact.null
              | Some(gc) =>
                <Cube
                 gameControls={gc}
                 rotateX={self.state.rotationX}
                 rotateY={self.state.rotationY}
                 texture={self.state.texture}
                />
            }
          }
        )
      </Scene>
    </div>,
};
