#pragma once

#include "Graphics/glHeaders.hpp"

namespace Graphics {
  namespace g3d {
    class g3dCompatible {
    public:
      virtual GLuint getVBO() = 0;
      virtual GLuint getIBO() = 0;
      virtual GLuint getIBOsize() = 0;
      virtual glm::mat4 getModelMatrix() = 0;
    };
  } // namespace g3d
} // namespace Graphics
