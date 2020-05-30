#pragma once
#include <vector>
#include <memory>
#include "Trace.hpp"
#include "Graphics/g3d/Panel.hpp"
#include "Graphics/Texture.hpp"
#include "Pacemaker.hpp"
#include "Graphics/glHeaders.hpp"

namespace otoge2019 {
  class TraceRenderer
  {
    private:
      Graphics::g3d::Panel *tracePanel;
      Graphics::Texture *traceImage;
      GLuint linebuffer;

    public:
      TraceRenderer(std::string traceImagePath);
      ~TraceRenderer();
      void render(std::shared_ptr<std::vector<Trace>>);
      void render(std::shared_ptr<std::vector<std::shared_ptr<Trace>>>);
  };
} // namespace otoge2019
