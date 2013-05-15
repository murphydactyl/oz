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
          glGenVertexArrays(1, &vao_);
          gl::checkError("VAO finished constructor");
      }

      ~VertexArrayObject() { glDeleteVertexArrays(1, &vao_); }
      void bind() { glBindVertexArray(vao_); }
      void unbind() { glBindVertexArray(0); }

  protected:
      GLuint vao_;
  };
}

#endif
