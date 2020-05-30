#include "Graphics/g3d/Panel.hpp"
#include "Graphics/g3d/g3dVertexData.hpp"
#include <vector>
#include <iostream>

namespace Graphics {
  namespace g3d {
    
    glm::vec2 Panel::getSize()
    {
      return realSize;
    }
    

    void Panel::setupShader(std::string vertex, std::string fragment)
    {
      defaultShader.reset(new TexturedShader(vertex, fragment));
    }

    void Panel::setupShader(std::shared_ptr<TexturedShader> texturedShader)
    {
      defaultShader = texturedShader;
    }

    /// あえて何もしていない. 派生クラスが何とかするため
    Panel::Panel()
    {
    }

    /// シャローコピーコンストラクタ
    /// 派生クラスが使うように
    Panel::Panel(Panel &parent)
    {
      texture = parent.texture;
      vbo = parent.vbo;
      ibo = parent.ibo;
      iboSize = parent.iboSize;
      scale = parent.scale;
      trans = parent.trans;
      rotate = parent.rotate;
      alpha = parent.alpha;
      colorModulation = glm::vec3(0, 0, 0);
      // コピー先はテクスチャを保持しない
      ownedTexture = false;
    }

    Panel::Panel(std::string path, GLfloat scale)
    {
      auto texture = new Texture(path);
      auto width = texture->getWidth();
      auto height = texture->getHeight();
      commonConstructor(texture, texture->getWidth(), texture->getHeight(), Rect(0, 0, width, height), scale);
      ownedTexture = true;
    }

    Panel::Panel(Texture* texture, GLfloat scale)
    {
      commonConstructor(texture, texture->getWidth(), texture->getHeight(), Rect(0, 0, texture->getWidth(), texture->getHeight()), scale);
      ownedTexture = false;
    }

    Panel::Panel(Texture* texture, GLfloat width, GLfloat height) : Panel::Panel(texture, width, height, Rect(0, 0, texture->getWidth(), texture->getHeight()))
    {
      ownedTexture = false;
    }

    void Panel::commonConstructor(Texture* texture, GLfloat width, GLfloat height, Rect rect, GLfloat scale = 1)
    {
      // 大きさ１の正方形を作る
      glm::vec3 vertices[] = {
        glm::vec3(0.5f, 0.5f, 0), glm::vec3(-0.5f, 0.5f, 0), glm::vec3(-0.5f, -0.5f, 0), glm::vec3(0.5f, -0.5f, 0)
      };
      // UVを設定する
      auto theight = texture->getHeight();
      auto twidth = texture->getWidth();
      glm::vec2 uvs[] = {
        glm::vec2((rect.x + rect.width) / twidth, rect.y / theight),
        glm::vec2(rect.x / twidth, rect.y / theight),
        glm::vec2(rect.x / twidth, (rect.y + rect.height) / theight),
        glm::vec2((rect.x + rect.width) / twidth, (rect.y + rect.height) / theight),
      };
      // g3dオブジェクトを生成
      std::vector<g3dVertexData> v;
      for (int i = 0; i < sizeof(vertices); i++) {
        g3dVertexData p;
        p.vertex = vertices[i];
        p.UV = uvs[i];
        v.push_back(p);
      }
      // openglバッファを生成
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(g3dVertexData), &v[0], GL_STATIC_DRAW);
      // インデックスバッファ
      GLuint indices[] = {0, 1, 2, 0, 2, 3};
      // OpenGLのバッファに書き込む
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
      iboSize = sizeof(indices) / sizeof(GLuint);

      this->realSize = glm::vec2(width * scale, height * scale);
      this->texture = texture;
      // 拡大縮小行列を作成
      this->scale = glm::scale(glm::vec3(width * scale, height * scale, 1.0f));
      // 平行移動行列を作成
      trans = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f));
      // 回転行列を作成
      rotate = glm::mat4(1);

      // 不透明度を1にする
      alpha = 1.0;
      colorModulation = glm::vec3(0, 0, 0);
    }

    Panel::Panel(Texture* texture, GLfloat width, GLfloat height, Rect rect)
    {
      commonConstructor(texture, width, height, rect);
    }

    Panel::~Panel()
    {
      if (ownedTexture) {
        delete texture;
      }
      glDeleteBuffers(1, &vbo);
      glDeleteBuffers(1, &ibo);
    }

    void Panel::setAlpha(double alpha)
    {
      this->alpha = alpha;
    }

    void Panel::setPosition(GLfloat x, GLfloat y, GLfloat z)
    {
      trans = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
    }

    void Panel::setRotation(GLfloat radian, glm::vec3 axis)
    {
      GLfloat degree = radian * 180 / 3.141592653589793238;
      rotate = glm::rotate(degree, axis);
    }

    void Panel::renderWithDefault()
    {
      defaultShader->render(this);
    }

    GLuint Panel::getVBO()
    {
      return vbo;
    }

    GLuint Panel::getIBO()
    {
      return ibo;
    }

    GLuint Panel::getIBOsize()
    {
      return iboSize;
    }

    GLuint Panel::getTexture()
    {
      return texture->getTexture();
    }

    glm::mat4 Panel::getModelMatrix()
    {
      return trans * rotate * scale;
    }

    GLfloat Panel::getAlpha()
    {
      return (GLfloat) alpha;
    }

    void Panel::setColorModulation(double r, double g, double b)
    {
      colorModulation = glm::vec3(r, g, b);
    }

    glm::vec3 Panel::getColorModulation()
    {
      return colorModulation;
    }

    std::shared_ptr<TexturedShader> Panel::defaultShader;
  } // namespace g3d
} // namespace Graphics
