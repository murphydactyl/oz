#ifndef __OZ__GEOMETRY__BONE__H__
#define __OZ__GEOMETRY__BONE__H__

#include "Math/Math.h"
#include "Geometry/Geometry.h"
#include <string>

namespace geom {

  class Bone {
    typedef math::Mat4f Mat4;

    public:
      Bone() {
        offset.identity();
        final.identity();
      }

      // Member variables -----------------------------------------------
      Mat4 offset;
      Mat4 final;
      std::string name;
  };

}
#endif
