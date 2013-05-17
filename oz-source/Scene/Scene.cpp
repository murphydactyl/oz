#include "Scene/Scene.h"

using namespace scene;
using namespace geom;

Scene::Scene() {
  root_ = new Node<float>();
  dfltSPTextured_ = new gl::ShaderProgram("TriangleMeshWithTexture.v.glsl", "TriangleMeshWithTexture.f.glsl");
  dfltSPVertexColors_ = new gl::ShaderProgram("triangle.v.glsl", "triangle.f.glsl");
  defaultShader_ = dfltSPTextured_;
  nStack_.resize(0);
  tStack_.resize(0);
}

Scene::~Scene() {
  delete root_;
  delete defaultShader_;
}

void Scene::print() {
  root_->print();
}

void Scene::render() {
  render(defaultShader_);
}

void Scene::render(gl::ShaderProgram* shader) {

  glViewport(0, 0, 640, 480);

  shader->bind();
  Math::Mat4f v = camera_->view().matrix();
  Math::Mat4f p = camera_->perspective();
  shader->setUniform("v", v);
  shader->setUniform("p", p);

  nStack_.resize(0);
  tStack_.resize(0);
  nStack_.push_back(root_);
  tStack_.push_back(root_->local());

  while(nStack_.size() > 0) {

    // POP TOP
    Nodef* top = nStack_.pop_back();
    Nodef::Aff3 currentWorldTransform = tStack_.pop_back();
    Math::Mat4f m = currentWorldTransform.matrix();
    shader->setUniform("m", m);
    Geometry* g = top->geometry();
    if (g != nullptr) {
      g->draw(shader);
    }

    // PUSH TOP'S CHILDREN
    for (auto i = 0; i < top->nChildren(); i++) {
      Nodef* child = top->child(i);
      nStack_.push_back(child);
      tStack_.push_back(currentWorldTransform * child->local());
    }

  }
}

