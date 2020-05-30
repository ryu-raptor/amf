#pragma once

#include "g3dCompatible.hpp"
#include "g3dVertexData.hpp"
#include "vector"

namespace Graphics {
  namespace g3d {
    // 太めのよく見える線を引く
    // 直線を直方体で表すので頂点数が8倍になる.
    // 直線: 2n - 1頂点 nは線の本数(n > 2)
    // FineLine: 4(2n - 1) = 8n - 4
    class FineLine : g3dCompatible
    {
      std::vector"g3dVertexData" v;
      GLfloat vbo;
      GLfloat ido;
    };
  } // namespace g3d
} // namespace Graphics

