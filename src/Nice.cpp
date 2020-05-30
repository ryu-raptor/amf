#include "Nice.hpp"
#include "Graphics/g3d/Panel.hpp"
#include <iostream>

namespace otoge2019 {
  std::unique_ptr<Graphics::g3d::Panel> Nice::source;

  void Nice::setupGraphic(ResourceFiler &rf)
  {
    auto dir = rf.get("Effect", "ResourceDirectory");
    auto path = dir + "/" + rf.get("Effect.Nice", "Graphic");
    std::cout << path << "\n";
    source.reset(new Graphics::g3d::Panel(path, 0.01));
  }

  Nice::Nice(GLfloat x, GLfloat y)
  {
    panel.reset(new Graphics::g3d::DuplicatedPanel(*(source.get())));
    panel->setPosition(x, y, 0);
    alpha = 1;
  }

  // virtuals
  void Nice::render()
  {
    debug();
    panel->renderWithDefault();
  }
} // namespace otoge2019
