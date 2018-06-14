[%bs.raw {|require('./App.css')|}];

type state = {
  rotationX: int,
  rotationY: int
};

type axis =
 | X
 | Y;

type action =
  | Rotate(axis, int);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { rotationX: 5, rotationY: 9 },
  reducer: (action, state: state) => {
    switch(action) {
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
      </div>
      <div className="scene" />
    </div>,
};
