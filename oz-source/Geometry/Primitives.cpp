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
  g->vao()->unbind();

  g->nFaces(12);
  g->ebo()->bind();
  g->ebo()->reserveNBytesOnGPU(g->nFaces() * 3 * 2);
  g->ebo()->copy2GPU(faces, g->nFaces(), 3);
  g->ebo()->unbind();

  return g;
}


Geometry* geom::makeCone(float r, float h) {

  uint8_t n = 20;
  int nVerts = n + 2;
  int nFaces = 2 * n;
  int P = n;
  int C = n + 1;
  float points[nVerts][4];
  float colors[nVerts][4];
  uint16_t faces[nFaces][3];

  int X = 0;
  int Y = 1;
  int Z = 2;
  int W = 3;

  points[P][X] = 0;
  points[P][Y] = 0;
  points[P][Z] = 1.0;
  points[P][W] = 1;
  colors[P][0] = 1;
  colors[P][1] = 0;
  colors[P][2] = 0;
  colors[P][3] = 1;


  points[C][X] = 0;
  points[C][Y] = 0;
  points[C][Z] = 0;
  points[C][W] = 1;
  colors[C][0] = 1;
  colors[C][1] = 1;
  colors[C][2] = 1;
  colors[C][3] = 1;

  /*
   * MAKE POINTS
   */
  float dt = math::TAU / (float)(n);
  for (int i = 0; i < n; i++) {
    points[i][X] = r * cos(i * dt);
    points[i][Y] = r * sin(i * dt);
    points[i][Z] = 0;
    points[i][W] = 1;

    colors[i][0] = 0;
    colors[i][1] = 0;
    colors[i][2] = 1;
    colors[i][3] = 1.0;
  }

  /*
   * MAKE FACES CIRCLE FACES
   */
  for (int i = 0; i < n; i++) {
    faces[i][0] = C;
    faces[i][1] = i;
    faces[i][2] = i == (n - 1) ? 0 : i + 1;
  }

  /*
   * MAKE FACES FOR POINT BIT
   */
  for (int i = 0, j = n; i < n; i++, j++) {
    faces[j][0] = i;
    faces[j][1] = P;
    faces[j][2] = i == (n - 1) ? 0 : i + 1;
  }

  auto g = new Mesh(TRIANGLE);

  g->nVerts(nVerts);
  g->vao()->bind();
  g->vbo()->bind();
  g->vbo()->setVertexType(gl::ATTRIB_V_POSITION |
                          gl::ATTRIB_V_COLOR);
  g->vbo()->allocVertexMemoryOnGPU(g->nVerts());
  g->vbo()->copyVertDataToGPU((float*)colors, g->nVerts(), gl::vcolor);
  g->vbo()->copyVertDataToGPU((float*)points, g->nVerts(), gl::vposition);
  g->vbo()->printBuffer(nVerts);
  g->vao()->unbind();

  g->nFaces(nFaces);
  g->ebo()->bind();
  g->ebo()->reserveNBytesOnGPU(g->nFaces() * 3 * 2);
  g->ebo()->copy2GPU((uint16_t*)faces, g->nFaces(), 3);
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
  g->vao()->unbind();

  g->nFaces(2);
  g->ebo()->bind();
  g->ebo()->reserveNBytesOnGPU(g->nFaces() * 3 * 2);
  g->ebo()->copy2GPU(faces, g->nFaces(), 3);
  g->ebo()->unbind();

  return g;
}
