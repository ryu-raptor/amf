#include "GameFrame.hpp"
#include <iostream>
#include "ChartBuilder.hpp"
#include "Singletons.hpp"
#include "Mook.hpp"
#include "Singletons.hpp"

using namespace Graphics::g2d;

namespace otoge2019 {
  void GameFrame::test_put_effect(Judge j, GLfloat x, GLfloat y)
  {
    if (j == Judge::Nice) {
      effector.add(std::shared_ptr<EffectorAcceptable>(new Nice(x, y)));
    }
    else {
      effector.add(std::shared_ptr<EffectorAcceptable>(new Bad(x, y)));
    }
  }

  GameFrame::GameFrame(double scale, std::string chartpath) {
    // ペースメーカをコンストラクトしておく
    pacemaker.setScale(scale);
    this->chartpath = chartpath;
  }

  void GameFrame::prepare()
  {
    ResourceFiler rf("ResourceInfo.ini");
    auto resourcedir = rf.get("root", "ResourceDirectory");
    rf.append(resourcedir + "/" + "ResourceInfo.ini");
    resourcedir = rf.get("Trace", "ResourceDirectory");
    rf.append(resourcedir + "/" + "ResourceInfo.ini");
    resourcedir = rf.get("Shader", "ResourceDirectory");
    rf.append(resourcedir + "/" + "ResourceInfo.ini");

    traceRenderer.reset(new TraceRenderer(rf.get("Trace", "ResourceDirectory") + "/" + rf.get("Trace", "Graphic")));
    sky.loadImage(rf.get("root", "ResourceDirectory") + "/Sky.png");
    auto shaderdir = rf.get("Shader", "ResourceDirectory");
    auto vipath = shaderdir + "/" + rf.get("Shader.g2d.Vertex", "File");
    auto fipath = shaderdir + "/" + rf.get("Shader.g2d.Fragment", "File");
    imageShader.reset(new ImageShader("resources/shaders/g2dShader.vertex.shader", "resources/shaders/g2dShader.fragment.shader"));//.reset(new Graphics::g2d::ImageShader(vipath, fipath));
    guage.reset(new Graphics::g2d::Image("fallback.png", 0, 0));
    keyConfig.load("KeyConfig.ini");

    // Chart
    ChartBuilder cbuilder(chartpath, pacemaker);
    chart = cbuilder.get();

    // Alice
    alice.reset(new Alice(rf.get("root", "ResourceDirectory") + "/" + rf.get("Alice", "Graphic"), chart.get(), &pacemaker));
    alice->followee(Singletons::cameraHolder.get());

    // Effector
    Note::setPutScoreCallback([&](Judge j, GLfloat x, GLfloat y){
      this->test_put_effect(j, x, y);
    });

    // Music
    if (!music.openFromFile(chartpath + "/" + "song.ogg")) {
      throw std::ios::failure("曲のオープンに失敗しました");
    }

    pacemaker.setTickFunction([&]{
      //if (music.getStatus() == sf::Music::Playing) {
        return music.getPlayingOffset().asSeconds();
      //}
      /*
      else {
        return -5.0f;
      }
      */
    });

    music.play();
  }

  void GameFrame::routine()
  {
    //std::cout << "\r" << music.getPlayingOffset().asSeconds();
    // キーバッファからボタンバッファへ移植
    Chart::ButtonBuffer bb;
    //bb.set(ButtonIdentifier::Upper, keyBuffer.getState(GLFW_KEY_UP));
    //bb.set(ButtonIdentifier::Lower, keyBuffer.getState(GLFW_KEY_DOWN));
    bb.set(ButtonIdentifier::Upper, Singletons::keyBuffer.getState(KeyConfigurator::Key::up));
    bb.set(ButtonIdentifier::Lower, Singletons::keyBuffer.getState(KeyConfigurator::Key::down));
    /*
    switch (keyBuffer.getState(GLFW_KEY_DOWN)) {
      case KeyBuffer::KeyState::hit:
        std::cout << "hit\n";
        break;
      case KeyBuffer::KeyState::press:
        std::cout << "press\n";
        break;
    }
    */

    // TEST: metric計算がちゃんとされているか確認
    chart->checkState(bb, pacemaker.getSeconds(pacemaker.getAlicePosition()));
    alice->update();
    sky.render();
    //traceRenderer->render(chart->traces);
    alice->render();
    chart->routine();
    effector.routine();
    //imageShader->render(guage.get());
    //line.draw(glm::vec3(0, 0, 0), glm::vec3(100, 0, 0), 1.0f);
  }

  void GameFrame::show()
  {
  }

  void GameFrame::dismiss()
  {
  }
} // namespace otoge2019
