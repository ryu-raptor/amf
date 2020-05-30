/*
 描画を収めておくレイヤー.
 描画順を指定できる
 */
#ifndef Layer_hpp_included
#define Layer_hpp_included

#include "Graphics/Renderable.hpp"
#include <vector>

namespace Graphics {
  class Layer : public Renderable
  {
    std::vector<Renderable*> children;
  public:
    void begin();

    void add(Renderable* child);

    void insertAt(int at, Renderable* child);
  };
} // namespace Graphics

#endif /* end of include guard */
