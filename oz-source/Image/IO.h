// Image/IO.h
// Functions for loading and saving images from the
// filesystem using FreeImage Library.
#ifndef __OZ__IMAGE__IO__H
#define __OZ__IMAGE__IO__H

#include <iostream>

namespace image {
  void init();
  uint8_t* LoadPNGRGBA8888(std::string filename, uint32_t& imWidth, uint32_t& imHeight);
  void cleanup();
}

#endif
