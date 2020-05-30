#pragma once
#include "Graphics/g3d/Panel.hpp"

namespace Graphics {
  namespace g3d {
    /// リソースを勝手に開放しない
    /// 親のパネルのopenGLバッファへの参照を持つ
    /// 拡大縮小行列を引き継ぐ
    class DuplicatedPanel : public Panel
    {
      public:
        DuplicatedPanel(Panel&);
        ~DuplicatedPanel();
    };
  } // namespace g3d
} // namespace Graphics
