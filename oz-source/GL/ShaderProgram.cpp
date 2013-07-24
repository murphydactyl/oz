//
//  shaderprogram.cpp
//  GLFW
//
//  Created by Murphy M Stein on 9/26/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//

#include "GL/ShaderProgram.h"
using namespace gl;

ShaderProgram::ShaderProgram() {
  fShader = nullptr;
  vShader = nullptr;
  gShader = nullptr;
  _glName = glCreateProgram();
  if (_glName == 0) {
      cout << "UH-OH!  Error creating new program." << endl;
    }
}

ShaderProgram::ShaderProgram(string vs_filename, string fs_filename) {
  _glName = glCreateProgram();
  if (_glName == 0) {
      cout << "UH-OH!  Error creating new program." << endl;
    }
  attachVS(vs_filename);
  attachFS(fs_filename);
  gShader = nullptr;
  link();
}

ShaderProgram::ShaderProgram(string vs_filename,
			     string fs_filename,
			     string gs_filename) {
  _glName = glCreateProgram();
  if (_glName == 0) {
      cout << "UH-OH!  Error creating new program." << endl;
    }
  attachVS(vs_filename);
  attachFS(fs_filename);
  attachGS(gs_filename);
  link();
}

ShaderProgram* ShaderProgram::attachSourceVS(string name, string vs) {
  gl::checkError("Before attachVS");
  vShader = VertexShader::loadString(name, vs);
  setDefaultAttribLocations();
  assert(vShader->glName());
  gl::checkError("After attachVS");
  return this;
}

ShaderProgram* ShaderProgram::attachSourceFS(string name, string fs) {
  gl::checkError("Before attachFS");
  fShader = FragmentShader::loadString(name, fs);
  setDefaultFragDataLocations();
  assert(fShader->glName());
  gl::checkError("After attachFS");
  return this;
}

ShaderProgram* ShaderProgram::attachSourceGS(string name, string gs) {
  gShader = GeometryShader::loadString(name, gs);
  return this;
}


ShaderProgram* ShaderProgram::attachVS(string vs_filename) {
  gl::checkError("Before attachVS");
  vShader = VertexShader::load(vs_filename);
  setDefaultAttribLocations();
  assert(vShader->glName());
  gl::checkError("After attachVS");
  return this;
}

ShaderProgram* ShaderProgram::attachFS(string fs_filename) {
  gl::checkError("Before attachFS");
  fShader = FragmentShader::load(fs_filename);
  setDefaultFragDataLocations();
  assert(fShader->glName());
  gl::checkError("After attachFS");
  return this;
}

ShaderProgram* ShaderProgram::attachGS(string gs_filename) {
  gShader = GeometryShader::load(gs_filename);
  return this;
}

ShaderProgram::~ShaderProgram() {
  if (status == GL_TRUE && owns_program) {
      glDeleteProgram(_glName);
    }
}

void ShaderProgram::setDefaultAttribLocations() {
  glBindAttribLocation(_glName, gl::ATTRIB_V_POSITION_LOC, "v_position");
  glBindAttribLocation(_glName, gl::ATTRIB_V_NORMAL_LOC, "v_normal");
  glBindAttribLocation(_glName, gl::ATTRIB_V_COLOR_LOC, "v_color");
  glBindAttribLocation(_glName, gl::ATTRIB_V_TEXCOORD_LOC, "v_texcoord");
  glBindAttribLocation(_glName, gl::ATTRIB_V_BONE_ID_LOC, "v_boneid");
  glBindAttribLocation(_glName, gl::ATTRIB_V_BONE_WEIGHT_LOC, "v_boneweight");
}

void ShaderProgram::setDefaultFragDataLocations() {
  glBindFragDataLocation(_glName, 0, "fragColor");
  glBindFragDataLocation(_glName, 1, "fragColor1");
  glBindFragDataLocation(_glName, 2, "fragColor2");
  glBindFragDataLocation(_glName, 3, "fragColor3");
  glBindFragDataLocation(_glName, 4, "fragColor4");
  glBindFragDataLocation(_glName, 5, "fragColor5");
  glBindFragDataLocation(_glName, 6, "fragColor6");
  glBindFragDataLocation(_glName, 7, "fragColor7");
}

