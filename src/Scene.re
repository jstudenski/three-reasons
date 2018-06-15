open Three;

type scene = {
  resize: unit => unit
};

type state = {
  initialized: bool
};

type action =
 | Ready(option(Dom.element));

let component = ReasonReact.reducerComponent("Scene");

let sceneStart = node => {
  let unwrapped = ReactDOMRe.domElementToObj(node);
  let rect = unwrapped##getBoundingClientRect();

  let camera = camera(70, rect##width /. rect##height, 1, 1000);
  camera |. position |. zSet(400.0);

  let renderer = rendererConfig(~antialias=true) |. webGLRenderer;
  renderer |. resize(rect##width, rect##height);
  unwrapped##appendChild(renderer |. domElement) |. ignore;

  let scene = scene();

  let rec loop = () => {
    animate(loop);
    renderer |. render(scene, camera);
  };

  loop();

  {
    resize: () => {
      let rect = unwrapped##getBoundingClientRect();
      camera |. aspectSet(rect##width /. rect##height);
      camera |. updateProjectionMatrix();
      renderer |. resize(rect##width, rect##height);
    }
  }
}

let make = (_) => {
  ...component,
  initialState: () => { initialized: false },
  reducer: (action, state) => {
    switch (action) {
      | Ready(container) => {
        switch(container, state.initialized) {
          | (Some(node), false) => ReasonReact.UpdateWithSideEffects({ initialized: true }, _ => {
            let game = sceneStart(node);
            listen("resize", _ => game.resize());
          })
          | _ => ReasonReact.NoUpdate
        }
      }
    }
  },
  render: self =>
    <div className="scene" ref={node => self.send(Ready(Js.Nullable.toOption(node)))} />
};
