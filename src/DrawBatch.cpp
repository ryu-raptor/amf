#include "glHeaders.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include <stdio.h>
#include <memory>
#include <list>

namespace DrawBatch {
  Camera* camera;
  Scene* scene;

  struct ModelInfo {
    GLuint id;
    Model* model;
  };

  GLuint modelLastID = 0;
  std::list<ModelInfo> models;

  void setCamera(Camera* c)
  {
    camera = c;
  }

  void setScene(Scene* s)
  {
    scene = s;
  }

  GLuint add(Model* m)
  {
    ModelInfo mi;
    mi.id = modelLastID++;
    mi.model = m;
    models.push_back(mi);
    return mi.id;
  }

  void renderWithScene(Scene* withscene)
  {
    withscene->begin();
    camera->begin(withscene);
    for (ModelInfo m : models) {
	  m.model->begin(withscene);
    }
  }

  void render() {
    renderWithScene(scene);
  }

  void remove(GLuint id)
  {
    for (auto i = models.begin(); i != models.end(); i++) {
      if ((*i).id == id) {
		models.erase(i);
		break;
      }
    }
  }
} // namespace DrawBatch
