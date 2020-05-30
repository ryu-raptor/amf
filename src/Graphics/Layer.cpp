#include "Graphics/Layer.hpp"

namespace Graphics {
  
void Layer::begin()
{
  // childrenの描画を行う
  for (auto child : children) {
    child->begin();
  }
}

void Layer::add(Renderable* child)
{
  children.push_back(child);
}

void Layer::insertAt(int at, Renderable* child)
{
  // 位置を指定して挿入
  children.push_back(child);
}

} // namespace Graphics
