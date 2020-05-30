#include <cassert>
#include "Graphics/g3d/LineShader.hpp"
#include "Graphics/g3d/TexturedShader.hpp"
#include "Graphics/g3d/g3dVertexData.hpp"
#include "Graphics/ShaderLoader.hpp"

namespace Graphics {
  namespace g3d {
    LineShader::LineShader(std::string vertex, std::string fragment)
    {
      this->programID = loadShaders(vertex.c_str(), fragment.c_str());
      mvpID = glGetUniformLocation(programID, "MVP");
    }

    void LineShader::render(g3dCompatible* object)
    {
      bool showerr = false;
      // シェーダを使用開始する
      glUseProgram(programID);
      GLenum err;
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("using program: %x\n", err);
      }
      // 頂点情報をバッファへ転送
      glBindBuffer(GL_ARRAY_BUFFER, object->getVBO());
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("bind vbo: %x\n", err);
      }

      // 変換行列を転送
      auto mvp = scene->getVP();// * object->getModelMatrix();
      //auto mvp = object->getModelMatrix();
      //glm::mat4 mvp(1);
      glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("trans matrix: %x\n", err);
      }

      // アトリビュートを設定する
      // attrib 0: 頂点
      // (attrib, count, type, isNormalized, stride, pointer)
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(g3dVertexData), (GLvoid*) offsetof(g3dVertexData, vertex));

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->getIBO());
      glDrawElements(GL_TRIANGLES, object->getIBOsize(), GL_UNSIGNED_INT, (GLvoid*) 0);
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("draw buffer: %x\n", err);
      }

      //glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);
    }

    void LineShader::setScene(Scene* scene)
    {
      this->scene = scene;
    }
  } // namespace g3d
} // namespace Graphics
