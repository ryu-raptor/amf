#include <string>
#include <vector>
#include "Graphics/glHeaders.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/g2d/g2dCompatible.hpp"
#include "Graphics/g2d/g2dVertexData.hpp"
#include "Graphics/g2d/Image.hpp"

inline g2dVertexData pack_data(glm::vec3 v, glm::vec2 u)
{
  g2dVertexData d;
  d.vertex = v;
  d.UV = u;
  return d;
}

namespace Graphics {
namespace g2d {
  void Image::commonInit(std::string filepath)
  {
    // 画像の読み込み
    texture = new Texture(filepath);
    // index buffer
    GLuint indices[] = {0, 1, 2, 0, 2, 3};
    // OpenGLのバッファに書き込む
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

  }

  Image::Image(std::string filepath, GLfloat x, GLfloat y, GLfloat width, GLfloat height)
  {
    commonInit(filepath);
    resize(width, height);
  }

  Image::Image(std::string filepath, GLfloat x, GLfloat y)
  {
    commonInit(filepath);
    // 幅と高さを計算
    GLfloat width = (texture->getWidth() * 2) / WINDOW_WIDTH;
    GLfloat height = (texture->getHeight() * 2) / WINDOW_HEIGHT;

    this->x = x;
    this->y = y;

    resize(width, height);
  }

  Image::~Image()
  {
    delete texture;
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
  }

  void Image::resize(GLfloat width, GLfloat height)
  {
    std::vector<g2dVertexData> v;
    // 頂点を追加する
    // 第1象限から反時計回りに
    v.push_back(pack_data(glm::vec3(x + width, y, 0),          glm::vec2(1.0f, 0.0f)));
    v.push_back(pack_data(glm::vec3(x, y, 0),                  glm::vec2(0.0f, 0.0f)));
    v.push_back(pack_data(glm::vec3(x, y - height, 0),         glm::vec2(0.0f, 1.0f)));
    v.push_back(pack_data(glm::vec3(x + width, y - height, 0), glm::vec2(1.0f, 1.0f)));
    // OpenGLのバッファに書き込む
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(g2dVertexData), &v[0], GL_STATIC_DRAW);
    this->w = width;
    this->h = height;
  }

  GLuint Image::getVBO()
  {
    return vbo;
  }

  GLuint Image::getIBO()
  {
    return ibo;
  }

  GLuint Image::getIBOsize()
  {
    return 6;
  }

  GLuint Image::getTexture()
  {
    return texture->getTexture();
  }
}

} // namespace g2d
