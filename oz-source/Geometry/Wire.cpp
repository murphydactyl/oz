#include "Wire.h"
#include "Math/Math.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"
#include "GL/ElementBuffer.h"
#include "GL/ShaderProgram.h"
using namespace geom;
using namespace std;

Wire::Wire() {
  elementType_ = geom::element_t::LINE;
  vao_ = new gl::VertexArrayObject();
  vbo_ = new gl::VertexBuffer();
  vao()->bind();
  vbo()->bind();
  vbo()->setVertexType(gl::ATTRIB_V_POSITION | gl::ATTRIB_V_COLOR);
  vao()->unbind();
  vbo()->unbind();
  position_ = new std::vector<position_t>();
  color_ = new std::vector<color_t>();
}

void Wire::nVerts(uint64_t newSize) {
  position_->reserve(newSize);
  color_->reserve(newSize);
}

uint64_t Wire::nVerts() {
  if (position_->size() >= color_->size()) {
    return color_->size();
  }
  return position_->size();
}

void Wire::addPosition(float x, float y, float z, float w) {
  position_t v(x, y, z, w);
  position_->push_back(v);
  bNeedSync_ = true;
}

void Wire::addColor(float r, float g, float b, float a) {
  color_t v(r, g, b, a);
  color_->push_back(v);
  bNeedSync_ = true;
}

void Wire::clear() {
  color_->resize(0);
  position_->resize(0);
  bNeedSync_ = true;
}

void Wire::sync() {
  cout << "Syncing wire data...";
  vao()->bind();
  vbo()->bind();
  vbo()->allocVertexMemoryOnGPU(nVerts());
  vbo()->copyVertDataToGPU((float*)color_->data(), nVerts(), gl::vcolor);
  vbo()->copyVertDataToGPU((float*)position_->data(), nVerts(), gl::vposition);
  vbo()->printBuffer(nVerts());
  vao()->unbind();
  bNeedSync_ = false;
  cout << "Done." << endl;
}

void Wire::draw(gl::ShaderProgram* shader) {
  if (bNeedSync_) {
    sync();
  }
  vao_->bind();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(elementType_, 0, nVerts());
  vao_->unbind();
}
