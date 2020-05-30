#include "TraceRenderer.hpp"
#include "Graphics/g3d/Line.hpp"
#include <iostream>

namespace otoge2019 {
  TraceRenderer::TraceRenderer(std::string traceImagePath)
  {
    traceImage = new Graphics::Texture(traceImagePath);
    tracePanel = new Graphics::g3d::Panel(traceImage, 0.01);
    glGenBuffers(1, &linebuffer);
  }

  TraceRenderer::~TraceRenderer()
  {
    delete tracePanel;
    delete traceImage;
    glDeleteBuffers(1, &linebuffer);
  }

  void TraceRenderer::render(std::shared_ptr<std::vector<std::shared_ptr<Trace>>> traces)
  {
    GLfloat lx = -10000;
    GLfloat ly = 0;
    Graphics::g3d::Line line;

    // 線の描画
    for (auto trace : *traces) {
      auto x = trace->position;
      auto y = trace->height;
      line.draw(glm::vec3(lx, ly, 0.0f), glm::vec3(x, y, 0.0f), 1.0f);
      lx = x;
      ly = y;
    }

    // トレース点の描画
    for (auto trace : *traces) {
      auto x = trace->position;
      auto y = trace->height;
      tracePanel->setPosition(x, y, 0);
      tracePanel->renderWithDefault();
    }
  }

  void TraceRenderer::render(std::shared_ptr<std::vector<Trace>> traces)
  {
    GLfloat lx = -10000;
    GLfloat ly = 0;
    Graphics::g3d::Line line;

    for (auto trace : *traces) {
      auto x = (float)trace.position;
      auto y = (float)trace.height;
      line.draw(glm::vec3(lx, ly, 0.0f), glm::vec3(x, y, 0.0f), 1.0f);
      //auto x = pacemaker.getPosition(trace.seconds);
      tracePanel->setPosition(trace.position, trace.height, 0);
      Graphics::g3d::Panel::defaultShader->render(tracePanel);
      lx = x;
      ly = y;
    }
  }
} // namespace otoge2019
