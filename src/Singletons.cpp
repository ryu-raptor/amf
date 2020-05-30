#include "Singletons.hpp"

/// シングルトンオブジェクトを格納しておく場所
/// Shader, Scene, Camera, CameraHolder
namespace otoge2019 {
  namespace Singletons {
    std::shared_ptr<Graphics::g3d::TexturedShader> shader;
    std::shared_ptr<Graphics::g3d::Scene>          scene;
    std::shared_ptr<Graphics::g3d::Camera>         camera;
    std::shared_ptr<CameraHolder>                  cameraHolder;
    KeyBuffer                                      keyBuffer;
    KeyConfigurator                                keyConfigurator;
  } // namespace Singletons
} // namespace otoge2019
