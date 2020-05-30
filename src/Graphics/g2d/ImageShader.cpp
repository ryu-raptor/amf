#include "Graphics/g2d/ImageShader.hpp"
#include "Graphics/ShaderLoader.hpp"
#include "Graphics/g2d/g2dVertexData.hpp"
#ifdef DEBUG
#include <stdio.h>
#endif

namespace Graphics {
  namespace g2d {
    ImageShader::ImageShader(std::string vertex, std::string fragment)
    {
      this->programID = loadShaders(vertex.c_str(), fragment.c_str());
      textureSamplerID = glGetUniformLocation(programID, "textureSampler");

#ifdef DEBUG
      GLfloat v[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 0.0f,  1.0f, 0.0f,
      };

      GLfloat uv[] = {
	1, 1,
	0, 1,
	0, 0,
	1, 0
      };
      // OpenGLのバッファに書き込む
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(v) * sizeof(GLfloat), v, GL_STATIC_DRAW);
      glGenBuffers(1, &uvbo);
      glBindBuffer(GL_ARRAY_BUFFER, uvbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(uv) * sizeof(GLfloat), v, GL_STATIC_DRAW);

      GLuint ind[] = {
	0, 1, 2,
	0, 2, 3
      };
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind) * sizeof(GLuint), ind, GL_STATIC_DRAW);
#endif
    }

    // オブジェクトからデータを引っ張って描画をする
    void ImageShader::render(g2dCompatible* object)
    {
      bool showerr = true;
      GLenum err;
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("some error occured: %x\n", err);
      }
      // シェーダを使用開始する
      glUseProgram(programID);
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("using program: %x\n", err);
      }
      // 頂点情報をバッファへ転送
      glBindBuffer(GL_ARRAY_BUFFER, object->getVBO());
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("bind vbo: %x\n", err);
      }

      // アトリビュートを設定する
      // attrib 0: 頂点
      // (attrib, count, type, isNormalized, stride, pointer)
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(g2dVertexData), (GLvoid*) offsetof(g2dVertexData, vertex));

      // attrib 1: UV coordinates
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(g2dVertexData), (GLvoid*) offsetof(g2dVertexData, UV));
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("attrib ptr: %x\n", err);
      }

      // texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, object->getTexture());
      // set texture0 to uniform
      glUniform1i(this->textureSamplerID, 0);
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("bind texture: %x\n", err);
      }

      
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->getIBO());
      glDrawElements(GL_TRIANGLES, object->getIBOsize(), GL_UNSIGNED_INT, (GLvoid*) 0);
      if (showerr && (err = glGetError()) != GL_NO_ERROR) {
        printf("draw buffer: %x\n", err);
      }

      //glDrawArrays(GL_TRIANGLES, 0, 3);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
    }
  } // namespace g2d
} // namespace Graphics
