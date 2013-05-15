#ifndef __OZ__GL__VERTEXBUFFER__H__
#define __OZ__GL__VERTEXBUFFER__H__

#include "GL/ArrayBuffer.h"
#include "GL/VertexBufferBase.h"
#include <stdio.h>

namespace gl {

  class VertexBuffer : public VertexBufferBase {

  public:

    const static uint8_t extent_position = 3;
    const static uint8_t extent_color = 4;

    typedef struct vertex_t {
      GLfloat v_position[extent_position];
      GLfloat v_custom;
      GLfloat v_color[extent_color];
    } vertex_t;

    void enablePoints() {
      gl::checkError("VBO @ before binding position");
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      glEnableVertexAttribArray(gl::ATTRIB_V_POSITION);
      glVertexAttribPointer(  gl::ATTRIB_V_POSITION,      // attribute
                              extent_position,            // number of elements per vertex
                              GL_FLOAT,                   // the type of each element
                              GL_FALSE,                   // GL_TRUE == normalize
                              sizeof(vertex_t),           // bytes between elements
                              reinterpret_cast<void*>(offsetof(vertex_t, v_position))  // offset of first element
                              );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      gl::checkError("VBO @ after binding position");
    }

    void enableColors() {
      gl::checkError("VBO @ before binding colors");
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      glEnableVertexAttribArray(gl::ATTRIB_V_COLOR);
      glVertexAttribPointer( gl::ATTRIB_V_COLOR,        // attribute
                             extent_color,              // number of elements per vertex
                             GL_FLOAT,                  // the type of each element
                             GL_FALSE,                  // GL_TRUE == normalize
                             sizeof(vertex_t),          // bytes between elements
                             reinterpret_cast<void*>(offsetof(vertex_t, v_color))   // offset of first element
                             );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      gl::checkError("VBO @ after binding colors");
    }

    void copy2GPUPoints(float* data, uint32_t nVerts) {
      enablePoints();
      copyToGPUInterleaved((char*)data,
                           nVerts,
                           sizeof(vertex_t::v_position),
                           0,
                           sizeof(vertex_t::v_position),
                           0,
                           sizeof(vertex_t));
    }

    void copy2GPUColors(float* data, uint32_t nVerts ) {
      enableColors();
      copyToGPUInterleaved((char*)data,
                           nVerts,
                           sizeof(vertex_t::v_color),
                           0,
                           sizeof(vertex_t::v_color),
                           offsetof(vertex_t, v_color),
                           sizeof(vertex_t));
    }

    void printBuffer(uint32_t nVerts) {
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      vertex_t* data = reinterpret_cast<vertex_t*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY));
      for (int i = 0; i < nVerts; i++) {
        for (int j = 0; j < extent_position; j++) {
          std::cout << data[i].v_position[j] << " ";
        }
        std::cout << data[i].v_custom << " ";
        for (int j = 0; j < extent_color; j++) {
          std::cout << data[i].v_color[j] << " ";
        }
        std::cout << std::endl;
      }
      glUnmapBuffer(GL_ARRAY_BUFFER);
    }

  protected:

  };


}
#endif
