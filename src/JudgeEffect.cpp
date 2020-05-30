#include "JudgeEffect.hpp"
#include <iostream>
#include <chrono>

namespace otoge2019 {
  JudgeEffect::JudgeEffect()
  {
    //std::cout << this << " constructed\n";
    ctime = std::chrono::system_clock::now();
  }

  JudgeEffect::~JudgeEffect()
  {
    dtime = std::chrono::system_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(dtime - ctime).count();
    //std::cout << this << " released: within " << dur << " ms\n";
  }

  void JudgeEffect::debug()
  {
    //std::cout << this << " render call: " << alpha << "\n";
  }
  
  bool JudgeEffect::isFinished()
  {
    if (alpha > 0) {
      alpha = alpha > 0.01 ? alpha - 0.01 : 0;
      panel->setAlpha(alpha);
      return false;
    }
    else {
      alpha = 0;
      panel->setAlpha(alpha);
      return true;
    }
  }
} // namespace otoge2019
