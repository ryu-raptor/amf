#pragma once
#include <memory>
#include "Graphics/g3d/TexturedShader.hpp"
#include "Graphics/g3d/Scene.hpp"
#include "Graphics/g3d/Camera.hpp"
#include "CameraHolder.hpp"
#include "KeyConfigurator.hpp"
#include "KeyBuffer.hpp"

/// シングルトンオブジェクトを格納しておく場所
/// Shader, Scene, Camera, CameraHolder
namespace otoge2019 {
  namespace Singletons {
    extern std::shared_ptr<Graphics::g3d::TexturedShader> shader;
    extern std::shared_ptr<Graphics::g3d::Scene>          scene;
    extern std::shared_ptr<Graphics::g3d::Camera>         camera;
    extern std::shared_ptr<CameraHolder>                  cameraHolder;
    extern KeyBuffer                                      keyBuffer;
    extern KeyConfigurator                                keyConfigurator;
  } // namespace Singletons
} // namespace otoge2019
