open Common;
open Three;

type state = {
  gameControls: option(gameControls),
  initialized: bool
};

type action =
 | Start(gameControls)
 | Ready(option(ReasonReact.reactRef));

let component = ReasonReact.reducerComponent("Scene");

let sceneStart = node => {
  let unwrapped = ReasonReact.refToJsObj(node);
  let rect = unwrapped##getBoundingClientRect();

  let camera = camera(70, rect##width /. rect##height, 1, 1000);
  camera |. position |. zSet(400.0);

  let renderer = rendererConfig(~antialias=true) |. webGLRenderer;
  renderer |. resize(rect##width, rect##height);
  unwrapped##appendChild(renderer |. domElement) |. ignore;

  let scene = scene();

  let gameObjects = ref([]);

  let rec loop = () => {
    animate(loop);
    List.iter(obj => obj.draw(), gameObjects^);
    renderer |. render(scene, camera);
  };

  loop();

  {
    addChild: child => {
      gameObjects := List.append(gameObjects^, [child]);
      scene |. addChild(child.mesh);
    },
    resize: () => {
      let rect = unwrapped##getBoundingClientRect();
      camera |. aspectSet(rect##width /. rect##height);
      camera |. updateProjectionMatrix();
      renderer |. resize(rect##width, rect##height);
    }
  }
}

let make = (children) => {
  ...component,
  initialState: () => { initialized: false, gameControls: None },
  reducer: (action, state) => {
    switch (action) {
      | Start(gc) => ReasonReact.Update({ ...state, gameControls: Some(gc) })
      | Ready(container) => {
        switch(container, state.initialized) {
          | (Some(node), false) => ReasonReact.UpdateWithSideEffects({ ...state, initialized: true }, self => {
            let gameControls = sceneStart(node);
            listen("resize", _ => gameControls.resize());
            self.send(Start(gameControls));
          })
          | _ => ReasonReact.NoUpdate
        }
      }
    }
  },
  render: self =>
    ReasonReact.createDomElement("div", ~props={
      "ref": node => Ready(Js.Nullable.toOption(node)) |. self.send,
      "className": "scene"
    }, [|children(self.state.gameControls)|])
};
