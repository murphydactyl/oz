#include "Scene/Scene.h"
#include "Geometry/Geometry.h"
#include "Geometry/Primitives.h"

using namespace scene;
using namespace geom;
using namespace std;

Scene::Scene() {
  root_ = new Node<float>();
  nStack_.resize(0);
  rNodes_.resize(0);
  cube_ = nullptr;
  lines_ = new geom::Wire();
  lineShader_ = new gl::ShaderProgram("line.v.glsl", "line.f.glsl");
  lineNode_ = new Nodef("Hierarchy Lines");
}

Scene::~Scene() {
  delete root_;
}

void Scene::print() {
  root_->print();
}

gl::ShaderProgram* Scene::shader() {
  return shader_;
}

void Scene::setShader(gl::ShaderProgram* newShader) {
  shader_ = newShader;
}


void Scene::render(int x, int y, int width, int height) {
  updatePerNodeWorldTransform();
  glViewport(x, y, width, height);
  renderRecursively();
  renderHierarchy();
}

void Scene::updatePerNodeWorldTransform() {
  nStack_.resize(0);
  nStack_.push_back(root_);
  root_->mWorld = root_->mLocal;
  rNodes_.resize(0);
  while(nStack_.size() > 0) {
    // POP TOP
    Nodef* top = nStack_.pop_back();
    if (top->parent() != nullptr) {
      top->mWorld = top->parent()->mWorld * top->mLocal;
      if (top->hasBone()) {
        top->bone()->final = top->mWorld * top->bone()->offset;
      }
    } else {
      top->mWorld.identity();
    }

    // PUSH TOP'S CHILDREN
    for (auto i = 0; i < top->nChildren(); i++) {
      Nodef* child = top->getChild(i);
      nStack_.push_back(child);
    }
    rNodes_.push_back(top);
  }
}

void Scene::renderRecursively() {
  shader()->setUniform("v", camera_->view());
  shader()->setUniform("p", camera_->perspective());

  for (auto i = 0; i < rNodes_.size(); i++) {
    Nodef* node = rNodes_[i];
    shader()->setUniform("m", node->mWorld);
    if (node->geometry() != nullptr) {
      node->geometry()->draw(shader());
    }
  }
}

void Scene::renderHierarchy() {
  lineShader_->setUniform("v", camera_->view());
  lineShader_->setUniform("p", camera_->perspective());
  lines_->clear();
  math::Mat4f identity = math::Mat4f::Identity();
  shader()->setUniform("m", identity);
  for (auto i = 0; i < rNodes_.size(); i++) {
    Nodef* n = rNodes_[i];
    Nodef* p = n->parent();
    if (p != nullptr) {
      lines_->addPosition(n->mWorld(0,3), n->mWorld(1,3), n->mWorld(2,3));
      lines_->addPosition(p->mWorld(0,3), p->mWorld(1,3), p->mWorld(2,3));
      lines_->addColor(0.5, 0.5, 0.5);
      lines_->addColor(0, 1, 0);
    }
  }
  lines_->draw(lineShader_);
}
