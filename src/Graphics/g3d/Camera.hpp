#pragma once
#include "Graphics/glHeaders.hpp"

namespace Graphics {
  namespace g3d {
    /// カメラオブジェクト
    class Camera
    {
      private:
        glm::vec3 position, lookat;
        glm::mat4 cameraMatrix;

        void updateMatrix();
      public:
        Camera();
        glm::mat4 getMatrix();
        void setPosition(GLfloat x, GLfloat y, GLfloat z);
        void setLookat(GLfloat x, GLfloat y, GLfloat z);
    };
  } // namespace g3d
} // namespace Graphics
