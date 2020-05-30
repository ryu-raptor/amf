#include "Graphics/Renderable.hpp"

namespace Graphics {
class Renderer {
  Renderable* root;
  public:
    Renderer(Renderable* root);
};

Renderer::Renderer(Renderable* root) {
  this->root = root;
}

} // namespace Graphics

