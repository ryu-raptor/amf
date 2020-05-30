#pragma once
#include "EffectorAcceptable.hpp"
#include <memory>
#include <list>

namespace otoge2019 {
  class Effector {
    private:
      std::list<std::shared_ptr<EffectorAcceptable>> effects;
    public:
      Effector();
      void add(std::shared_ptr<EffectorAcceptable>);

      /// @fn
      /// 毎フレーム必ず呼ぶこと
      void routine();
  };
} // namespace otoge2019

