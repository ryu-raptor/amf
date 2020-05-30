#pragma once
#include "Graphics/g3d/g3dCompatible.hpp"

namespace Graphics {
  namespace g3d {
    class TexturedCompatible : public g3dCompatible
    {
      public:
        virtual GLuint getTexture() = 0;
        virtual GLfloat getAlpha() = 0;
        virtual glm::vec3 getColorModulation() = 0;
    };
  } // namespace g3d
} // namespace Graphics
