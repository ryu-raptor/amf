#include "Graphics/g3d/Camera.hpp"

namespace Graphics {
  namespace g3d {
    Camera::Camera()
    {
      position = glm::vec3(0.0f, 0.0f, 0.0f);
      lookat = glm::vec3(0.0f, 0.0f, 0.0f);
      cameraMatrix = glm::lookAt(
          position,
          lookat,
          glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 Camera::getMatrix()
    {
      return cameraMatrix;
    }

    void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z)
    {
      position = glm::vec3(x, y, z);
      updateMatrix();
    }

    void Camera::setLookat(GLfloat x, GLfloat y, GLfloat z)
    {
      lookat = glm::vec3(x, y, z);
      updateMatrix();
    }

    void Camera::updateMatrix()
    {
      cameraMatrix = glm::lookAt(
          position,
          lookat,
          glm::vec3(0.0f, 1.0f, 0.0f));
    }
  }
}
