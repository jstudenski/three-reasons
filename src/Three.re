type scene;
type jsEvent;
type textureLoader;
type texture;
type geometry;
type material;

[@bs.deriving abstract]
type rendererConfig = {
  antialias: bool
};

[@bs.deriving abstract]
type renderer = {
  domElement: Dom.element
};

[@bs.deriving abstract]
type meshConfig = {
  map: texture
};

[@bs.deriving abstract]
type vector = {
  mutable x: float,
  mutable y: float,
  mutable z: float
};

[@bs.deriving abstract]
type mesh = {
  rotation: vector,
  mutable material: material
};

[@bs.deriving abstract]
type camera = {
  position: vector,
  mutable aspect: float
};

type childObject = mesh;

[@bs.module "three"][@bs.new] external scene : unit => scene = "Scene";
[@bs.module "three"][@bs.new] external camera : (int, float, int, int) => camera = "PerspectiveCamera";
[@bs.send] external updateProjectionMatrix : (camera, unit) => unit = "updateProjectionMatrix";
[@bs.send] external addChild : (scene, childObject) => unit = "add";


[@bs.module "three"][@bs.new] external webGLRenderer : rendererConfig => renderer = "WebGLRenderer";
[@bs.send] external resize : (renderer, float, float) => unit = "setSize";
[@bs.send] external render : (renderer, scene, camera) => unit = "render";

[@bs.scope "window"][@bs.val] external animate : (unit => unit) => unit = "requestAnimationFrame";
[@bs.scope "window"][@bs.val] external listen : (string, (jsEvent => unit)) => unit = "addEventListener";

[@bs.module "three"][@bs.new] external textureLoader : unit => textureLoader = "TextureLoader";
[@bs.send] external loadTexture : (textureLoader, string) => texture = "load";
[@bs.module "three"][@bs.new] external boxGeo : (int, int, int) => geometry = "BoxBufferGeometry";
[@bs.module "three"][@bs.new] external meshBasicMaterial : meshConfig => material = "MeshBasicMaterial";
[@bs.module "three"][@bs.new] external mesh : (geometry, material) => mesh = "Mesh";
