#ifndef __OZ__MATH__H__
#define __OZ__MATH__H__

#include <Eigen/Dense>

typedef Eigen::Matrix3f Mat3f;
typedef Eigen::Matrix4f Mat4f;

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
  inline float x() { return data()[0]; }
  inline float y() { return data()[1]; }
  inline float z() { return data()[2]; }

  inline float x() const { return data()[0]; }
  inline float y() const { return data()[1]; }
  inline float z() const { return data()[2]; }

};

#endif
