#ifndef __OZ__GL__VERTEXBUFFERBASE__H__
#define __OZ__GL__VERTEXBUFFERBASE__H__

#include "GL/ArrayBuffer.h"
#include <stdio.h>

namespace gl {

  class VertexBufferBase : public ArrayBuffer {

  public:
    void copyToGPUInterleaved(char*    src, uint32_t nVerts, uint32_t nBytesPerVert,
                              uint32_t nSrcOffsetBytes, uint32_t nSrcStrideBytes,
                              uint32_t nDstOffsetBytes, uint32_t nDstStrideBytes) {
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      char* dst = (char*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
      dst += nDstOffsetBytes;
      src += nSrcOffsetBytes;
      for (int i = 0; i < nVerts; i++) {
        std::memcpy(dst, src, nBytesPerVert);
        dst += nDstStrideBytes;
        src += nSrcStrideBytes;
      }
      glUnmapBuffer(GL_ARRAY_BUFFER);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
  };


}
#endif
