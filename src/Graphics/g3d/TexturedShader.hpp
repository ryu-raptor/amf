#pragma once
#include "Graphics/g3d/TexturedCompatible.hpp"
#include "Graphics/g3d/Scene.hpp"

namespace Graphics {
  namespace g3d {
    class TexturedShader
    {
      private:
        GLuint programID;
        Scene* scene;
        GLuint textureSamplerID;
        GLuint mvpID;
        GLfloat alphaID;
        GLfloat modulationID;

      public:
        TexturedShader(std::string vertex, std::string fragment);
        void setScene(Scene*);
        void render(TexturedCompatible* object);
    };
  } // namespace g3d
} // namespace Graphics

