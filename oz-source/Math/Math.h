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


  class Vec4f : public Eigen::Vector4f
  {
  public:
    inline float x() { return data()[0]; }
    inline float y() { return data()[1]; }
    inline float z() { return data()[2]; }
    inline float w() { return data()[3]; }

    inline float x() const { return data()[0]; }
    inline float y() const { return data()[1]; }
    inline float z() const { return data()[2]; }
    inline float w() const { return data()[3]; }
  };

  class Vec3f : public Eigen::Vector3f
  {
  public:
    Vec3f(float a, float b, float c) : Eigen::Vector3f(a,b,c) {}

    inline float x() { return data()[0]; }
    inline float y() { return data()[1]; }
    inline float z() { return data()[2]; }

    inline float x() const { return data()[0]; }
    inline float y() const { return data()[1]; }
    inline float z() const { return data()[2]; }

  };
}

#endif
