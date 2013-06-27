#ifndef __OZ__GL__TEXTURE2D__H__
#define __OZ__GL__TEXTURE2D__H__

#include "GL/Texture.h"

namespace gl {

  template <class T>
  class Texture2D : public Texture
  {

    public:
      typedef T pixelType;
      Texture2D(uint32_t width, uint32_t height);
      Texture2D(T* src, uint32_t width, uint32_t height);
      virtual void initOnGPU();
      virtual void bind(uint8_t textureUnit=0);
      virtual uint32_t width();
      virtual uint32_t height();
      T* data();
      virtual void copy2GPU();
      virtual void copy2CPU();
      virtual char* ptr2RawData();
      ~Texture2D();

    protected:
      void init(T* src, uint32_t width, uint32_t height);
      uint32_t width_;
      uint32_t height_;
      GLint glInternalFormat_;
      GLint glFormat_;
      GLint glType_;
      T* data_;

  };

}

////////////////////////////////////////////////////////////////////////////////
// NOTES ON COMBOS OF internalformat x format x type
//		INTERNALFORMAT				FORMAT						TYPE
//		GL_RGBA                     GL_RGBA						GL_UNSIGNED_BYTE
//		GL_R32F                     GL_RED						GL_FLOAT
//		GL_RG32F					GL_RG                       GL_FLOAT
//		GL_RGBA32I					GL_RGBA_INTEGER				GL_INT
//		GL_RGBA32UI                 GL_RGBA_INTEGER				GL_UNSIGNED_INT
//		GL_DEPTH_COMPONENT32F       GL_DEPTH_COMPONENT			GL_FLOAT
//		GL_R16UI                    GL_RED_INTEGER				GL_UNSIGNED_SHORT
#endif
