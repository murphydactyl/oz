#ifndef __OZ__GL__ARRAYBUFFER__H__
#define __OZ__GL__ARRAYBUFFER__H__

#include "GL/GLContext.h"

namespace gl {
  class ArrayBuffer {
  public:
    ArrayBuffer() {
      gl::checkError("VBO @ constructor");
      glGenBuffers(1, &buf_);
      gl::checkError("VBO finished constructor");

      nBytesOnGPU_ = 0;
    }

    ~ArrayBuffer() {
      gl::checkError("VBO @ destructor");
      glDeleteBuffers(1, &buf_);
      gl::checkError("VBO finished destructor");
    }

    void reserveNBytesOnGPU(uint32_t s) {
      nBytesOnGPU_ = s;
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      glBufferData(GL_ARRAY_BUFFER,
                   nBytesOnGPU_,
                   NULL,
                   GL_STREAM_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    size_t nBytesOnGPU() { return nBytesOnGPU_; }
    GLuint object() { return buf_; }

  protected:
    GLuint buf_;
    uint32_t nBytesOnGPU_;
    uint32_t nBytesPerVertex_;

  };
}

#endif
