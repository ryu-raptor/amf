#pragma once

#include <memory>
#include <string>
#include "Follower.hpp"
#include "Graphics/g3d/Panel.hpp"
#include "Graphics/g3d/DuplicatedPanel.hpp"

namespace otoge2019 {
  struct Sky
  {
    std::unique_ptr<Graphics::g3d::Panel> basePanel;
    std::unique_ptr<Graphics::g3d::DuplicatedPanel> sky[2];

    void loadImage(std::string);
    void render();
  };
} // namespace otoge2019
