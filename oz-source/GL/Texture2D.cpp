#include "GL/Texture2D.h"
#include <typeinfo>
#include <iostream>

using namespace std;
using namespace gl;


template <class T>
Texture2D<T>::Texture2D(uint32_t width, uint32_t height)
{
  T* src = new T[width * height];
  init(src, width, height);
}

template <class T>
Texture2D<T>::Texture2D(T* src, uint32_t width, uint32_t height)
{
  init(src, width, height);
}

template <class T>
void Texture2D<T>::init(T* src, uint32_t width, uint32_t height)
{
  cout << "Creating new texture with pixel size: " << sizeof(T) << " bytes" << endl;
  width_ = width;
  height_ = height;
  data_ = src;

  if (typeid(T) == typeid(rgba32f_t)) {
    glInternalFormat_ = GL_RGBA32F;
    glFormat_ = GL_RGBA;
    glType_ = GL_FLOAT;
  } else if (typeid(T) == typeid(rgba32i_t)) {
    glInternalFormat_ = GL_RGBA32I;
    glFormat_ = GL_RGBA_INTEGER;
    glType_ = GL_INT;
  } else if (typeid(T) == typeid(rgba8888_t)) {
    glInternalFormat_ = GL_RGBA8;
    glFormat_ = GL_BGRA;
    glType_ = GL_UNSIGNED_INT_8_8_8_8_REV;
  }
  initOnGPU();
}

template <class T>
void Texture2D<T>::initOnGPU()
{
  gl::checkError("before initOnGPU");
  glGenTextures(1, &glName_);
  bind();
  glTexImage2D(GL_TEXTURE_2D,     // target
               0,                 // level, 0 = base, no minimap,
               glInternalFormat_, // internalformat
               width_,            // width
               height_,           // height
               0,                 // border, always 0 in OpenGL ES
               glFormat_,         // format
               glType_,           // type
               NULL);             // pixels themselves
  gl::checkError("after initOnGPU");
}

template <class T>
void Texture2D<T>::bind(uint8_t textureUnit)
{
  gl::checkError("Texture2D @ bind");
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(GL_TEXTURE_2D, glName_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  gl::checkError("Texture2D finished bind");
}

template <class T>
Texture2D<T>::~Texture2D()
{
  glDeleteTextures(1, &glName_);
  delete data_;
}

template <class T>
T* Texture2D<T>::data()
{
  return data_;
}

template <class T>
void Texture2D<T>::copy2GPU()
{
  bind();
  glTexSubImage2D(GL_TEXTURE_2D,
                  0,
                  0,
                  0,
                  width_,
                  height_,
                  glFormat_,
                  glType_,
                  ptr2RawData());
}

template <class T>
void Texture2D<T>::copy2CPU()
{
  bind();
  glGetTexImage(GL_TEXTURE_2D, 0, glFormat_, glType_, ptr2RawData());
//  for (int i = 0; i < 10; i++) {
//    cout << (int)data_[i].r << " ";
//    cout << (int)data_[i].g << " ";
//    cout << (int)data_[i].b << " ";
//    cout << (int)data_[i].a << endl;
//  }
}


template <class T>
uint32_t Texture2D<T>::width() {
  return width_;
}

template <class T>
uint32_t Texture2D<T>::height() {
  return height_;
}

template <class T>
char* Texture2D<T>::ptr2RawData() {
  return reinterpret_cast<char*>(data_);
}



/******************************************************************************
 * EXPLICIT INSTATIATIONS
 *****************************************************************************/
namespace gl {

  template class Texture2D<rgba32f_t>;
  template class Texture2D<rgba32i_t>;
  template class Texture2D<rgba8888_t>;

}
