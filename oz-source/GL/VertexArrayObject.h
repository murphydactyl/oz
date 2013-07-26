//
//  vaobase.h
//  ModelVis
//
//  Created by Murphy M Stein on 1/4/13.
//  Copyright (c) 2013 Murphy M Stein. All rights reserved.
//

#ifndef __OZ__GL__VERTEXARRAYOBJECT__H__
#define __OZ__GL__VERTEXARRAYOBJECT__H__

#include "GL/GLContext.h"

namespace gl {
  class VertexArrayObject {
  public:
      VertexArrayObject() {
          gl::checkError("VAO @ constructor");
          glGenVertexArrays(1, &glName);
          gl::checkError("VAO finished constructor");
      }
      ~VertexArrayObject() {
        gl::checkError("VAO @ destructor");
        glDeleteVertexArrays(1, &glName);
        gl::checkError("VAO @ destructor");
      }
      void bind() {
        gl::checkError("VAO @ before bind");
        glBindVertexArray(glName);
        gl::checkError("VAO @ after bind");
      }
      void unbind() {
        gl::checkError("VAO @ before unbind");
        glBindVertexArray(0);
        gl::checkError("VAO @ after unbind");
      }

  protected:
      GLuint glName;
  };
}

#endif
