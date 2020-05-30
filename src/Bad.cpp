#include "Bad.hpp"

#include "Bad.hpp"
#include <iostream>

namespace otoge2019 {
  std::unique_ptr<Graphics::g3d::Panel> Bad::source;

  void Bad::setupGraphic(ResourceFiler &rf)
  {
    auto dir = rf.get("Effect", "ResourceDirectory");
    auto path = dir + "/" + rf.get("Effect.Bad", "Graphic");
    std::cout << path << "\n";
    source.reset(new Graphics::g3d::Panel(path, 0.01));
  }

  Bad::Bad(GLfloat x, GLfloat y)
  {
    panel.reset(new Graphics::g3d::DuplicatedPanel(*(source.get())));
    panel->setPosition(x, y, 0);
    alpha = 1;
  }

  // virtuals
  void Bad::render()
  {
    debug();
    panel->renderWithDefault();
  }
} // namespace otoge2019
