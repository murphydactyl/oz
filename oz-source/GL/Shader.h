
//  shader.h
//  GLFW
//
//  Created by Murphy M Stein on 9/26/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#ifndef __OZ__GL__Shader__H__
#define __OZ__GL__Shader__H__

#include <iostream>
#include <map>
#include <string>
#include "GL/GLContext.h"

#define SHADER_PATH "../shaders/"
#define ABSOLUTE_PATHS 0x01
#define JUST_FILENAME 0x02
#define LIBRARY_USES ABSOLUTE_PATHS
#define GLSL_VERSION "#version 150\nprecision lowp float;\n"

namespace gl {
  using namespace std;
  enum ShaderType {
    Vert = GL_VERTEX_SHADER,
    Frag = GL_FRAGMENT_SHADER,
    Geom = GL_GEOMETRY_SHADER
  };

  class VertexShader;
  class FragmentShader;
  class GeometryShader;
  class Shader;
  class ShaderLibrary;

  class ShaderLibrary : public map<string, Shader*> {
  public:
    ~ShaderLibrary();
  };

  typedef ShaderLibrary library_t;

  class Shader {

  public:
    Shader();
    ~Shader();
    GLuint glName() { return _glName; };
    string pathToSource() { return _absolute_path; };

  protected:
    static library_t library;
    GLuint _glName;
    string _filename;
    string _absolute_path;

    static Shader* retrieveCompiledShader(string full_filename);
    static string constructAbsolutePathFromDefaultShaderDirPath(string filename);
    static char* loadSourceFromFile(const char* filename);
    static GLuint compileSource(const char* source, ShaderType type);
    static void print_log(GLuint object);
    static Shader* load(string filename, ShaderType st);
    static Shader* loadString(string name, string src, ShaderType st);
    static void addShaderToLibrary(Shader* shader);

  };

  class VertexShader : public Shader {
  public:
    static VertexShader* load(string filename) {
      return static_cast<VertexShader*>(Shader::load(filename, ShaderType::Vert));
    };
    static VertexShader* loadString(string name, string src) {
      return static_cast<VertexShader*>(Shader::loadString(name, src, ShaderType::Vert));
    };
  };

  class FragmentShader : public Shader {
  public:
    static FragmentShader* load(string filename) {
      return static_cast<FragmentShader*>(Shader::load(filename, ShaderType::Frag));
    };
    static FragmentShader* loadString(string name, string src) {
      return static_cast<FragmentShader*>(Shader::loadString(name, src, ShaderType::Frag));
    };
  };

  class GeometryShader : public Shader {
  public:
    static GeometryShader* load(string filename) {
      return static_cast<GeometryShader*>(Shader::load(filename, ShaderType::Geom));
    };
    static GeometryShader* loadString(string name, string src) {
      return static_cast<GeometryShader*>(Shader::loadString(name, src, ShaderType::Geom));
    };
  };
}


#endif /* defined(__GLFW__shader__) */
