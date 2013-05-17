#include "Geometry/Primitives.h"
#include "Geometry/Geometry.h"
#include "Geometry/TriangleMesh.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"
#include "GL/ElementBuffer.h"

using namespace geom;

Geometry* geom::makeCube(float unit) {

  auto g = new TriangleMesh<TRIANGLE>();

  float u = unit;
  float points[] = {
    -u, -u, +u,
    +u, -u, +u,
    +u, +u, +u,
    -u, +u, +u,

    -u, -u, -u,
    +u, -u, -u,
    +u, +u, -u,
    -u, +u, -u,

    +u, -u, +u,
    +u, -u, -u,
    +u, +u, -u,
    +u, +u, +u,

    -u, -u, +u,
    -u, -u, -u,
    -u, +u, -u,
    -u, +u, +u,

    -u, +u, +u,
    +u, +u, +u,
    +u, +u, -u,
    -u, +u, -u,

    -u, -u, +u,   // 20
    +u, -u, +u,   // 21
    +u, -u, -u,   // 22
    -u, -u, -u,   // 23
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
  g->nFaces(12);

  g->vao()->bind();
  g->vbo()->reserveNBytesOnGPU(g->nVerts() * 8 * 4);
  g->ebo()->reserveNBytesOnGPU(g->nFaces() * 3 * 2);

  g->vbo()->copy2GPUPoints(points, g->nVerts());
  g->vbo()->copy2GPUColors(colors, g->nVerts());
  g->ebo()->copy2GPU(faces, g->nFaces(), 3);
  g->vao()->unbind();

  return g;
}

Geometry* geom::makeQuad(float unit)
{
  auto g = new TriangleMesh<TRIANGLE>();
  float s = unit;
  float points[] = {
    -s, -s, 0,
    +s ,-s, 0,
    -s, +s, 0,
    +s, +s, 0
  };
//  _vbo_quad = new VertexBuffer<vertex_t>({{-1, -1}, {1 ,-1}, {-1, 1}, {1, 1}});


  float colors[] = {
    1, 0, 0, 1,
    0, 1, 0, 1,
    0, 0, 1, 1,
    1, 1, 1, 1
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
  g->vbo()->reserveNBytesOnGPU(g->nVerts() * (4 + 4 + 2) * 4);
  g->vbo()->copy2GPUPoints(points, 4);
  g->vbo()->copy2GPUColors(colors, 4);
  g->vbo()->copy2GPUTexcoords(texcoords, 4);
  g->vbo()->printBuffer(4);
  g->vao()->unbind();

  g->nFaces(2);
  g->ebo()->bind();
  g->ebo()->reserveNBytesOnGPU(g->nFaces() * 3 * 2);
  g->ebo()->copy2GPU(faces, g->nFaces(), 2);
  g->ebo()->unbind();

  return g;
}
