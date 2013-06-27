#ifndef __OZ__GL__GLCONTEXT__H__
#define __OZ__GL__GLCONTEXT__H__

#include <GL/glfw3.h>
#include <OpenGL/gl3.h>
#include <assert.h>
#include <sstream>
#include <iostream>
#include "GL/Constants.h"
#include "../Math/Math.h"

namespace gl {

  typedef enum POINT {
    HAS_RGBA_COLOR = 0x00000001
  } POINT;

  static inline int checkError(const std::string& msg, int line, const char* file) {
    std::stringstream s;
    s << msg << " at line " << line << " in file " << file;
    GLenum stat = glGetError();
    if (stat != GL_NO_ERROR) {
        std::cout << "[" << s.str() << "] Error: " << stat << std::endl;
        assert(0);
        return 0;
      }
    return 1;
  }

  static inline int checkError(const std::string& msg, bool always_print = false) {
    GLenum stat = glGetError();
    if (stat != GL_NO_ERROR) {
        std::cout << "[" << msg << "] Error: " << stat << std::endl;
        assert(0);
        return 0;
      } else if (always_print) {
        std::cout << "[" << msg << "] No error." << std::endl;
      }
    return 1;
  }

  class GLContext {
  public:

  };
}

#endif
