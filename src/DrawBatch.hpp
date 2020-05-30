#include <memory>
#include "glHeaders.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Model.hpp"

namespace DrawBatch {
  void setCamera(Camera*);
  void setScene(Scene*);
  GLuint add(Model*);
  void render();
  void renderWithScene(Scene*);
  void remove(GLuint);
  void finalize();
} // namespace DrawBatch

