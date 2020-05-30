#include <vector>
#include "Image.hpp"

namespace g2d {
namespace Renderer {
  std::vector"Image*" images;

  void add(Image* img) {
    images.push_back(img);
  }

  void render()
  {
  }
} // namespace Renderer
} // namespace g2d
