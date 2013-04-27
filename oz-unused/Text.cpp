//
//  File.cpp
//  ModelVis
//
//  Created by Murphy M Stein on 1/12/13.
//  Copyright (c) 2013 Murphy M Stein. All rights reserved.
//

#define PATH_TO_DEFAULT_FONT "../fonts/"

#include <sstream>
#include "GL/Text.h"
#include "GL/ShaderProgram.h"

Text::Text(uint32_t windowWidth, uint32_t windowHeight) {

  winHeight = windowHeight;
  winWidth = windowWidth;

  // STATIC INITIALIZATIONS	////////////////////////////////////////////////////
  if (ft == nullptr) {
      if(FT_Init_FreeType(&ft)) {
          fprintf(stderr, "Could not init freetype library\n");
          // throw error here
        }
    }

  // LOAD FONT /////////////////////////////////////////////////////////////////
  if (face == nullptr) {
      stringstream ss;
      ss << PATH_TO_DEFAULT_FONT << "Arial.ttf";
      if(FT_New_Face(ft, ss.str().c_str(), 0, &face)) {
          fprintf(stderr, "Could not open font\n");
          // throw error here
        }

      if(FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
          fprintf(stderr, "Could not load character 'X'\n");
          // throw error here
          g = face->glyph;
        }

      FT_Set_Pixel_Sizes(face, 0, _text_size);

    }

  // LOAD SHADER ///////////////////////////////////////////////////////////////
  if (shader == nullptr) {
      shader = new ShaderProgram("fontglyph.v.glsl", "fontglyph.f.glsl");

      // PREPARE TEXTURE
      glActiveTexture(GL_TEXTURE0 + TEXTURE_UNIT);
      glGenTextures(1, &tex);

      vao.bind();
      vbo.bindAttribute(&vao, shader, "coord");
      vao.unbind();
      vbo.resize(4);

    }

}

void Text::drawString(string str, float x, float y) {

  y = winHeight - y;

  bindTexture();
  const char *p;
  const char *text = str.c_str();

  vao.bind();
  shader->setUniform("width", winWidth);
  shader->setUniform("height", winHeight);
  shader->bind();
  for(p = text; *p; p++) {
      if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
        continue;

      glTexImage2D(   GL_TEXTURE_2D,
                      0,
                      GL_R8,
                      g->bitmap.width,
                      g->bitmap.rows,
                      0,
                      GL_RED,
                      GL_UNSIGNED_BYTE,
                      g->bitmap.buffer
                      );

      float l = x + g->bitmap_left;
      float t = y + g->bitmap_top;
      float r = l + g->bitmap.width;
      float b = t - g->bitmap.rows;

      // draw CCW QUAD as Triangle Strip
      //
      //		2	------	3
      //		|	\			|
      //		|	  \		|
      //		|		  \	|
      //		0 ------	4
      //
      vbo[0].r = l;
      vbo[0].g = b;
      vbo[0].b = 0;
      vbo[0].a = 1;

      vbo[1].r = r;
      vbo[1].g = b;
      vbo[1].b = 1;
      vbo[1].a = 1;

      vbo[2].r = l;
      vbo[2].g = t;
      vbo[2].b = 0;
      vbo[2].a = 0;

      vbo[3].r = r;
      vbo[3].g = t;
      vbo[3].b = 1;
      vbo[3].a = 0;

      vbo.syncForce();
      glDisable(GL_CULL_FACE);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      x += (g->advance.x >> 6);
      y += (g->advance.y >> 6);
    }

  vao.unbind();

}

void Text::bindTexture() {
  glActiveTexture(GL_TEXTURE0 + TEXTURE_UNIT);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  shader->setUniform("tex", TEXTURE_UNIT);
}
