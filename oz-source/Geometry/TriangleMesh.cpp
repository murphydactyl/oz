#include "../Math/Math.h"
#include "Geometry/TriangleMesh.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"
#include "GL/ElementBuffer.h"
#include "GL/ShaderProgram.h"

using namespace geom;
using namespace std;

template <element_t E>
TriangleMesh<E>::TriangleMesh() {
  vao_ = new gl::VertexArrayObject();
  vbo_ = new gl::VertexBuffer();
  ebo_ = new gl::ElementBuffer<uint16_t>();

  nVerts_ = 0;
  nFaces_ = 0;

  tex_ = nullptr;
}

template <element_t E>
TriangleMesh<E>::~TriangleMesh() {
  delete vao_;
  delete vbo_;
  delete ebo_;
}

template <element_t E>
gl::ElementBuffer<uint16_t>* TriangleMesh<E>::ebo() {
  return ebo_;
}

template <element_t E>
uint64_t TriangleMesh<E>::nFaces()
{
  return nFaces_;
}

template <element_t E>
uint64_t TriangleMesh<E>::nVerts()
{
  return nVerts_;
}

template <element_t E>
void TriangleMesh<E>::nFaces(uint64_t nFaces)
{
  nFaces_ = nFaces;
}

template <element_t E>
void TriangleMesh<E>::nVerts(uint64_t nVerts) {
  nVerts_ = nVerts;
}

template <element_t E>
element_t TriangleMesh<E>::elementType() {
  return elementType_;
}

template <element_t E>
positions_t& TriangleMesh<E>::positions() {
  return positions_;
}

template <element_t E>
colors_t& TriangleMesh<E>::colors() {
  return colors_;
}

template <element_t E>
normals_t& TriangleMesh<E>::normals() {
  return normals_;
}

template <element_t E>
faces_t& TriangleMesh<E>::faces() {
  return faces_;
}

template <element_t E>
texcoord_t& TriangleMesh<E>::texcoords() {
  return texcoords_;
}

template <element_t E>
void TriangleMesh<E>::attachTexture(gl::Texture *tex)
{
  tex_ = tex;
}

template <element_t E>
bool TriangleMesh<E>::hasTexture()
{
  return tex_ != nullptr;
}



template <element_t E>
void TriangleMesh<E>::draw(gl::ShaderProgram* shader) {
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
  template class TriangleMesh<TRIANGLE>;
  template class TriangleMesh<TRIANGLE_STRIP>;
}
