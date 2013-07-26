#include "Geometry/TriangleMesh.h"
#include "Math/Math.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"
#include "GL/ElementBuffer.h"
#include "GL/ShaderProgram.h"

using namespace geom;
using namespace std;


typedef struct point {
    float position[4];
    float color[4];
} point_t;

Mesh::Mesh() : Mesh(TRIANGLE){}

Mesh::Mesh(element_t e){
  elementType_ = e;

  vao_ = new gl::VertexArrayObject();
  vbo_ = new gl::VertexBuffer();
  ebo_ = new gl::ElementBuffer<uint16_t>();

  nVerts_ = 0;
  nFaces_ = 0;
  tex_ = nullptr;
}

Mesh::~Mesh() {
  delete vao_;
  delete vbo_;
  delete ebo_;
}

gl::ElementBuffer<uint16_t>* Mesh::ebo() {
  return ebo_;
}

uint64_t Mesh::nFaces()
{
  return nFaces_;
}

uint64_t Mesh::nVerts()
{
  return nVerts_;
}

void Mesh::nFaces(uint64_t nFaces)
{
  nFaces_ = nFaces;
}

void Mesh::nVerts(uint64_t nVerts) {
  nVerts_ = nVerts;
}

positions_t& Mesh::positions() {
  return positions_;
}

colors_t& Mesh::colors() {
  return colors_;
}

normals_t& Mesh::normals() {
  return normals_;
}

faces_t& Mesh::faces() {
  return faces_;
}

texcoord_t& Mesh::texcoords() {
  return texcoords_;
}

boneweights_t& Mesh::boneweights() {
  return boneweights_;
}

boneids_t& Mesh::boneids() {
  return boneids_;
}

void Mesh::attachTexture(gl::Texture *tex)
{
  tex_ = tex;
}

bool Mesh::hasTexture()
{
  return tex_ != nullptr;
}

bool Mesh::hasBones()
{
  return !bones_.isEmpty();
}

bonelist_t& Mesh::bones()
{
  return bones_;
}

void Mesh::draw(gl::ShaderProgram* shader) {
  if (hasTexture()) {
    shader->setUniform("tex", 0);
  }

  //  cout << "Position of v_position in shader is "
  //       << glGetAttribLocation(shader->glName(), "v_position") << endl;
  //  cout << "Position of v_color in shader is "
  //       << glGetAttribLocation(shader->glName(), "v_color") << endl;

  vao_->bind();
  //  glPointSize(10.0f);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  ebo_->bind();

  //  glDrawArrays(GL_POINTS, 0, 4);
  glDrawElements(elementType_, 3 * nFaces_, GL_UNSIGNED_SHORT, (void*)(nullptr));
  ebo_->unbind();
  vao_->unbind();
}

//void Geometry::drawArray() {
//  switch (primitiveType_) {
//    case GL_TRIANGLES:
//      glDrawArrays(GL_TRIANGLES, 0, nVerts());
//      break;
//    case GL_TRIANGLE_STRIP:
//      glDrawArrays(GL_TRIANGLE_STRIP, 0, nVerts());
//      break;
//  }
//}
