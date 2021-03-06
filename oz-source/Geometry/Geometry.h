#ifndef __OZ__GEOMETRY__GEOMETRY__H__
#define __OZ__GEOMETRY__GEOMETRY__H__

#include "GL/GLContext.h"
#include "GL/VertexArrayObject.h"
#include "GL/VertexBuffer.h"
#include "GL/ShaderProgram.h"

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
      /*
       * Pure-virtual Methods
       */
      virtual void draw(gl::ShaderProgram* shader)=0;
      virtual void nVerts(uint64_t newSize)=0;
      virtual uint64_t nVerts()=0;

      /*
       * Virtual methods
       */
      virtual std::string name() { return name_; }
      virtual void name(std::string name) { name_ = name; }

      /*
       * Built-in methods
       */
      vaoptr_t vao() { return vao_; }
      vboptr_t vbo() { return vbo_; }
      element_t elementType() { return elementType_; }
      void setElementType(element_t e) { elementType_ = e; }

    protected:
      element_t elementType_;
      vboptr_t vbo_;
      vaoptr_t vao_;
      std::string name_;
  };
}
#endif
