#ifndef __OZ__MATH__H__
#define __OZ__MATH__H__

#define EIGEN_NO_DEBUG
#define EIGEN_TRANSFORM_PLUGIN "Math/TransformBaseAddons.h"
#define OZ_ISROWMAJOR true
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "../../math/include/matrix3.h"
#include "../../math/include/matrix4.h"
#include "../../math/include/vector3.h"
#include "../../math/include/vector4.h"

namespace math {

  const double PI = 3.1415926535897932384626433832795;
  const double TAU = 2 * PI;

  //#if OZ_ISROWMAJOR
  //  typedef Eigen::Transform<float,2,Eigen::Affine, Eigen::RowMajor> Aff2f;
  //  typedef Eigen::Matrix<float,3,3, Eigen::RowMajor> Mat3f;
  //  typedef Eigen::Matrix<float,4,4, Eigen::RowMajor> Mat4f;
  //#else
  //  typedef Eigen::Transform<float,2,Eigen::Affine, Eigen::ColMajor> Aff2f;
  //  typedef Eigen::Matrix<float,3,3, Eigen::ColMajor> Mat3f;
  //  typedef Eigen::Matrix<float,4,4, Eigen::ColMajor> Mat4f;
  //#endif

  typedef m3d::Float3x3 Mat3f;
  typedef m3d::Float4x4 Mat4f;

  typedef m3d::Float3 Vec3f;
  typedef m3d::Float4 Vec4f;

  typedef Eigen::Matrix<float, 2, Eigen::Dynamic, Eigen::ColMajor> Mat2Xf;
  typedef Eigen::Matrix<float, 3, Eigen::Dynamic, Eigen::ColMajor> Mat3Xf;
  typedef Eigen::Matrix<float, 4, Eigen::Dynamic, Eigen::ColMajor> Mat4Xf;
  typedef Eigen::Matrix<uint16_t, 3, Eigen::Dynamic, Eigen::ColMajor> Mat3Xu16;

}

#endif
