#ifndef __OZ__GL__VERTEXWRITER__H__
#define __OZ__GL__VERTEXWRITER__H__

#include "GL/GLContext.h"
#include <vector>

namespace gl {
  class VertexWriter {

      typedef math::Vec4f position_t;
      typedef math::Vec4f color_t;


      /*
     * Default C'tor
     */
      VertexWriter() {
        vbo_ = new VertexBuffer();
        vao_ = new VertexArrayObject();
        position_ = new std::vector<position_t>();
        color_ = new std::vector<color_t>();

        vao()->bind();
        vbo()->bind();
        vbo()->setVertexType(gl::ATTRIB_V_POSITION |
                             gl::ATTRIB_V_COLOR);
        vao()->unbind();
      }

      /*
       * D'tor
       */
      ~VertexWriter() {
        delete vbo_;
        delete vao_;
        delete position_;
        delete color_;
      }

      inline void addPosition(float x, float y, float z, float w=1.0) {
        position_t v(x, y, z, w);
        position_->push_back(v);
      }

      inline void addColor(float r, float g, float b, float a=1.0) {
        color_t v(r, g, b, a);
        color_->push_back(v);
      }

      void reset() {
        color_->resize(0);
        position_->resize(0);
      }

      void sync() {
        vao()->bind();
        vbo()->bind();
        vbo()->allocVertexMemoryOnGPU(nVerts());
        vbo()->copyVertDataToGPU((float*)color_->data(), nVerts(), gl::vcolor);
        vbo()->copyVertDataToGPU((float*)position_->data(), nVerts(), gl::vposition);
        vbo()->printBuffer(nVerts());
        vao()->unbind();
      }

      inline size_t nVerts() {
        if (position_->size() >= color_->size()) return color_->size();
        return position_->size();
      }

      void bind() {
        vao()->bind();
      }

      void unbind() {
        vao()->unbind();
      }

      /*
       * Getters
       */
      VertexBuffer* vbo() { return vbo_; }
      VertexArrayObject* vao() { return vao_; }

    protected:
      VertexBuffer* vbo_;
      VertexArrayObject* vao_;
      std::vector<position_t>* position_;
      std::vector<color_t>* color_;

  };
}

#endif
