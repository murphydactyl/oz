//
//  shader.cpp
//  GLFW
//
//  Created by Murphy M Stein on 9/26/12.
//  Copyright (c) 2012 Murphy M Stein. All rights reserved.
//
// COPIED DIRECTLY FROM THE WEB AT
// http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_02

#include "GL/Shader.h"
#include <sstream>

using namespace gl;

////////////////////////////////////////////////////////////////////////////////
// SHADER LIBRARY --------------------------------------------------------------

library_t Shader::library;
ShaderLibrary::~ShaderLibrary() {
  cout << "ShaderLibrary destructor called" << endl;
  for (auto &pair : *this) {
    Shader* shader = (Shader*)(pair.second);
    delete shader;
  }
}

Shader::Shader() {
  _glName = 0;
}

Shader::~Shader() {
  glDeleteShader(_glName);
}

/**
 * Store all the file's contents in memory, useful to pass shaders
 * source code to OpenGL
 */
/* Problem:
 *  We should close the input file before the return NULL; statements but this would lead to a lot of repetition (DRY)
 *   -you could solve this by using goto or by abusing switch/for/while + break or by building an if else mess
 *  better solution: let the user handle the File: char* file_read(const FILE* input)
 */
char* Shader::loadSourceFromFile(const char* filename)
{
  FILE* input = fopen(filename, "rb");
  if(input == NULL) return nullptr;

  if(fseek(input, 0, SEEK_END) == -1) return nullptr;
  long size = ftell(input);
  if(size == -1) return nullptr;
  if(fseek(input, 0, SEEK_SET) == -1) return nullptr;

  /*if using c-compiler: dont cast malloc's return value*/
  char *content = (char*) malloc( (size_t) size +1  );
  if(content == NULL) return nullptr;

  fread(content, 1, (size_t)size, input);
  if(ferror(input)) {
    free(content);
    return nullptr;
  }

  fclose(input);
  content[size] = '\0';
  return content;
}

/**
 * Display compilation errors from the OpenGL shader compiler
 */
void Shader::print_log(GLuint object)
{
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

/**
 * Compile the shader from file 'filename', with error handling
 */
GLuint Shader::compileSource(const char* source, ShaderType type)
{
  GLuint glName = glCreateShader(type);
  const char* completeSource[2] = {GLSL_VERSION, source};
  glShaderSource(glName, 2, completeSource, NULL);
  glCompileShader(glName);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(glName, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
    cout << "ERROR COMPILING SHADER:" << endl;
    print_log(glName);
    cout << "-----------------------------------------" << endl;
    cout << completeSource[0] << completeSource[1] << endl;
    cout << "-----------------------------------------" << endl;
    glDeleteShader(glName);
    return 0;
  } else {
  }
  return glName;
}

Shader* Shader::load(string filename, ShaderType st) {

  // CONSTRUCT ABSOLUTE PATH
  string path = constructAbsolutePathFromDefaultShaderDirPath(filename);

  // RETRIEVE EXISTING SHADER IF IT EXISTS
  Shader* shader = retrieveCompiledShader(path);
  if (shader != nullptr) {
    //cout << "Reusing shader for file: " << path << endl;
    return shader;
  }

  // SHADER DOESN'T EXIST SO CREATE A NEW ONE
  shader = new Shader();

  // GET SOURCE FROM FILE
  char* source = loadSourceFromFile(path.c_str());
  if (source == nullptr) {
    cout << "Couldn't load shader source from file: " << path << endl;
    return nullptr;
  }

  // COMPILE NEW SHADER OF APPROPRIATE TYPE WITH SOURCE
  GLuint glName = compileSource(source, st);
  // FREE SOURCE STRING NOW
  free(source);

  // SET MEMBER VARIABLES ON SUCCESS
  if (glName != 0) {
    shader->_absolute_path = path;
    shader->_filename = filename;
    shader->_glName = glName;

    // ADD SHADER TO LIBRARY
    addShaderToLibrary(shader);

    return shader;
  }

  // FAILURE
  delete shader;
  cout << "CATASTROPHIC SHADER FAIL..." << endl;
  return nullptr;
}


Shader* Shader::loadString(string name, string src, ShaderType st) {

  // CONSTRUCT ABSOLUTE PATH
  stringstream ss;
  ss << "dynamic-" << name;
  string path = ss.str();

  // RETRIEVE EXISTING SHADER IF IT EXISTS
  Shader* shader = retrieveCompiledShader(path);
  if (shader != nullptr) {
    //cout << "Reusing shader for file: " << path << endl;
    return shader;
  }

  // SHADER DOESN'T EXIST SO CREATE A NEW ONE
  shader = new Shader();

  // COMPILE NEW SHADER OF APPROPRIATE TYPE WITH SOURCE
  GLuint glName = compileSource(src.c_str(), st);

  // SET MEMBER VARIABLES ON SUCCESS
  if (glName != 0) {
    shader->_absolute_path = path;
    shader->_filename = name;
    shader->_glName = glName;

    // ADD SHADER TO LIBRARY
    addShaderToLibrary(shader);

    return shader;
  }

  // FAILURE
  delete shader;
  cout << "CATASTROPHIC SHADER FAIL..." << endl;
  return nullptr;
}

string Shader::constructAbsolutePathFromDefaultShaderDirPath(string filename) {
  stringstream pathMaker;
  string defaultDirectory(SHADER_PATH);
  if (defaultDirectory.back() != '/') {
    defaultDirectory.push_back('/');
  }
  pathMaker << defaultDirectory << filename;
  return pathMaker.str();
}


Shader* Shader::retrieveCompiledShader(string full_filename) {
  auto record = library.find(full_filename);
  if (record == library.end()) {
    return nullptr;
  }
  //cout << "Found shader named " << full_filename << endl;
  return record->second;
}

void Shader::addShaderToLibrary(Shader* shader) {
  string key;
  if (LIBRARY_USES == ABSOLUTE_PATHS) {
    key = shader->_absolute_path;
  } else {
    key = shader->_filename;
  }
  library.insert(std::pair<string, Shader*>(key, shader));
  //cout << "Library size: " << library.size() << endl;
}
