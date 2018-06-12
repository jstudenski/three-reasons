[%bs.raw {|require('./App.css')|}];

type state = {
  playing: bool
};

type action =
 | Toggle;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { playing: false },
  reducer: (action, state) => switch(action) {
    | Toggle => ReasonReact.Update({ playing: !state.playing })
  },
  render: self =>
    <div className="App">
      <button onClick={_ => self.send(Toggle)}>
        (ReasonReact.string(
          self.state.playing ? "Pause" : "Play"
        ))
      </button>
    </div>,
};
