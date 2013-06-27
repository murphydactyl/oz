#ifndef __OZ__GL__TEXTURE__H__
#define __OZ__GL__TEXTURE__H__

#include "GL/GLContext.h"
#include "GL/PixelTypes.h"

namespace gl {

  class Texture
  {
    public:

      virtual void initOnGPU()=0;
      virtual void bind(uint8_t textureUnit=0)=0;
      virtual void copy2GPU()=0;
      virtual void copy2CPU()=0;
      virtual char* ptr2RawData()=0;
    protected:
      GLuint glName_;

  };

}

#endif


