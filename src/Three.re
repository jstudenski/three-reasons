type scene;
type jsEvent;

[@bs.deriving abstract]
type rendererConfig = {
  antialias: bool
};

[@bs.deriving abstract]
type renderer = {
  domElement: Dom.element
};

[@bs.deriving abstract]
type vector = {
  mutable x: float,
  mutable y: float,
  mutable z: float
};

[@bs.deriving abstract]
type camera = {
  position: vector,
  mutable aspect: float
};

[@bs.module "three"][@bs.new] external scene : unit => scene = "Scene";
[@bs.module "three"][@bs.new] external camera : (int, float, int, int) => camera = "PerspectiveCamera";
[@bs.send] external updateProjectionMatrix : (camera, unit) => unit = "updateProjectionMatrix";


[@bs.module "three"][@bs.new] external webGLRenderer : rendererConfig => renderer = "WebGLRenderer";
[@bs.send] external resize : (renderer, float, float) => unit = "setSize";
[@bs.send] external render : (renderer, scene, camera) => unit = "render";

[@bs.scope "window"][@bs.val] external animate : (unit => unit) => unit = "requestAnimationFrame";
[@bs.scope "window"][@bs.val] external listen : (string, (jsEvent => unit)) => unit = "addEventListener";
