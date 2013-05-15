#ifndef __OZ__GL__ELEMENTBUFFER__H__
#define __OZ__GL__ELEMENTBUFFER__H__

#include "GL/ArrayBuffer.h"

namespace gl {

  template<typename I=uint16_t>
  class ElementBuffer : public ArrayBuffer {
  public:

    typedef struct triangle_t {
      typedef I index_t;
      const uint32_t gl_t = GL_UNSIGNED_SHORT;
      const size_t nBytes = 6;
    } triangle_t;

    void copy2GPU(I* data, uint32_t nElements, uint16_t nVertsPerElement) {
      nVertsPerElement_ = nVertsPerElement;
      gl::checkError("EBO @ copy");
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_);
      glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                    nBytesOnGPU_,
                    data,
                    GL_STREAM_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      gl::checkError("EBO finsihed sync");
      std::cout << "copied: " << nBytesOnGPU_ << " bytes to element buffer" << std::endl;
    }

    void bind() {
      gl::checkError("EBO @ ", __LINE__, __FILE__);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_);
      gl::checkError("EBO finished bind");
    }

    void unbind() {
      gl::checkError("EBO @ ", __LINE__, __FILE__);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      gl::checkError("EBO finished unbind");
    }

    void printBuffer(uint32_t nFaces) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_);
      I* data = reinterpret_cast<I*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY));
      for (int i = 0; i < nFaces; i++) {
        for (int j = 0; j < nVertsPerElement_; j++) {
          std::cout << data[nVertsPerElement_ * i + j] << " ";
        }
        std::cout << std::endl;
      }
      glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

  protected:

    uint16_t nVertsPerElement_;

  };


}
#endif
