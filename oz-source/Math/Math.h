#ifndef __OZ__MATH__H__
#define __OZ__MATH__H__

#define EIGEN_NO_DEBUG
#define EIGEN_TRANSFORM_PLUGIN "Math/TransformBaseAddons.h"
#define OZ_ISROWMAJOR true
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "matrix3.h"
#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"

namespace math {

  const double PI = 3.1415926535897932384626433832795;
  const double TAU = 2 * PI;

  typedef m3d::Float3x3 Mat3f;
  typedef m3d::Float4x4 Mat4f;

  typedef m3d::Float3 Vec3f;
  typedef m3d::Float4 Vec4f;

  typedef Eigen::Matrix<float, 2, Eigen::Dynamic, Eigen::ColMajor> Mat2Xf;
  typedef Eigen::Matrix<float, 3, Eigen::Dynamic, Eigen::ColMajor> Mat3Xf;
  typedef Eigen::Matrix<float, 4, Eigen::Dynamic, Eigen::ColMajor> Mat4Xf;
  typedef Eigen::Matrix<float, 16, Eigen::Dynamic, Eigen::ColMajor> Mat16Xf;
  typedef Eigen::Matrix<uint32_t, 16, Eigen::Dynamic, Eigen::ColMajor> Mat16Xu;
  typedef Eigen::Matrix<uint16_t, 3, Eigen::Dynamic, Eigen::ColMajor> Mat3Xu16;

}

#endif
