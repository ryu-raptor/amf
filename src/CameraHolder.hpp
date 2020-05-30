#pragma once
/// カメラホルダー
/// カメラの移動させる

#include "Follower.hpp"
#include "Graphics/g3d/Camera.hpp"

using namespace Graphics::g3d;

namespace otoge2019 {
  class CameraHolder : public Follower
  {
    private:
      Camera *camera;
      GLfloat distance;
      glm::vec3 position;
    public:
      CameraHolder(Camera*);
      /// @fn
      /// ゼロ平面からの距離を設定します
      void setDistance(GLfloat z);
      void follower(GLfloat x, GLfloat y, GLfloat z);
      glm::vec3 getPosition();
  };
} // namespace otoge2019
