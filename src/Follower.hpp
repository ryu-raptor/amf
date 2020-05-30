#pragma once
#include "Graphics/glHeaders.hpp"

namespace otoge2019 {
  class Follower
  {
    public:
      /// 追っかけに自分の位置を教えてあげる
      virtual void follower(GLfloat x, GLfloat y, GLfloat z) = 0;
  };
} // namespace otoge2019
