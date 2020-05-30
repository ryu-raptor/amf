#pragma once
#include <unordered_map>
#include "KeyConfigurator.hpp"

namespace otoge2019 {
  class KeyBuffer
  {
    public:
      enum class KeyState {
        release, hit, press
      };

      /// フレームごとに呼び出されて更新
      void update();
      void keyUpdate(int, int);
      KeyState getState(int);
      KeyState getState(KeyConfigurator::Key);
    private:
      std::unordered_map<int, KeyState> buffer;
      std::unordered_map<int, KeyState> lastBuffer;
  };
} // namespace otoge2019
