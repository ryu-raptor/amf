#include "Tap.hpp"
#include <iostream>
#include <cmath>

namespace otoge2019 {
  double Tap::forwardMissThreasholds = 0.6; //> 早押しミスの閾値

  Tap::Tap()
  {
  }

  Tap::Tap(ButtonIdentifier bi, Trace trace)
  {
    this->trace = trace;
    //std::cout << "Tap: Trace: (p: " << trace.position << ", t: " << trace.seconds << ", h: " << trace.height << std::endl;
    point.reset(new Graphics::g3d::DuplicatedPanel(*(pointSource.get())));
    int sign = 1;
    if (bi == ButtonIdentifier::Upper) {
      sign = 1;
      point->setColorModulation(255, 0, 0);
    }
    else {
      sign = -1;
      point->setColorModulation(0, 0, 255);
    }

    this->trace.height = trace.height + sign * laneHeightOffset;
    point->setPosition(trace.position, this->trace.height, 0);

    scored = false;
  }

  void Tap::render()
  {
    point->renderWithDefault();
  }

  Note::Result Tap::state(KeyBuffer::KeyState ks, double seconds)
  {
    //std::cout << "state: " << std::endl;
    // 現在時刻との比較
    // Nice判定範囲
    if (std::abs(trace.seconds - seconds) <= judgeThreasholds) {
      // 押していたらもちろんオーケー
      if (ks == KeyBuffer::KeyState::hit) {
        //std::cout << "state\n";
        if (putScore) {
          scored = true;
          putScore(Judge::Nice, trace.position, trace.height);
        }
        return release;
      }
    }
    // 遅れた時
    else if (seconds > trace.seconds) {
      if (putScore) {
        scored = true;
        putScore(Judge::Bad, trace.position, trace.height);
      }
      return release;
    }
    /*
    // 早い時
    else if (trace.seconds - seconds < forwardMissThreasholds){
      // 押していたら早押しなのでアウト
      if (ks == KeyBuffer::KeyState::hit) {
        if (putScore) {
          scored = true;
          putScore(Judge::Bad, trace.position, trace.height);
        }
        return release;
      }
    }
    */
    return keep;
  }

  double Tap::metric(double seconds)
  {
    return std::abs(trace.seconds - seconds);
  }

  void Tap::loadNoteGraphic(ResourceFiler resource)
  {
    auto filename = resource.get("Tap.Graphic", "Point");
    auto directory = resource.get("Note", "ResourceDirectory");
    auto path = directory + "/" + filename;
    pointSource.reset(new Graphics::g3d::Panel(path, 0.01));
  }

  bool Tap::isFinished()
  {
    if (!scored) {
      putScore(Judge::Bad, trace.position, trace.height);
      scored = true;
    }
    return true;
  }

  // クロージャによって動的に生成された関数を実行する
  void Tap::scheduledTask()
  {
  }

  std::shared_ptr<Graphics::g3d::Panel> Tap::pointSource; //> タップ点のグラフィックの素
} // namespace otoge2019
