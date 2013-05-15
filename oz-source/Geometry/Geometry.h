#ifndef __OZ__GEOMETRY__GEOMETRY__H__
#define __OZ__GEOMETRY__GEOMETRY__H__

#include "GL/GLContext.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"

namespace gl {
  class VertexArrayObject;
  class VertexBuffer;
}

namespace geom {

  typedef gl::VertexBuffer* vboptr_t;
  typedef gl::VertexArrayObject* vaoptr_t;

  enum element_t {
    TRIANGLE = GL_TRIANGLES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    POINT = GL_POINTS,
    LINE = GL_LINES,
    LINE_STRIP = GL_LINE_STRIP
  };

  class Geometry {
    public:
      virtual void draw()=0;
      virtual void nVerts(uint64_t newSize)=0;
      virtual uint64_t nVerts()=0;
      virtual element_t elementType()=0;
      vaoptr_t vao() { return vao_ ; }
      vboptr_t vbo() { return vbo_; }

    protected:
      vboptr_t vbo_;
      vaoptr_t vao_;
  };
}
#endif
