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
#include "GameFrame.cpp"
#include "Singletons.hpp"
#include "Graphics/g3d/Line.hpp"
#include "EditorFrame.cpp"

using namespace otoge2019;

int main()
{
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

  auto shaderdir = rf.get("Shader", "ResourceDirectory");
#ifdef OLDGL
  auto vshaderpath = shaderdir + "/" + rf.get("Shader.Vertex", "OldGLFile");
  auto fshaderpath = shaderdir + "/" + rf.get("Shader.Fragment", "OldGLFile");
#else
  auto vshaderpath = shaderdir + "/" + rf.get("Shader.Vertex", "File");
  auto fshaderpath = shaderdir + "/" + rf.get("Shader.Fragment", "File");
#endif
  Singletons::shader.reset(new Graphics::g3d::TexturedShader(vshaderpath, fshaderpath));
  Graphics::g3d::Line::setupShader(shaderdir + "/g3dLineShader.vertex.shader", shaderdir + "/g3dLineShader.fragment.shader");
  Graphics::g3d::Line::shader->setScene(Singletons::scene.get());

  Singletons::camera->setPosition(0.0f, 0.0f, 30.0f);
  Singletons::camera->setLookat(0.0f, 0.0f, 0.0f);
  Singletons::scene->setCamera(Singletons::camera.get());
  Singletons::shader->setScene(Singletons::scene.get());

  // Panelにシェーダを設定
  Graphics::g3d::Panel::setupShader(Singletons::shader);

  otoge2019::TraceRenderer trenderer("fallback.png");
  otoge2019::Pacemaker pacemaker;
  pacemaker.setScale(1.0);

  /*
  otoge2019::ChartBuilder cbuilder("Tutorial.chart", pacemaker);;
  auto chart = cbuilder.get();
  */
  /*
  otoge2019::TraceBuilder builder;
  otoge2019::NoteBuilder nbuilder;
  auto traces = builder.build("Tutorial.chart/trace", pacemaker);
  nbuilder.build("Tutorial.chart/note", traces);
  auto notes = nbuilder.get(otoge2019::ButtonIdentifier::Upper);
  for (auto nptr : *notes) {
    std::cout << nptr->metric(0) << std::endl;
  }
  */
  /*
  GLfloat x = -10;
  pacemaker.setTickFunction([&]{return x;});
  */

  // Alice
  /*
  otoge2019::Alice alice("fallback.png", chart.get(), &pacemaker);
  alice.followee(Singletons::cameraHolder.get());
  */

  /*
  Mook::setKeyCallback([&](int keycode, int scancode, int action, int mod) {
    Mook::keyBuffer.keyUpdate(keycode, action);
  });
  */

  //EditorFrame gameFrame(10.0, "Tutorial.chart");
  GameFrame gameFrame(10.0, "charts/U.N.Owen_was_her.chart");
  gameFrame.prepare();

  Mook::setRenderProcess([&]{
    gameFrame.routine();
    /*
    Mook::keyBuffer.update();
    if (Mook::keyBuffer.getState(GLFW_KEY_SPACE) != KeyBuffer::KeyState::release) {
      x += 0.1;
    }
    alice.update();
    //Graphics::g3d::Panel::defaultShader->render(&p);
    //Graphics::g3d::Panel::defaultShader->render(&dp);
    trenderer.render(chart->traces, &pacemaker);
    alice.render();
    chart->routine();
    */
  });

  Mook::doRenderProcess();
  Mook::finalize();

  return 0;
}
