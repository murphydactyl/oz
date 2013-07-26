#include "Geometry/Primitives.h"
#include "Geometry/Geometry.h"
#include "Geometry/TriangleMesh.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"
#include "GL/ElementBuffer.h"

using namespace geom;

Geometry* geom::makeBox(float ux, float uy, float uz) {

  auto g = new Mesh(TRIANGLE);

  float points[] = {
    -ux, -uy, +uz, 1,
    +ux, -uy, +uz, 1,
    +ux, +uy, +uz, 1,
    -ux, +uy, +uz, 1,

    -ux, -uy, -uz, 1,
    +ux, -uy, -uz, 1,
    +ux, +uy, -uz, 1,
    -ux, +uy, -uz, 1,

    +ux, -uy, +uz, 1,
    +ux, -uy, -uz, 1,
    +ux, +uy, -uz, 1,
    +ux, +uy, +uz, 1,

    -ux, -uy, +uz, 1,
    -ux, -uy, -uz, 1,
    -ux, +uy, -uz, 1,
    -ux, +uy, +uz, 1,

    -ux, +uy, +uz, 1,
    +ux, +uy, +uz, 1,
    +ux, +uy, -uz, 1,
    -ux, +uy, -uz, 1,

    -ux, -uy, +uz, 1,   // 20
    +ux, -uy, +uz, 1,   // 21
    +ux, -uy, -uz, 1,   // 22
    -ux, -uy, -uz, 1   // 23
  };

  float a = 0.5;
  float colors[] = {
    1, 1, 1, a,
    1, 1, 1, a,
    1, 1, 1, a,
    1, 1, 1, a,

    1, 0, 0, a,
    1, 0, 0, a,
    1, 0, 0, a,
    1, 0, 0, a,

    0, 1, 0, a,
    0, 1, 0, a,
    0, 1, 0, a,
    0, 1, 0, a,

    0, 0, 1, a,
    0, 0, 1, a,
    0, 0, 1, a,
    0, 0, 1, a,

    0, 1, 1, a,
    0, 1, 1, a,
    0, 1, 1, a,
    0, 1, 1, a,

    0, 0, 0, a,
    0, 0, 0, a,
    0, 0, 0, a,
    0, 0, 0, a,
  };

  uint16_t faces[] = {
    0,   1,    2,
    2,   3,    0,
    5,   4,    7,
    7,   6,    5,
    8,   9,    10,
    8,   10,   11,
    12,   15,   13,
    15,   14,   13,
    16,   17,   18,
    16,   18,   19,
    23,   21,   20,
    23,   22,   21,
  };

  g->nVerts(24);
  g->vao()->bind();
  g->vbo()->bind();
  g->vbo()->setVertexType(gl::ATTRIB_V_POSITION |
                          gl::ATTRIB_V_COLOR);
  g->vbo()->allocVertexMemoryOnGPU(g->nVerts());
  g->vbo()->copyVertDataToGPU(colors, g->nVerts(), gl::vcolor);
  g->vbo()->copyVertDataToGPU(points, g->nVerts(), gl::vposition);
  g->vbo()->printBuffer(g->nVerts());
  g->vao()->unbind();

  g->nFaces(12);
  g->ebo()->bind();
  g->ebo()->reserveNBytesOnGPU(g->nFaces() * 3 * 2);
  g->ebo()->copy2GPU(faces, g->nFaces(), 3);
  g->ebo()->unbind();

  return g;
}

Geometry* geom::makeQuad(float unit)
{
  auto g = new Mesh(TRIANGLE);
  float s = unit;
  float points[] = {
    -s, -s, 0, 1,
    +s ,-s, 0, 1,
    -s, +s, 0, 1,
    +s, +s, 0, 1
  };

  float colors[] = {
    1, 0, 0, 1,
    0, 1, 0, 1,
    0, 0, 1, 1,
    1, 1, 1, 1
  };

  float normals[] = {
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1,
    0, 0, 1, 1
  };

  float texcoords[] = {
    0, 1,
    1, 1,
    0, 0,
    1, 0
  };

  uint16_t faces[] {
    0, 1, 2,
    2, 1, 3
  };

  g->nVerts(4);
  g->vao()->bind();
  g->vbo()->bind();
  g->vbo()->setVertexType(gl::ATTRIB_V_POSITION |
                          gl::ATTRIB_V_COLOR |
                          gl::ATTRIB_V_NORMAL |
                          gl::ATTRIB_V_TEXCOORD);
  g->vbo()->allocVertexMemoryOnGPU(g->nVerts());
  g->vbo()->copyVertDataToGPU(normals, g->nVerts(), gl::vnormal);
  g->vbo()->copyVertDataToGPU(colors, g->nVerts(), gl::vcolor);
  g->vbo()->copyVertDataToGPU(texcoords, g->nVerts(), gl::vtexcoord);
  g->vbo()->copyVertDataToGPU(points, g->nVerts(), gl::vposition);
  g->vbo()->printBuffer(g->nVerts());
  g->vao()->unbind();

  g->nFaces(2);
  g->ebo()->bind();
  g->ebo()->reserveNBytesOnGPU(g->nFaces() * 3 * 2);
  g->ebo()->copy2GPU(faces, g->nFaces(), 3);
  g->ebo()->unbind();


  return g;
}
