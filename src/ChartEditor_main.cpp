#include <iostream>
#include "Graphics/g3d/Panel.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/g3d/Camera.hpp"
#include "Graphics/g3d/Scene.hpp"
#include "Graphics/g3d/TexturedShader.hpp"
#include "Pacemaker.hpp"
#include "ButtonIdentifier.hpp"
#include "TraceRenderer.hpp"
#include "Graphics/g3d/DuplicatedPanel.hpp"
#include "Alice.hpp"
#include "Mook.hpp"
#include "CameraHolder.hpp"
#include "TraceBuilder.hpp"
#include "NoteBuilder.hpp"
#include "ChartBuilder.hpp"
#include "ResourceFiler.hpp"
#include "Tap.hpp"
#include "Nice.hpp"
#include "KeyBuffer.hpp"
#include "GameFrame.hpp"
#include "Singletons.hpp"
#include "Graphics/g3d/Line.hpp"
#include "EditorFrame.hpp"

using namespace otoge2019;

int main(int argc, char** argv)
{
  Mook::title = "Alice's Music Flight Chart Editor";
  // Zバッファを使わない
  Mook::depthTest = false;
  Mook::init();

  otoge2019::ResourceFiler rf("ResourceInfo.ini");
  auto rcdir = rf.get("root", "ResourceDirectory");
  rf.append(rcdir + "/ResourceInfo.ini");
  rcdir = rf.get("Note", "ResourceDirectory");
  rf.append(rcdir + "/ResourceInfo.ini");
  rcdir = rf.get("Effect", "ResourceDirectory");
  rf.append(rcdir + "/ResourceInfo.ini");
  rcdir = rf.get("Shader", "ResourceDirectory");
  rf.append(rcdir + "/ResourceInfo.ini");

  // staticグラフィックの読み込み
  otoge2019::Tap::loadNoteGraphic(rf);
  otoge2019::Nice::setupGraphic(rf);
  otoge2019::Bad::setupGraphic(rf);

  // シングルトン
  Singletons::scene.reset(new Graphics::g3d::Scene()); // 射影行列が必要
  Singletons::camera.reset(new Graphics::g3d::Camera());
  Singletons::cameraHolder.reset(new otoge2019::CameraHolder(Singletons::camera.get()));
  Singletons::cameraHolder->setDistance(30.0f);

  auto shaderdir = rf.get("Shader", "ResourceDirectory");
#ifdef OLDGL
  auto vshaderpath = shaderdir + "/" + rf.get("Shader.Vertex", "OldGLFile");
  auto fshaderpath = shaderdir + "/" + rf.get("Shader.Fragment", "OldGLFile");
#else
  auto vshaderpath = shaderdir + "/" + rf.get("Shader.Vertex", "File");
  auto fshaderpath = shaderdir + "/" + rf.get("Shader.Fragment", "File");
#endif
  Singletons::shader.reset(new Graphics::g3d::TexturedShader(vshaderpath, fshaderpath));

#ifdef OLDGL
  auto vlshaderpath = shaderdir + "/" + rf.get("Shader.Line.Vertex", "OldGLFile");
  auto flshaderpath = shaderdir + "/" + rf.get("Shader.Line.Fragment", "OldGLFile");
#else
  auto vlshaderpath = shaderdir + "/" + rf.get("Shader.Line.Vertex", "File");
  auto flshaderpath = shaderdir + "/" + rf.get("Shader.Line.Fragment", "File");
#endif
  Graphics::g3d::Line::setupShader(vlshaderpath, flshaderpath);
  Graphics::g3d::Line::shader->setScene(Singletons::scene.get());

  Singletons::camera->setPosition(0.0f, 0.0f, 30.0f);
  Singletons::camera->setLookat(0.0f, 0.0f, 0.0f);
  Singletons::scene->setCamera(Singletons::camera.get());
  Singletons::shader->setScene(Singletons::scene.get());

  // Panelにシェーダを設定
  Graphics::g3d::Panel::setupShader(Singletons::shader);

  if (argc != 2) {
    std::cout << "譜面のディレクトリを与えてください\n";
    Mook::finalize();
    return -1;
  }

  auto chartPath = std::string(argv[1]);
  EditorFrame gameFrame(10.0, chartPath);
  gameFrame.prepare();

  Mook::setRenderProcess([&]{
    gameFrame.routine();
  });

  Mook::doRenderProcess();

  Mook::finalize();

  return 0;
}
