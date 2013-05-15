#include "Scene/Scene.h"

using namespace scene;

Scene::Scene() {
  root_ = new Node<float>();
  shader_ = new gl::ShaderProgram("triangle.v.glsl", "triangle.f.glsl");
  nStack_.resize(0);
  tStack_.resize(0);
}

Scene::~Scene() {
  delete root_;
  delete shader_;
}

void Scene::print() {
  root_->print();
}

void Scene::render() {

  glViewport(0, 0, 640, 480);

  shader_->bind();
  Math::Mat4f v = camera_->view().matrix();
  Math::Mat4f p = camera_->perspective();
  shader_->setUniform("v", v);
  shader_->setUniform("p", p);

  nStack_.resize(0);
  tStack_.resize(0);
  nStack_.push_back(root_);
  tStack_.push_back(root_->local());

  while(nStack_.size() > 0) {

    // POP TOPMOST NODE
    Nodef* top = nStack_.pop_back();
    Nodef::Aff3 currentWorldTransform = tStack_.pop_back();
    Math::Mat4f m = currentWorldTransform.matrix();
    shader_->setUniform("m", m);
    if (top->geometry() != nullptr) {
      top->geometry()->draw();
    }

    for (auto i = 0; i < top->nChildren(); i++) {
      Nodef* child = top->child(i);
      nStack_.push_back(child);
      tStack_.push_back(currentWorldTransform * child->local());
    }

  }

}

