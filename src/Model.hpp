#ifndef Model_hpp
#define Model_hpp

#include <string>
#include <vector>
#include <memory>
#include <assimp/types.h>
#include <assimp/scene.h>
#include "glHeaders.hpp"
#include "Scene.hpp"
#include "Followable.hpp"
#include "Texture.hpp"

class Model : public virtual Followable
{
private:

  struct Vertex {
	glm::vec3 vertex;
	glm::vec3 normal;
	glm::vec2 uv;
  };

  struct Mesh {
	Mesh();

	// OpenGLのバッファを解放する
	~Mesh();

	void finalize();

	// OpenGLのバッファに書き込む
	void initialize(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indeces);
	GLuint vbo; // 頂点バッファ
	GLuint ibo; // インデックスバッファ
	GLuint numIndeces; // インデックスの数(インデックスバッファのサイズ)
	GLubyte materialIndex; // はっつけるマテリアルのインデックス
  };

  GLuint modelID; // DrawBatchから返される自身のID
  std::vector<Mesh> meshs;
  std::vector<std::unique_ptr<Texture> > textures;

  glm::vec3 position;
  glm::mat4 positioning;
  glm::mat4 rotating;
  glm::mat4 scaling;
  glm::mat4 worldMatrix;
  
  // メッシュ/マテリアルを取り出す
  void initFromScene(std::string modelPath, const aiScene* pScene);
  void initMaterials(std::string modelPath, const aiScene* pScene);
  // aiMeshからデータを抜き出す
  void initMesh(unsigned int index, const aiMesh* pMesh);
  void recomputeWorldMatrix();
  
public:
  Model(std::string modelPath);
  ~Model();

  // あんまり意味がない
  // Modelは座標変換をしない. Entityなどがそれをする. 同じModelを参照すればモデルの複製が成立する
  Model(const Model* basemodel);
  // 描画
  void render(GLuint programID, glm::mat4 MVP);
  // DrawBatchが利用する
  void begin(Scene*);

  glm::vec3 getPosition();
  void setCallback(Follower*);
  // 呼ばれる際にワールド行列を再計算する
  void setPosition(glm::vec3 position); // 位置を絶対座標で指定
  void setRotation(GLfloat angle, glm::vec3 axrote); // axroteで回転軸を設定(degee)
  void appendRotation(GLfloat angle, glm::vec3 axrote); // 回転を追加
  void setDirection(glm::vec3 direction); // その物体を向けたい方向の軸を設定. (X軸がデフォルト)
  void setScale(glm::vec3 axscale); // 各軸の倍率を設定

  void finalize();
};

#endif /* end of include guard */

