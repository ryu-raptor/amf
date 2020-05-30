#pragma once
#include "ResourceFiler.hpp"
#include "JudgeEffect.hpp"
#include <chrono>

namespace otoge2019 {
  class Bad : public JudgeEffect
  {
    private:
      static std::unique_ptr<Graphics::g3d::Panel> source;

    public:
      static void setupGraphic(ResourceFiler&);
      Bad(GLfloat x, GLfloat y);

      // virtuals
      void render();
  };
} // namespace otoge2019
