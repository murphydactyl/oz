#ifndef __OZ__GL__VERTEXBUFFER__H__
#define __OZ__GL__VERTEXBUFFER__H__

#include "GL/Constants.h"
#include "GL/ArrayBuffer.h"
#include <vector>
#include <stdio.h>

namespace gl {

  class vattribute {
    public:
      vattribute(std::string Name, int ShaderLoc, int GLType,
                 uint32_t NumElements, uint32_t ElementSize,
                 bool Normalize = false) {
        name = Name;
        shader_location = ShaderLoc;
        gl_underlying_type = GLType;
        num_elements = NumElements;
        element_size_in_bytes = ElementSize;
        normalized = Normalize;
      }

      std::string name;
      int shader_location;
      int gl_underlying_type;
      uint32_t num_elements;
      uint32_t element_size_in_bytes;
      bool normalized = false;

      bool operator==(const vattribute& rhs) const
      {
        return (shader_location == rhs.shader_location &&
                gl_underlying_type == rhs.gl_underlying_type &&
                num_elements == rhs.num_elements &&
                element_size_in_bytes == rhs.element_size_in_bytes);
      }

      uint32_t sizeInBytes() {
        return element_size_in_bytes * num_elements;
      }

      void print(char* start) {
        std::cout << name << ": ";
        for (auto i = 0; i < num_elements; i++)
          switch (gl_underlying_type) {
            case GL_FLOAT: {
              auto el = reinterpret_cast<float*>(start);
              std::cout << el[i] << " ";
              break;
            }
            case GL_DOUBLE: {
              auto el = reinterpret_cast<double*>(start);
              std::cout << el[i] << " ";
              break;
            }
            case GL_UNSIGNED_INT: {
              auto el = reinterpret_cast<uint32_t*>(start);
              std::cout << el[i] << " ";
              break;
            }
            case GL_INT: {
              auto el = reinterpret_cast<int32_t*>(start);
              std::cout << el[i] << " ";
              break;
            }
            default:
              std::cout << "Uncaught opengl type in " <<
                           __FILE__;
          }
        std::cout << std::endl;
      }

  };

  static const vattribute vposition("position", gl::ATTRIB_V_POSITION_LOC,GL_FLOAT, 4, 4);
  static const vattribute vnormal("normal", gl::ATTRIB_V_NORMAL_LOC,GL_FLOAT, 4, 4);
  static const vattribute vtexcoord("texcoord", gl::ATTRIB_V_TEXCOORD_LOC,GL_FLOAT, 2, 4);
  static const vattribute vcolor("color", gl::ATTRIB_V_COLOR_LOC,GL_FLOAT, 4, 4);
  static const vattribute vboneid("boneid", gl::ATTRIB_V_BONE_ID_LOC,GL_UNSIGNED_INT, 4, 4);
  static const vattribute vboneweight("boneweight", gl::ATTRIB_V_BONE_WEIGHT_LOC,GL_FLOAT, 4, 4);

  typedef enum {
    ATTRIB_V_POSITION =    1 << gl::ATTRIB_V_POSITION_LOC,
    ATTRIB_V_NORMAL =      1 << gl::ATTRIB_V_NORMAL_LOC,
    ATTRIB_V_TEXCOORD =    1 << gl::ATTRIB_V_TEXCOORD_LOC,
    ATTRIB_V_COLOR =       1 << gl::ATTRIB_V_COLOR_LOC,
    ATTRIB_V_BONEID =      1 << gl::ATTRIB_V_BONE_ID_LOC,
    ATTRIB_V_BONEWEIGHT =  1 << gl::ATTRIB_V_BONE_WEIGHT_LOC
  } ATTR_V_FLAG;

  class VertexBuffer : public ArrayBuffer {

    private:

      uint32_t enabled_attributes_ = 0;
      std::vector<vattribute> vpatts;

    public:

      bool isEnabled(ATTR_V_FLAG a) {
        return (enabled_attributes_ & a);
      }

      /*
       * Build up known offsets based on which attributes are enabled
       */
      VertexBuffer() {}

