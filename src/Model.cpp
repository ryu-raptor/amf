#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "Followable.hpp"
#include "Scene.cpp"

using namespace glm;

/*
  Stores Buffer
 */

class Model : virtual public Followable
{
private:
  GLfloat *vertex;
  size_t vertexSize;
  GLfloat *vcolor; // 頂点カラー
  size_t vcolorSize;
  GLfloat *UVMap;
  
  GLuint vertexBuffer;
  GLuint vcolorBuffer;

  vec3 position;
  vec3 rotation;
  vec3 scale;

public:
  Model() {
	// 頂点バッファ
	// create buffer id
	glGenBuffers(1, &vertexBuffer);
	// now we handle buffer, id: vertexbuffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);

	// color
	glGenBuffers(1, &vcolorBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vcolorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, vcolorSize , vcolor, GL_STATIC_DRAW);

	//vecs
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
  }
  
  Model(Model* base) {
	// モデル情報のみコピー
	this->vertex = base->vertex;
	this->vcolor = base->vcolor;
	this->UVMap = base->UVMap;
  }
  
  void setVertex(GLfloat *vertex, size_t size) {
	this->vertex = vertex;
	vertexSize = size;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);
  }

  void setVertexColor(GLfloat *vcolor, size_t size) {
	this->vcolor = vcolor;
	vcolorSize = size;
	glBindBuffer(GL_ARRAY_BUFFER, vcolorBuffer);
	glBufferData(GL_ARRAY_BUFFER, vcolorSize , vcolor, GL_STATIC_DRAW);
  }

  void setUVMap(GLfloat *uv) {
	this->UVMap = uv;
  }

  glm::vec3 getPosition() {
	return position;
  }

  void setCallback(FollowerCallback fcb) {
	this->followerCallBack = fcb;
  }

  void render(Scene* scene) {
	// Mを計算
	// M = Translation * Rotation * Scale
	// Rotation 未実装
	glm::mat4 M = glm::translate(position) * glm::scale(this->scale);
	// VPにMをかける
	glm::mat4 MVP = scene->VP * M;

	// 描画する
	GLuint matrixID = glGetUniformLocation(scene->shaderID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// attributes
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
						  0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
						  3, // size
						  GL_FLOAT, // type
						  GL_FALSE, // normalized?
						  0, // stride
						  (void*) 0 // array buffer offset
						  );

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vcolorBuffer);
	glVertexAttribPointer(
						  1,
						  3,
						  GL_FLOAT,
						  GL_FALSE,
						  0,
						  (void*) 0
						  );
	
	// draw
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
  }
};
