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
    const static uint8_t extent_texcoord = 2;
    const static uint8_t extent_boneweights = 4;
    const static uint8_t extent_boneids = extent_boneweights;

    typedef struct vertex_t {
      GLfloat v_position[extent_position];
      GLfloat v_custom1;
      GLfloat v_color[extent_color];
      GLfloat v_texcoord[extent_texcoord];
      GLuint  v_boneids[extent_boneids];
      GLfloat v_boneweights[extent_boneweights];
      GLfloat v_custom3;
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

    void enableTexcoords() {
      gl::checkError("VBO @ before binding texcoords");
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      glEnableVertexAttribArray(gl::ATTRIB_V_TEXCOORD);
      glVertexAttribPointer( gl::ATTRIB_V_TEXCOORD,     // attribute
                             extent_texcoord,           // number of elements per vertex
                             GL_FLOAT,                  // the type of each element
                             GL_FALSE,                  // GL_TRUE == normalize
                             sizeof(vertex_t),          // bytes between elements
                             reinterpret_cast<void*>(offsetof(vertex_t, v_texcoord))   // offset of first element
                             );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      gl::checkError("VBO @ after binding texcoords");
    }

    void enableBoneIds() {
      gl::checkError("VBO @ before binding bones");
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      glEnableVertexAttribArray(gl::ATTRIB_V_BONE_ID);
      glVertexAttribPointer( gl::ATTRIB_V_BONE_ID,     // attribute
                             extent_boneids,           // number of elements per vertex
                             GL_UNSIGNED_INT,         // the type of each element
                             GL_FALSE,                  // GL_TRUE == normalize
                             sizeof(vertex_t),          // bytes between elements
                             reinterpret_cast<void*>(offsetof(vertex_t, v_boneids))   // offset of first element
                             );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      gl::checkError("VBO @ after binding weights");
    }

    void enableBoneWeights() {
      gl::checkError("VBO @ before binding weights");
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      glEnableVertexAttribArray(gl::ATTRIB_V_BONE_WEIGHT);
      glVertexAttribPointer( gl::ATTRIB_V_BONE_WEIGHT,     // attribute
                             extent_boneweights,           // number of elements per vertex
                             GL_FLOAT,                  // the type of each element
                             GL_FALSE,                  // GL_TRUE == normalize
                             sizeof(vertex_t),          // bytes between elements
                             reinterpret_cast<void*>(offsetof(vertex_t, v_boneweights))   // offset of first element
                             );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      gl::checkError("VBO @ after binding weights");
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

    void copy2GPUTexcoords(float* data, uint32_t nVerts ) {
      enableTexcoords();
      copyToGPUInterleaved((char*)data,
                           nVerts,
                           sizeof(vertex_t::v_texcoord),
                           0,
                           sizeof(vertex_t::v_texcoord),
                           offsetof(vertex_t, v_texcoord),
                           sizeof(vertex_t));
    }

    void copy2GPUBoneWeights(float* data, uint32_t nVerts ) {
      enableBoneWeights();
      copyToGPUInterleaved((char*)data,
                           nVerts,
                           sizeof(vertex_t::v_boneweights),
                           0,
                           sizeof(vertex_t::v_boneweights),
                           offsetof(vertex_t, v_boneweights),
                           sizeof(vertex_t));
    }

    void copy2GPUBoneIds(uint32_t* data, uint32_t nVerts ) {
      enableBoneIds();
      copyToGPUInterleaved((char*)data,
                           nVerts,
                           sizeof(vertex_t::v_boneids),
                           0,
                           sizeof(vertex_t::v_boneids),
                           offsetof(vertex_t, v_boneids),
                           sizeof(vertex_t));
    }


    void printBuffer(uint32_t nVerts) {
      glBindBuffer(GL_ARRAY_BUFFER, buf_);
      vertex_t* data = reinterpret_cast<vertex_t*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY));
      for (int i = 0; i < nVerts; i++) {
        for (int j = 0; j < extent_position; j++) {
          std::cout << data[i].v_position[j] << " ";
        }
        std::cout << data[i].v_custom1 << " ";
        for (int j = 0; j < extent_color; j++) {
          std::cout << data[i].v_color[j] << " ";
        }
        for (int j = 0; j < extent_texcoord; j++) {
          std::cout << data[i].v_texcoord[j] << " ";
        }
        for (int j = 0; j < extent_boneweights; j++) {
          std::cout << "("
                    << data[i].v_boneids[j] << ","
                    << data[i].v_boneweights[j] << ")";
        }
        std::cout << data[i].v_custom3 << " ";
        std::cout << std::endl;
      }
      glUnmapBuffer(GL_ARRAY_BUFFER);
    }

  protected:

  };


}
#endif
