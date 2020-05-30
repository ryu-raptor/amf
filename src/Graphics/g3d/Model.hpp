#pragma once

#include "Graphics/g3d/g3dCompatible.hpp"
#include <string>

namespace Graphics {
  namespace g3d {
    // グラフィックを行う実体
    class Model : public g3dCompatible {
    public:
      Model(std::string);
      ~Model();

      // 呼ばれる際にワールド行列を再計算する
      void setPosition(glm::vec3 position); // 位置を絶対座標で指定
      void setRotation(GLfloat angle, glm::vec3 axrote); // axroteで回転軸を設定(degee)
      void appendRotation(GLfloat angle, glm::vec3 axrote); // 回転を追加
      void setDirection(glm::vec3 direction); // その物体を向けたい方向の軸を設定. (X軸がデフォルト)
      void setScale(glm::vec3 axscale); // 各軸の倍率を設定
    };
  } // namespace g3d
} // namespace Graphics
