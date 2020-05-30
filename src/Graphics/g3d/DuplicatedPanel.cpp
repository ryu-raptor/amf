#include "Graphics/g3d/DuplicatedPanel.hpp"

namespace Graphics {
  namespace g3d {
    DuplicatedPanel::DuplicatedPanel(Panel &parent) : Panel(parent)
    {
      alpha = 1.0;
      trans = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f));
    }

    DuplicatedPanel::~DuplicatedPanel()
    {
    }
  } // namespace g3d
} // namespace Graphics
