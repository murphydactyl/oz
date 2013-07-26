#include "Scene/Scene.h"
#include "Geometry/Geometry.h"
#include "Geometry/Primitives.h"

using namespace scene;
using namespace geom;
using namespace std;


Scene::Scene() {
  root_ = new Node<float>();
  dfltSPTextured_ = new gl::ShaderProgram("TriangleMeshWithTexture.v.glsl", "TriangleMeshWithTexture.f.glsl");
  dfltSPVertexColors_ = new gl::ShaderProgram("triangle.v.glsl", "triangle.f.glsl");
  defaultShader_ = dfltSPVertexColors_;
  nStack_.resize(0);
  tStack_.resize(0);
  cube_ = nullptr;
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

  glViewport(0, 0, 1024, 768);

  shader->bind();
  math::Mat4f v = camera_->view();
  math::Mat4f p = camera_->perspective();
  shader->setUniform("v", v);
  shader->setUniform("p", p);

  nStack_.resize(0);
  nStack_.push_back(root_);
  root_->mWorld.identity();

  while(nStack_.size() > 0) {
    // POP TOP
    Nodef* top = nStack_.pop_back();

    if (top->parent() != nullptr) {
      top->mWorld = top->parent()->mWorld * top->mLocal;
    } else {
      top->mWorld.identity();
    }

    // PUSH TOP'S CHILDREN
    for (auto i = 0; i < top->nChildren(); i++) {
      Nodef* child = top->getChild(i);
      nStack_.push_back(child);
    }
  }

  nStack_.push_back(root_);
  while (nStack_.size() > 0) {
    // POP TOP
    Nodef* top = nStack_.pop_back();
    shader->setUniform("m", top->mWorld);
    if (top->geometry() != nullptr) {
      top->geometry()->draw(shader);
    }
    if (top->hasBone()) {
      drawCube(shader);
    }

    // PUSH TOP'S CHILDREN
    for (auto i = 0; i < top->nChildren(); i++) {
      Nodef* child = top->getChild(i);
      nStack_.push_back(child);
    }
  }
}

void Scene::drawCube(gl::ShaderProgram* shader) {
  if (cube_ == nullptr) {
    cube_ = geom::makeBox(1.0, 1.0, 1.0);
  }
  cube_->draw(dfltSPVertexColors_);
}

