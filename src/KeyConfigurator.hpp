#pragma once
#include <unordered_map>
#include <string>

namespace otoge2019 {
  class KeyConfigurator {
    public:
      enum class Key {
        up, down, select
      };
      KeyConfigurator();
      void load(std::string);
      int get(Key);
    private:
      std::unordered_map<Key, short> keyMap;
  };
}
