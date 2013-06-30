#ifndef __OZ__GEOMETRY__MESH__H__
#define __OZ__GEOMETRY__MESH__H__

#include "Vector/Vector.h"
#include "Math/Math.h"
#include "Geometry/Geometry.h"
#include "GL/ElementBuffer.h"
#include "GL/Texture.h"
#include "Scene/Node.h"

namespace gl {
  template <typename uint16_t> class ElementBuffer;
  class ShaderProgram;
}

namespace geom {

  typedef gl::ElementBuffer<uint16_t>* eboptr_t;
  typedef math::Mat3Xf positions_t;
  typedef math::Mat3Xf normals_t;
  typedef math::Mat4Xf colors_t;
  typedef math::Mat3Xu16 faces_t;
  typedef math::Mat2Xf texcoord_t;
  typedef math::Mat16Xf boneweights_t;
  typedef math::Mat16Xu boneids_t;
  typedef Vector<scene::Node<float>*> bonelist_t;

  template <element_t E=TRIANGLE>
  class Mesh : public Geometry {

    public:

      Mesh();
      ~Mesh();
      virtual void draw(gl::ShaderProgram* shader=nullptr);
      uint64_t nFaces();
      uint64_t nVerts();
      void nVerts(uint64_t newSize);
      void nFaces(uint64_t nFaces);
      void attachTexture(gl::Texture* tex);
      element_t elementType();
      eboptr_t ebo();
      faces_t& faces();
      positions_t& positions();
      normals_t& normals();
      colors_t& colors();
      texcoord_t& texcoords();
      boneweights_t& boneweights();
      boneids_t& boneids();
      bool hasTexture();
      bool hasBones();
      bonelist_t& bones();

    protected:
      element_t elementType_ = E;
      uint64_t nVerts_;
      uint64_t nFaces_;
      eboptr_t ebo_;
      positions_t positions_;
      colors_t colors_;
      normals_t normals_;
      faces_t faces_;
      texcoord_t texcoords_;
      boneweights_t boneweights_;
      boneids_t boneids_;
      gl::Texture* tex_;
      bonelist_t bones_;
  };

  typedef Mesh<TRIANGLE> TriangleMesh;

}

#endif
