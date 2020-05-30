#ifndef g2d_ShaderBase_hpp_included
#define g2d_ShaderBase_hpp_included

#include "glHeaders.hpp"

namespace Graphics {
namespace g2d {
  class ShaderBase
  {
    // 2d用のシェーダーのベースシェーダ
    // 頂点とUVを渡せて, textureSamplerが使える
    GLuint shaderID; 
    GLuint textureSamplerID;

  public:
    ShaderBase(std::string vshaderpath, std::string fshaderpath);

    ~ShaderBase();

    // アトリビュートにセットする.
    void setBufferObject(GLuint);
    void setVertices(size_t stride, GLvoid*);
    void setUVs(size_t stride, GLvoid*);

    // テクスチャをセットする
    void setTexture(GLuint texid);

    // 描画をする
    void draw(GLuint ibo);
  };
} // namespace g2d
} // namespace Graphics
#endif /* end of include guard */
