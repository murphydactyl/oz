#ifndef __OZ__GL__PIXELTYPES__H__
#define __OZ__GL__PIXELTYPES__H__

namespace gl {

  typedef struct pixeltype_t {} pixeltype_t;

  typedef struct rgba8888_t : pixeltype_t
  {
    typedef uint8_t channelType;
    channelType r;
    channelType g;
    channelType b;
    channelType a;
  } rgba8888_t;

  typedef struct rgba32f_t : pixeltype_t
  {
    typedef float channelType;
    channelType r;
    channelType g;
    channelType b;
    channelType a;
  } rgba32f_t;

  typedef struct rgba32i_t : pixeltype_t
  {
    typedef int channelType;
    channelType r;
    channelType g;
    channelType b;
    channelType a;
  } rgba32i_t;
}

#endif

