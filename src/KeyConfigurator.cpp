#include "KeyConfigurator.hpp"
#include "ResourceFiler.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <sstream>
#include <memory>

namespace otoge2019 {
  KeyConfigurator::KeyConfigurator() {
    
  }

  void KeyConfigurator::load(std::string path)
  {
    std::stringstream ss;
    ResourceFiler rf(path);
    rf.lockCategory("KeyConfiguration");
    ss << rf.get("Up");
    ss >> keyMap[Key::up];
    ss.clear();
    ss << rf.get("Down");
    ss >> keyMap[Key::down];
    ss.clear();
    ss << rf.get("Select");
    ss >> keyMap[Key::select];
    std::cout << "Key: Up: " << get(Key::up) << "\n";
    std::cout << "Key: Down: " << get(Key::down) << "\n";
    std::cout << "Key: Select: " << get(Key::select) << "\n";
  }

  int KeyConfigurator::get(Key key)
  {
    return keyMap.at(key);
  }
} // namespace otoge2019
