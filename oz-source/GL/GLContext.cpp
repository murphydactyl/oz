#include <assert.h>
#include <sstream>
#include "GL/GLContext.h"

using namespace std;

int GLContext::checkError(const string& msg, int line, const char* file) {
  stringstream s;
  s << msg << " at line " << line << " in file " << file;
  GLenum stat = glGetError();
  if (stat != GL_NO_ERROR) {
      cout << "[" << s.str() << "] Error: " << stat << endl;
      assert(0);
      return 0;
    }
  return 1;
}

int GLContext::checkError(const string& msg, bool always_print) {
  GLenum stat = glGetError();
  if (stat != GL_NO_ERROR) {
      cout << "[" << msg << "] Error: " << stat << endl;
      assert(0);
      return 0;
    } else if (always_print) {
      cout << "[" << msg << "] No error." << endl;
    }
  return 1;
}
