#pragma once

#include "JudgeEffect.hpp"
#include "ResourceFiler.hpp"
#include "Graphics/g3d/DuplicatedPanel.hpp"
#include "Graphics/glHeaders.hpp"

namespace otoge2019 {
  class Nice : public JudgeEffect
  {
    private:
      static std::unique_ptr<Graphics::g3d::Panel> source;
    public:
      static void setupGraphic(ResourceFiler&);
      Nice(GLfloat x, GLfloat y);

      // virtuals
      void render();
  };
} // namespace otoge2019
