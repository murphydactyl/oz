#include "Geometry/TriangleMesh.h"
#include "Math/Math.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"
#include "GL/ElementBuffer.h"
#include "GL/ShaderProgram.h"

using namespace geom;
using namespace std;

template <element_t E>
Mesh<E>::Mesh() {
  vao_ = new gl::VertexArrayObject();
  vbo_ = new gl::VertexBuffer();
  ebo_ = new gl::ElementBuffer<uint16_t>();

  nVerts_ = 0;
  nFaces_ = 0;

  tex_ = nullptr;
}

template <element_t E>
Mesh<E>::~Mesh() {
  delete vao_;
  delete vbo_;
  delete ebo_;
}

template <element_t E>
gl::ElementBuffer<uint16_t>* Mesh<E>::ebo() {
  return ebo_;
}

template <element_t E>
uint64_t Mesh<E>::nFaces()
{
  return nFaces_;
}

template <element_t E>
uint64_t Mesh<E>::nVerts()
{
  return nVerts_;
}

template <element_t E>
void Mesh<E>::nFaces(uint64_t nFaces)
{
  nFaces_ = nFaces;
}

template <element_t E>
void Mesh<E>::nVerts(uint64_t nVerts) {
  nVerts_ = nVerts;
}

template <element_t E>
element_t Mesh<E>::elementType() {
  return elementType_;
}

template <element_t E>
positions_t& Mesh<E>::positions() {
  return positions_;
}

template <element_t E>
colors_t& Mesh<E>::colors() {
  return colors_;
}

template <element_t E>
normals_t& Mesh<E>::normals() {
  return normals_;
}

template <element_t E>
faces_t& Mesh<E>::faces() {
  return faces_;
}

template <element_t E>
texcoord_t& Mesh<E>::texcoords() {
  return texcoords_;
}

template <element_t E>
boneweights_t& Mesh<E>::boneweights() {
  return boneweights_;
}

template <element_t E>
boneids_t& Mesh<E>::boneids() {
  return boneids_;
}

template <element_t E>
void Mesh<E>::attachTexture(gl::Texture *tex)
{
  tex_ = tex;
}

template <element_t E>
bool Mesh<E>::hasTexture()
{
  return tex_ != nullptr;
}

template <element_t E>
bool Mesh<E>::hasBones()
{
  return !bones_.isEmpty();
}

template <element_t E>
bonelist_t& Mesh<E>::bones()
{
  return bones_;
}

template <element_t E>
void Mesh<E>::draw(gl::ShaderProgram* shader) {
  if (hasTexture()) {
    shader->setUniform("tex", 0);
  }
  vao_->bind();
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  ebo_->bind();
  switch (E) {
    case GL_TRIANGLES:
    case GL_TRIANGLE_STRIP:
      glDrawElements(E, 3 * nFaces_, GL_UNSIGNED_SHORT, (void*)(nullptr));
      break;
  }
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

/**
 EXPLICIT INSTANTIATIONS
**/
namespace geom {
  template class Mesh<TRIANGLE>;
  template class Mesh<TRIANGLE_STRIP>;
}
