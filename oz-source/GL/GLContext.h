#ifndef __OZ_GLCONTEXT__H__
#define __OZ_GLCONTEXT__H__

#include <GL/glfw.h>
#include <OpenGL/gl3.h>
#include <iostream>

#include "GL/Constants.h"
#include "../Math/Math.h"

class GLContext {
public:
  static int checkError(const std::string& msg, int line, const char* file);
  static int checkError(const std::string& msg, bool always_print = false);

};

#endif
