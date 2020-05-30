#include <vector>
#include <iostream>
#include "Graphics/g3d/Line.hpp"
#include "Graphics/g3d/g3dVertexData.hpp"

namespace Graphics {
  namespace g3d {
    std::unique_ptr<LineShader> Line::shader;

    Line::Line()
    {
      glGenBuffers(1, &vbo);

      // インデックスバッファ
      GLuint indices[] = {0, 1, 3, 1, 2, 3};
      // OpenGLのバッファに書き込む
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
      iboSize = sizeof(indices) / sizeof(GLuint);
    }

    Line::~Line()
    {
      glDeleteBuffers(1, &vbo);
    }

    void Line::setupShader(std::string vertex, std::string fragment){
      shader.reset(new LineShader(vertex, fragment));
    }

    void Line::draw(glm::vec3 vertex1, glm::vec3 vertex2, GLfloat dwidth){
      GLfloat width = dwidth / 2;
      // 頂点をバインド
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      // 頂点を作成
      // v1
      // +-------------+
      // |       \     |
      // +-------------+
      auto v1 = vertex1;
      auto v2 = vertex1;
      auto v3 = vertex2;
      auto v4 = vertex2;
      v1.y -= width;
      v2.y += width;
      v3.y += width;
      v4.y -= width;
      glm::vec3 v[] = {
        v1, v2, v3, v4
      };
      std::vector<g3dVertexData> vd;
      for (int i = 0; i < 4; i++) {
        g3dVertexData d;
        d.vertex = v[i];
        vd.push_back(d);
      }
      // 転送
      glBufferData(GL_ARRAY_BUFFER, vd.size() * sizeof(g3dVertexData), &vd[0], GL_DYNAMIC_DRAW);

      // シェーダで描画
      shader->render(this);
    }


    GLuint Line::getVBO(){
      return vbo;
    }

    GLuint Line::getIBO(){
      return ibo;
    }

    GLuint Line::getIBOsize(){
      return iboSize;
    }

    glm::mat4 Line::getModelMatrix(){
      return glm::mat4(1);
    }
  } // namespace g3d
} // namespace Graphics
