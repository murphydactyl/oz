#ifndef __OZ__GEOMETRY__WIRE__H__
#define __OZ__GEOMETRY__WIRE__H__

#include "Geometry/Geometry.h"
#include "GL/ShaderProgram.h"
#include <vector>

namespace gl {
  class VertexArrayObject;
  class VertexBuffer;
}

namespace geom {

  class Wire : public Geometry {
      typedef math::Vec4f position_t;
      typedef math::Vec4f color_t;

    public:
      Wire();
      ~Wire();
      void draw(gl::ShaderProgram* shader);
      void nVerts(uint64_t newSize);
      uint64_t nVerts();

      void addPosition(float x, float y, float z, float w=1.0);
      void addColor(float r, float g, float b, float a=1.0);
      void clear();
      void sync();

    protected:

      std::vector<position_t>* position_ = nullptr;
      std::vector<color_t>* color_ = nullptr;
      bool bNeedSync_ = false;

      /*
       * Static methods
       */

  };
}
#endif // __OZ__GEOMETRY__WIRE__H__
