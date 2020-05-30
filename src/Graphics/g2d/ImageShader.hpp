#pragma once

#include "g2dCompatible.hpp"
#include <string>

namespace Graphics {
  namespace g2d {
    class ImageShader
    {
      GLuint programID;
      GLuint textureSamplerID;

      GLuint vbo;
      GLuint uvbo;
      GLuint ibo;
    public:
      ImageShader(std::string vertex, std::string fragment);
      void render(g2dCompatible* object);
    };
  } // namespace g2d
} // namespace Graphics
