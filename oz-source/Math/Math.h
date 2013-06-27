#ifndef __OZ__MATH__H__
#define __OZ__MATH__H__

#define EIGEN_NO_DEBUG
#define EIGEN_TRANSFORM_PLUGIN "Math/TransformBaseAddons.h"
#define OZ_ISROWMAJOR true
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace Math {

  const double PI = 3.1415926535897932384626433832795;
  const double TAU = 2 * PI;

#if OZ_ISROWMAJOR
  typedef Eigen::Transform<float,2,Eigen::Affine, Eigen::RowMajor> Aff2f;
  typedef Eigen::Matrix<float,3,3, Eigen::RowMajor> Mat3f;
  typedef Eigen::Matrix<float,4,4, Eigen::RowMajor> Mat4f;
#else
  typedef Eigen::Transform<float,2,Eigen::Affine, Eigen::ColMajor> Aff2f;
  typedef Eigen::Matrix<float,3,3, Eigen::ColMajor> Mat3f;
  typedef Eigen::Matrix<float,4,4, Eigen::ColMajor> Mat4f;
#endif

  typedef Eigen::Matrix<float, 2, Eigen::Dynamic, Eigen::ColMajor> Mat2Xf;
  typedef Eigen::Matrix<float, 3, Eigen::Dynamic, Eigen::ColMajor> Mat3Xf;
  typedef Eigen::Matrix<float, 4, Eigen::Dynamic, Eigen::ColMajor> Mat4Xf;
  typedef Eigen::Matrix<uint16_t, 3, Eigen::Dynamic, Eigen::ColMajor> Mat3Xu16;

  typedef Eigen::Vector3f Vec3f;
  typedef Eigen::Vector4f Vec4f;
}

#endif
