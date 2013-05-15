#ifndef __OZ__GEOMETRY__TRIANGLEMESH__H__
#define __OZ__GEOMETRY__TRIANGLEMESH__H__

#include "Vector/Vector.h"
#include "Math/Math.h"
#include "Geometry/Geometry.h"
#include "GL/ElementBuffer.h"

namespace gl {
  template <typename uint16_t> class ElementBuffer;
}

namespace geom {

  enum vertproperty_t {

  };

  typedef gl::ElementBuffer<uint16_t>* eboptr_t;
  typedef Math::Mat3Xf positions_t;
  typedef Math::Mat3Xf normals_t;
  typedef Math::Mat4Xf colors_t;
  typedef Math::Mat3Xu16 faces_t;
  typedef Math::Mat2Xf texcoord_t;

  template <element_t E>
  class TriangleMesh : public Geometry {

    public:

      TriangleMesh();
      ~TriangleMesh();
      virtual void draw();
      uint64_t nFaces();
      uint64_t nVerts();
      void nVerts(uint64_t newSize);
      void nFaces(uint64_t nFaces);
      element_t elementType();
      eboptr_t ebo();
      faces_t& faces();
      positions_t& positions();
      normals_t& normals();
      colors_t& colors();

    protected:
      element_t elementType_ = E;
      uint64_t nVerts_;
      uint64_t nFaces_;
      eboptr_t ebo_;
      positions_t positions_;
      colors_t colors_;
      normals_t normals_;
      faces_t faces_;
      texcoord_t texcoord_;

  };
}

#endif
