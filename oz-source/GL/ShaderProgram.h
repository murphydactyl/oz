//
//  shaderprogram.h
//  GLFW
//
//  Created by Murphy M Stein on 9/26/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#ifndef __OZ__GL__SHADERPROGRAM__H__
#define __OZ__GL__SHADERPROGRAM__H__

#include <iostream>
#include "GL/Shader.h"

namespace gl {
  typedef std::shared_ptr<Shader> shaderPtr;
  class ShaderProgram {
  public:
    ShaderProgram();
    ShaderProgram(string vs, string fs);
    ShaderProgram(string vs, string fs, string gs);
    ~ShaderProgram();
    GLuint glName();
    GLint getUniformLocation(string name);
    GLint getAttribLocation(string name);
    void bind()         { glUseProgram(_glName);  }
    GLint link();
    void validate();
    ShaderProgram* attachSourceVS(string name, string source);
    ShaderProgram* attachSourceFS(string name, string source);
    ShaderProgram* attachSourceGS(string name, string source);
    ShaderProgram* attachVS(string vs_filename);
    ShaderProgram* attachFS(string fs_filename);
    ShaderProgram* attachGS(string gs_filename);

    void setFragDataLocation(GLint colorNum, string name);

    void setUniform(string n, GLfloat v0);
    void setUniform(string n, GLfloat v0, GLfloat v1);
    void setUniform(string n, GLfloat v0, GLfloat v1, GLfloat v2);
    void setUniform(string n, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

    void setUniform(string n, GLuint v0);

    void setUniform(string n, GLint v0);
    void setUniform(string n, GLint v0, GLint v1);
    void setUniform(string n, GLint v0, GLint v1, GLint v2);
    void setUniform(string n, GLint v0, GLint v1, GLint v2, GLint v3);

    void setUniform(string n, const math::Mat4f& mat4);
    void setUniform(string n, const math::Mat3f& mat3);

    void setUniform(string n, const math::Vec3f&);
    void setUniform(string n, const math::Vec4f&);


  protected:

    void setDefaultAttribLocations();
    void setDefaultFragDataLocations();

    Shader* vShader;
    Shader* fShader;
    Shader* gShader;
    void print_log(GLuint);
    GLuint _glName;
    GLenum status;
    bool _validated = false;
    bool owns_shaders;
    bool owns_program;

    void constructProgramName(string vertShader, string fragShader);
    void constructProgramName(string vertShader, string fragShader, string geomShader);

  };
}
#endif
