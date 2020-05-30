#pragma once

#include "Graphics/g2d/g2dCompatible.hpp"
#include "Graphics/Texture.hpp"
#include "globals.hpp"

namespace Graphics {
namespace g2d
{
  class Image : public g2dCompatible {
  private:
    Texture* texture;
    static GLuint programID;
    GLuint vbo;
    GLuint ibo;

    GLfloat x, y, w, h;

    void commonInit(std::string filepath);
  public:
    // 単位はOpenGL座標系
    Image(std::string filepath, GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    // 画像のサイズを算出する
    Image(std::string filepath, GLfloat x, GLfloat y);
    Image(Image*, GLfloat x, GLfloat y);

    ~Image();

    // OpenGL座標系でリサイズ
    void resize(GLfloat width, GLfloat height);

    // 位置を変更
    void setPosition(GLfloat x, GLfloat y);

    GLuint getVBO();

    GLuint getIBO();

    GLuint getIBOsize();

    GLuint getTexture();
  };
} // namespace Graphics
}
