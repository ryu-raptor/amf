#include "CameraHolder.hpp"
#include <iostream>

using namespace Graphics::g3d;

namespace otoge2019 {
  CameraHolder::CameraHolder(Camera* target)
  {
    camera = target;
  }

  void CameraHolder::setDistance(GLfloat z)
  {
    distance = z;
  }

  glm::vec3 CameraHolder::getPosition()
  {
    return position;
  }

  void CameraHolder::follower(GLfloat x, GLfloat y, GLfloat z)
  {
    /*
    camera->setPosition(0.0f, 0.0f, 20.0f);
    camera->setLookat(0.0f, 0.0f, 0.0f);
    */
    camera->setLookat(x, y, z);
    camera->setPosition(x, y, z + distance);
    position = glm::vec3(x, y, z + distance);
  }
} // namespace otoge2019
