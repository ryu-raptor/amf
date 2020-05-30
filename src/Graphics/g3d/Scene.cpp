#include <string>
#include <memory>
#include <vector>
#include "Graphics/g3d/Camera.hpp"

#include "Graphics/g3d/Scene.hpp"

namespace Graphics {
  namespace g3d {
    Scene::Scene()
    {
      projection = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f);
    }

    Scene::~Scene()
    {
    }

    glm::mat4 Scene::getVP()
    {
      return projection * camera->getMatrix();
    }

    void Scene::setCamera(Camera* camera)
    {
      this->camera = camera;
    }
  } // namespace g3d
} // namespace Graphics
