#pragma once
#include <memory>
#include <chrono>
#include "EffectorAcceptable.hpp"
#include "Graphics/g3d/DuplicatedPanel.hpp"

namespace otoge2019 {
  class JudgeEffect : public EffectorAcceptable {
    protected:
      std::unique_ptr<Graphics::g3d::DuplicatedPanel> panel;
      double alpha;
      std::chrono::system_clock::time_point ctime, dtime;
    public:
      JudgeEffect();
      ~JudgeEffect();

      void debug();

      bool isFinished();
  };
} // namespace otoge2019
