#include <memory>
#include "Mook.hpp"
#include "Graphics/g2d/Image.hpp"
#include "Graphics/g2d/ImageShader.hpp"
#include <stdio.h>

using namespace otoge2019;

void proc();

int main()
{
  Mook::init();

  proc();
  puts("exit proc");
  
  Mook::finalize();
  return 0;
}

void proc()
{
  Graphics::g2d::Image img("fallback.png", -1, 1);
  Graphics::g2d::ImageShader shader("resources/shaders/g2dShader.vertex.shader", "resources/shaders/g2dShader.fragment.shader");

  Mook::setRenderProcess([&](){
      shader.render(&img);
      });
  Mook::doRenderProcess();

  puts("exiting proc");
}
