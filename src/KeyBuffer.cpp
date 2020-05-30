#include "KeyBuffer.hpp"
#include "Singletons.hpp"
#include <iostream>
#include "Graphics/glHeaders.hpp"

namespace otoge2019 {
  void KeyBuffer::update()
  {
    // bufferの値をinsert
    for (auto pair : buffer) {
      lastBuffer.insert(pair);
    }
    // バッファを更新
    for (auto pair : lastBuffer) {
      // last = hit & now = hit  -> hit
      // last = hit & now = rele -> rele
      // last = pre & now = rele -> rele

      // last = hit & now = none -> press
      if (buffer.find(pair.first) == buffer.end()) { 
        // set rule
        if (pair.second == KeyState::hit) {
          lastBuffer[pair.first] = KeyState::press;
        }
        // keep rule
      }
      // copy rule
      else {
        lastBuffer[pair.first] = buffer[pair.first];
      }
    }
    buffer.clear();
  }

  void KeyBuffer::keyUpdate(int keyCode, int state)
  {
    KeyState kstate = KeyState::release;
    if (state == GLFW_PRESS) {
      //std::cout << "hit!!\n";
      kstate = KeyState::hit;
    }
    else if (state == GLFW_RELEASE) {
      //std::cout << "release!!\n";
      kstate = KeyState::release;
    }
    else if (state == GLFW_REPEAT) {
      //std::cout << "repeat!!\n";
      kstate = KeyState::press;
    }

    buffer[keyCode] = kstate;
  }

  KeyBuffer::KeyState KeyBuffer::getState(int keyCode)
  {
    // 見つからない
    if (lastBuffer.find(keyCode) == lastBuffer.end()) {
      return KeyState::release;
    }
    return lastBuffer[keyCode];
  }

  KeyBuffer::KeyState KeyBuffer::getState(KeyConfigurator::Key key)
  {
    return getState(Singletons::keyConfigurator.get(key));
  }
} // namespace otoge2019
