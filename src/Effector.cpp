#include "EffectorAcceptable.hpp"
#include "Effector.hpp"
#include <memory>
#include <list>

namespace otoge2019 {
  Effector::Effector() {
    
  }

  void Effector::add(std::shared_ptr<EffectorAcceptable> effect)
  {
    effects.push_back(effect);
  }

  void Effector::routine()
  {
    // 描画および削除処理
    for (auto itr = effects.begin(); itr != effects.end();) {
      if (!(*itr)->isFinished()) {
        (*itr)->render();
        itr++;
      }
      else {
        itr = effects.erase(itr);
      }
    }
  }
} // namespace otoge2019
