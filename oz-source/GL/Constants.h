#ifndef __OZ__GL__CONSTANTS__H__
#define __OZ__GL__CONSTANTS__H__

#include <glfw3.h>
#include <OpenGL/gl3.h>

namespace gl {
  const GLuint ATTRIB_V_POSITION = 0;
  const GLuint ATTRIB_V_NORMAL = 1;
  const GLuint ATTRIB_V_TEXCOORD = 2;
  const GLuint ATTRIB_V_COLOR = 3;
  const GLuint ATTRIB_V_BONE_ID = 4;
  const GLuint ATTRIB_V_BONE_WEIGHT = 5;
  const GLuint ATTRIB_V_TANGENT = 6;
  const GLuint ATTRIB_V_BITANGENT = 7;
}

#endif
