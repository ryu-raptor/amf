#pragma once

#include "Graphics/glHeaders.hpp"
#include "Graphics/Renderable.hpp"

namespace Graphics {
  namespace g2d {
    class g2dCompatible
    {
    public:
      virtual GLuint getVBO() = 0;
      virtual GLuint getIBO() = 0;
      virtual GLuint getIBOsize() = 0;
      virtual GLuint getTexture() = 0;
    };
  } // namespace g2d
} // namespace Graphics