      uint32_t calculateOffset(vattribute a) {
        uint32_t offset = 0;
        for (int i = 0; i < vpatts.size(); i++) {
          if (a == vpatts[i]) {
            return offset;
          }
          offset += vpatts[i].sizeInBytes();
        }
        std::cerr << "Dying... can't calculate offset of vattribute named "
                  << a.name << "since it is not enabled" << std::endl;
        assert(false);
      }

      void setVertexType(uint32_t flags) {
        enabled_attributes_ = flags;
        vpatts.clear();
        if (isEnabled(ATTRIB_V_POSITION)) vpatts.push_back(vposition);
        if (isEnabled(ATTRIB_V_NORMAL)) vpatts.push_back(vnormal);
        if (isEnabled(ATTRIB_V_TEXCOORD)) vpatts.push_back(vtexcoord);
        if (isEnabled(ATTRIB_V_COLOR)) vpatts.push_back(vcolor);
        if (isEnabled(ATTRIB_V_BONEID)) vpatts.push_back(vboneid);
        if (isEnabled(ATTRIB_V_BONEWEIGHT)) vpatts.push_back(vboneweight);

        // compute offsets
        nBytesPerVertex_ = 0;
        for (int i = 0; i < vpatts.size(); i++) {
          std::cout << "enabled: " << vpatts[i].name << std::endl;
          nBytesPerVertex_ += vpatts[i].sizeInBytes();
        }

        for (int i = 0; i < vpatts.size(); i++) {
          enableAttribute(vpatts[i]);
        }
        std::cout << "nBytesPerVertex is " << nBytesPerVertex_ << std::endl;
      }

      void copyVertDataToGPU(void* data, size_t nVerts, vattribute a) {
        gl::checkError("VBO @ before copying vert data " + a.name);
        uint32_t byte_offset = calculateOffset(a);
        copyToGPUInterleaved((char*)data, nVerts, a.sizeInBytes(),
                             0, a.sizeInBytes(),
                             byte_offset, nBytesPerVertex_);
        gl::checkError("VBO @ after copying vert data " + a.name);
      }

      void copyToGPUInterleaved(char*    src, uint32_t nVerts, uint32_t nBytesToCopyPerVert,
                                uint32_t nSrcOffsetBytes, uint32_t nSrcStrideBytes,
                                uint32_t nDstOffsetBytes, uint32_t nDstStrideBytes) {
        glBindBuffer(GL_ARRAY_BUFFER, buf_);
        char* dst = (char*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        src += nSrcOffsetBytes;
        dst += nDstOffsetBytes;
        for (int i = 0; i < nVerts; i++) {
          std::memcpy(dst, src, nBytesToCopyPerVert);
          src += nSrcStrideBytes;
          dst += nDstStrideBytes;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
      }

      void printBuffer(uint32_t nVerts) {
        glBindBuffer(GL_ARRAY_BUFFER, buf_);
        char* data = reinterpret_cast<char*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY));
        for (auto i = 0; i < nVerts; i++) {
          for (auto j = 0; j < vpatts.size(); j++) {
            vpatts[j].print(data);
            data += vpatts[j].sizeInBytes();
          }
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
      }

      void allocVertexMemoryOnGPU(uint32_t nVerts) {
        uint64_t nBytesRequested = nBytesPerVertex() * nVerts;
        if (nBytesRequested != nBytesOnGPU()) {
          std::cout << "Allocating " << nBytesRequested
                    << " bytes on GPU for VertexBuffer" << object() << "...";
          reserveNBytesOnGPU(nBytesRequested);
          std::cout << " Success" << std::endl;
        }
      }


    protected:

      void enableAttribute(vattribute a) {
        gl::checkError("VBO @ before binding attribute " + a.name);
        uint32_t byte_offset = calculateOffset(a);
        glBindBuffer(GL_ARRAY_BUFFER, buf_);
        glEnableVertexAttribArray(a.shader_location);
        glVertexAttribPointer(  a.shader_location,
                                a.num_elements,
                                a.gl_underlying_type,
                                a.normalized,
                                nBytesPerVertex(),
                                reinterpret_cast<GLvoid*>(byte_offset));
        gl::checkError("VBO @ after binding attribute " + a.name);
      }

  };


}
#endif
