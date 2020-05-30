#pragma once

#include "Graphics/glHeaders.hpp"

namespace Graphics {
  namespace g3d {
    struct g3dVertexData
    {
      glm::vec3 vertex;
      glm::vec3 normal;
      glm::vec2 UV;
    };
  }
}
