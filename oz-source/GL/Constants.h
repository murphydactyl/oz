#ifndef __OZ__GL__CONSTANTS__H__
#define __OZ__GL__CONSTANTS__H__

#include <glfw3.h>
#include <OpenGL/gl3.h>

namespace gl {
  const GLuint ATTRIB_V_POSITION_LOC = 0;
  const GLuint ATTRIB_V_NORMAL_LOC = 1;
  const GLuint ATTRIB_V_TEXCOORD_LOC = 2;
  const GLuint ATTRIB_V_COLOR_LOC = 3;
  const GLuint ATTRIB_V_BONE_ID_LOC = 4;
  const GLuint ATTRIB_V_BONE_WEIGHT_LOC = 5;

  const GLuint MAX_BONES_PER_VERTEX = 4;
  const GLuint NO_OP_BONE_INDEX = MAX_BONES_PER_VERTEX;
}

#endif
