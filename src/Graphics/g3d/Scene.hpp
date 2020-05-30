#pragma once

#include "Graphics/glHeaders.hpp"
#include "Graphics/g3d/Camera.hpp"
#include <vector>

namespace Graphics {
  namespace g3d {
    class Scene
    {
      private:
        glm::mat4 projection; //> 射影行列
        Camera* camera;
      public:

        Scene();
        ~Scene();
        glm::mat4 getVP();
        void setCamera(Camera*);
    };
  } // namespace g3d
} // namespace Graphics

