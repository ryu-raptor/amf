#pragma once
#include "Graphics/g3d/g3dCompatible.hpp"
#include "Graphics/g3d/Scene.hpp"

namespace Graphics {
  namespace g3d {
    class LineShader
    {
      private:
        GLuint programID;
        Scene* scene;
        GLuint mvpID;

      public:
        LineShader(std::string vertex, std::string fragment);
        void setScene(Scene*);
        void render(g3dCompatible* object);
    };
  } // namespace g3d
} // namespace Graphics

