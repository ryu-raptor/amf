#include "Sky.hpp"

namespace otoge2019 {
  void Sky::loadImage(std::string path)
  {
    basePanel.reset(new Graphics::g3d::Panel(path, 0.8));
    basePanel->setPosition(0, 100, -50);
    
    sky[0].reset(new Graphics::g3d::DuplicatedPanel(*(basePanel.get())));
    sky[0]->setPosition(0 + basePanel->getSize().x, 100, -50);
    
  }

  void Sky::render()
  {
    basePanel->renderWithDefault();
    sky[0]->renderWithDefault();
  }
} // namespace otoge2019
