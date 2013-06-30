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
  const GLuint ATTRIB_V_BONE_WEIGHT = 8;
  const GLuint ATTRIB_V_TANGENT = 13;
  const GLuint ATTRIB_V_BITANGENT = 14;
  const GLuint MAX_BONES_PER_VERTEX = 4;
  const GLuint NO_OP_BONE_INDEX = MAX_BONES_PER_VERTEX;
}

#endif