void ShaderProgram::setFragDataLocation(GLint colorNum, string name) {
  glBindFragDataLocation(_glName, colorNum, name.c_str());
}

GLint ShaderProgram::link() {
  gl::checkError("before link");
  GLint link_ok = GL_FALSE;
  glAttachShader(_glName, vShader->glName());
  gl::checkError("here");
  glAttachShader(_glName, fShader->glName());
  if (gShader != nullptr) {
      glAttachShader(_glName, gShader->glName());
    }
  glLinkProgram(_glName);
  glGetProgramiv(_glName, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
      fprintf(stderr, "Error in glLinkProgram.\n");
      print_log(_glName);
      return GL_FALSE;

    } else {
    }

  owns_program = true;
  gl::checkError("after link");
  return GL_TRUE;
}

void ShaderProgram::validate() {
  glValidateProgram(_glName);
  GLint valid;
  glGetProgramiv(_glName, GL_VALIDATE_STATUS, &valid);
  if (!_validated) {
      if (valid == GL_FALSE) {
          ShaderProgram::print_log(_glName);
        } else {
          cout << "ShaderProgram #" << glName() << " is valid." << endl;
        }
    }
  _validated = true;
}

GLuint ShaderProgram::glName() {
  return _glName;
}


GLint ShaderProgram::getUniformLocation(string name) {
  GLint loc = glGetUniformLocation(_glName, name.c_str());
  if (loc == -1) {
      //cerr << "ShaderProgram missing uniform: " <<  name.c_str() << endl;
      return -1;
    }
  return loc;
}

GLint ShaderProgram::getAttribLocation(string name) {
  GLint loc = glGetAttribLocation(_glName, name.c_str());
  if (loc == -1) {
      cerr << "Shader missing attribute: " << name << endl;
      cerr << "While using shader: " << vShader->pathToSource() << endl;
      return -1;
    }
  return loc;
}



// LOG /////////////////////////////////////////////////////////////////////////
// Display compilation errors from the OpenGL shader compiler
//
void ShaderProgram::print_log(GLuint object) {
  GLint log_length = 0;
  if (glIsShader(object))
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else if (glIsProgram(object))
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else {
      fprintf(stderr, "printlog: Not a shader or a program\n");
      return;
    }

  char* log = (char*)malloc(log_length);

  if (glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else if (glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);

  fprintf(stderr, "%s", log);
  free(log);
}

//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
// SETTERS           /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
void ShaderProgram::setUniform(string n, GLfloat v0) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform1f(loc, v0);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n, GLfloat v0, GLfloat v1) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform2f(loc, v0, v1);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n,
                               GLfloat v0, GLfloat v1, GLfloat v2) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform3f(loc, v0, v1, v2);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n,
                               GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform4f(loc, v0, v1, v2, v3);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}

// GLuint ///////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniform(string n, GLuint v0) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform1ui(loc, v0);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}


void ShaderProgram::setUniform(string n, GLint v0) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform1i(loc, v0);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n, GLint v0, GLint v1) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform2i(loc, v0, v1);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n, GLint v0, GLint v1, GLint v2) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform3i(loc, v0, v1, v2);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n,
                               GLint v0, GLint v1, GLint v2, GLint v3) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniform4i(loc, v0, v1, v2, v3);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n, const math::Vec3f &v) {
  setUniform(n, v.x, v.y, v.z);
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}

void ShaderProgram::setUniform(string n, const math::Vec4f &v) {
  setUniform(n, v.x, v.y, v.z, v.w);
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}

void ShaderProgram::setUniform(string n, math::Mat3f &mat) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniformMatrix3fv(loc, 1, OZ_ISROWMAJOR, mat.m);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
void ShaderProgram::setUniform(string n, math::Mat4f &mat) {
  bind();
  GLint loc = getUniformLocation(n.c_str());
  if (loc > -1) {
      glUniformMatrix4fv(loc, 1, OZ_ISROWMAJOR, mat.m);
    }
  gl::checkError("Error in setUniform", __LINE__, __FILE__);
}
