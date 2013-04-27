//
//  File.h
//  ModelVis
//
//  Created by Murphy M Stein on 1/12/13.
//  Copyright (c) 2013 Murphy M Stein. All rights reserved.
//

#ifndef __ModelVis__Text__
#define __ModelVis__Text__

#include <iostream>
#include <ft2build.h>
#include "GL/GLContext.h"

#include FT_FREETYPE_H

using namespace std;

class ShaderProgram;
class App;
class Text {
public:
  Text(uint32_t windowWidth, uint32_t windowHeight);
  void drawString(string str, float x, float y);

protected:
  FT_Library ft = nullptr;
  FT_Face face = nullptr;
  FT_GlyphSlot g = nullptr;
  ShaderProgram* shader = nullptr;

  GLuint tex;
  VertexBuffer<rgba32f_t> vbo;
  VAOBase vao;

  void bindTexture();
  const int TEXTURE_UNIT = 7;
  bool _bUsePixelAlignment;
  uint32_t winWidth;
  uint32_t winHeight;

  uint32_t _text_size = 18;

};
#endif /* defined(__ModelVis__Text__) */
