// Image/IO.cpp
// Implementation of functions for loading and saving
// images from the filesystem using FreeImage Library
// FreeImage requires one-time pre-initialization
// and de-initialization and this is handled automatically
// by calling init() from every function depending on FreeImage.
// These calls should probably be the first line of each function.
// TODO: save png
// TODO: load/save jpg

#include "Image/IO.h"
#include <FreeImage.h>
#include <thread>
#include <mutex>

// This function is called exactly once.  And it initializes
// the underlying FreeImage library.  It may be safely called
// by each and every function requiring FreeImage without
// worry that FreeImage will be initialized multiple times.
// It is also lazy, in the sense that FreeImage is not initialized
// until this function is called.  And as soon as its called once,
// it adds the cleanup method to **atexit** so that it can be properly
// deinitialized.
void image::init() {
  std::once_flag flag;
  std::call_once(flag, []()
  {
    std::cout << "Initializing FreeImage...";
    FreeImage_Initialise();
    atexit(image::cleanup);
    std::cout << "Done." << std::endl;
  });
}

// This function deinitializes FreeImage.  It ensures that it
// called exactly once, and it will only be called if init() was called.
void image::cleanup() {
  std::once_flag flag;
  std::call_once(flag, []()
  {
    std::cout << "Deinitializing FreeImage...";
    FreeImage_DeInitialise();
    std::cout << "Done." << std::endl;
  });
}

// Load an image from a file and return it as a 32-bit RGBA
// If the image could not be loaded, the return value is null,
// and the width and height are set to 0.  If the source image is
// 24-bit it is automatically converted to 32-bit.  The caller
// is responsible for freeing the returned memory if any.
uint8_t* image::LoadPNGRGBA8888(std::string filename, uint32_t& width, uint32_t& height) {
  init();
  FIBITMAP* src = FreeImage_Load(FIF_PNG, filename.c_str());
  if (src == nullptr) {
    std::cout << "Couldn't load image " << filename << std::endl;
    return nullptr;
  }

  // If the image loaded successfully is 24-bits per pixel or less
  // convert it to 32-bits and free the old version's memory
  if (FreeImage_GetBPP(src) != 32) {
    // convert to 32 bits
    FIBITMAP* src24 = src;
    src = FreeImage_ConvertTo32Bits(src24);
    width = 0;
    height = 0;
    FreeImage_Unload(src24);
  }

  // allocate memory for raw image which is to be returned
  // TODO: check for errors
  width = FreeImage_GetWidth(src);
  height = FreeImage_GetHeight(src);
  int scan_width = FreeImage_GetPitch(src);
  BYTE *bits = (BYTE*)malloc(height * scan_width);

  FreeImage_ConvertToRawBits(bits, src, scan_width, 32,
                             FI_RGBA_RED_MASK,
                             FI_RGBA_BLUE_MASK,
                             FI_RGBA_GREEN_MASK,
                             FALSE);

  FreeImage_Unload(src);

  return bits;

}

