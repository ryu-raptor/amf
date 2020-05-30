#include "Alice.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "Graphics/glHeaders.hpp"

namespace otoge2019 {
  Alice::Alice(std::string alicepath, Chart* playingChart, Pacemaker* pacemaker)
  {
    texture = new Graphics::Texture(alicepath);
    graphic.reset(new Graphics::g3d::Panel(texture, 0.01));
    graphic->setAlpha(1);
    this->chart = playingChart;
    this->pacemaker = pacemaker;
    follower = nullptr;
  }

  Alice::~Alice()
  {
    delete texture;
  }

  void Alice::setAlpha(double a)
  {
    graphic->setAlpha(a);
  }

  double Alice::linearInterpolation(Trace* t1, Trace* t2, double s, Trace* &responce, double* gradptr = nullptr)
  {
    if (gradptr != nullptr) {
      *gradptr = 0;
    }
    // 普通の状態
    if (t1->seconds < t2->seconds) {
      // すでに次のトレースの後ろにいる
      if (t2->seconds <= s) {
        responce = t2;
        return t2->height;
      }
      responce = t1;
      auto a = (t2->height - t1->height) / (t2->seconds - t1->seconds);
      if (gradptr != nullptr) {
        *gradptr = a;
      }
      return (s - t1->seconds) * a + t1->height;
    }
    // 次のトレースが前のトレースに被っている
    else {
      responce = t2;
      return t2->height;
    }
  }

  /// アリスの現在の高さを取得
  double Alice::getHeight()
  {
    auto position = pacemaker->getAlicePosition();
    auto tindex = chart->getLatestTraceIndex(pacemaker->getSeconds(position));
    Trace t1, t2;
    // アリスが開始トレースよりも早い位置にいる場合
    if (tindex <= -1) {
      t1.seconds = -100000;
      t1.height = 0;
    }
    else {
      t1 = chart->getTrace(tindex);
    }

    // アリスが最終トレースよりも遅い位置にいる場合
    if (tindex + 1 >= chart->getTracesSize()) {
      t2.seconds = 100000;
      t2.height = 0;
    }
    else {
      t2 = chart->getTrace(tindex + 1);
    }

    // TODO: 何に使うの?
    Trace* res;

    return linearInterpolation(&t1, &t2, pacemaker->getSeconds(position), res, &gradient);
  }

  int Alice::getLatestTraceIndex(double seconds)
  {
    int index = -1;
    int i;
    for (i = 0; i < chart->traces->size(); i++) {
      if ((*(chart->traces))[i].seconds > seconds)
      {
        break;
      }
    }
    index = i - 1;
    return index;
  }

  void Alice::render()
  {
    graphic->renderWithDefault();
  }

  // あんまり片付いていない関数
  void Alice::update()
  {
    auto position = pacemaker->getAlicePosition();
    // 回転と高さを求める
    auto lastg = gradient;
    auto height = getHeight();
    
    /*
    if (lastg != gradient) {
      // gradient -> radian
      auto radian = std::atan(gradient);
      graphic->setRotation(radian , glm::vec3(0, 0, 1));
    }
    */
    
    graphic->setPosition(position, height, 0);
    if (follower != nullptr) {
      follower->follower(position, height, 0);
    }
  }

  void Alice::followee(Follower* f)
  {
    follower = f;
  }
} // namespace otoge2019
