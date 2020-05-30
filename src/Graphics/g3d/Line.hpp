#pragma once

#include <memory>
#include "Graphics/glHeaders.hpp"
#include "Graphics/g3d/g3dCompatible.hpp"
#include "Graphics/g3d/LineShader.hpp"

namespace Graphics {
  namespace g3d {
    class Line : public g3dCompatible
    {
      private:
        GLuint vbo;
        GLuint ibo;
        GLuint iboSize;
      public:
        static std::unique_ptr<LineShader> shader;
        Line();
        ~Line();
        static void setupShader(std::string vertex, std::string fragment);
        void draw(glm::vec3, glm::vec3, GLfloat);
        GLuint getVBO();
        GLuint getIBO();
        GLuint getIBOsize();
        glm::mat4 getModelMatrix();
    };
  } // namespace g3d
} // namespace Graphics
