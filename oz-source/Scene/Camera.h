#ifndef __OZ__SCENE__CAMERA__H__
#define __OZ__SCENE__CAMERA__H__

#include "../Math/Math.h"
#include "Scene/Node.h"

namespace scene {

  template<typename Scalar=float>
  class Camera : public Node<Scalar> {
    public:
      typedef math::Vec3f Vec3;
      typedef math::Mat4f Mat4;

      Camera() {
        anim_.identity();
        pos_.identity();
        rot_.identity();
        this->perspective_.identity();
      }

      void translate(Scalar x, Scalar y, Scalar z) {
        Vec3 t = (rot_ * anim_) * Vec3(x, y, z);
        pos_.translate(t);
      }

      Mat4 view() {
        Mat4 v = pos_ * rot_ * anim_;
        return v.affineInverse();
      }

      Mat4& anim() { return anim_; }

      void makeAnimationPermanent() {
        this->rot_ = this->rot_ * anim_;
        anim_.identity();
      }
      Mat4     perspective() { return this->perspective_; }

    protected:
      Mat4 perspective_;
      Mat4 anim_;
      Mat4 rot_;
      Mat4 pos_;
  };


  template<typename Scalar=float>
  class CameraOrtho : public Camera<Scalar> {
    public:

      CameraOrtho(double width, double height, double near, double far) {
        widthInPixels_ = width;
        heightInPixels_ = height;
        right_ = width/2;
        left_ = -right_;
        top_ = height/2;
        bottom_ = -top_;
        near_ = near;
        far_ = far;

        this->perspective_(0,0) = 2/(right_-left_);
        this->perspective_(0,1) = 0;
        this->perspective_(0,2) = 0;
        this->perspective_(0,3) = 0;
        this->perspective_(1,0) = 0;
        this->perspective_(1,1) = 2/(top_-bottom_);
        this->perspective_(1,2) = 0;
        this->perspective_(1,3) = 0;
        this->perspective_(2,0) = 0;
        this->perspective_(2,1) = 0;
        this->perspective_(2,2) = -2/(far_-near_);
        this->perspective_(2,3) = -(far_+near_)/(far_-near_);
        this->perspective_(3,0) = 0;
        this->perspective_(3,1) = 0;
        this->perspective_(3,2) = 0;
        this->perspective_(3,3) = 1;
      }

    protected:
      double widthInPixels_;
      double heightInPixels_;
      double near_;
      double far_;
      double left_;
      double top_;
      double bottom_;
      double right_;
  };

  template<typename Scalar=float>
  class CameraPerspective : public Camera<Scalar> {
    public:

      CameraPerspective(double width, double height, double near, double far) {
        widthInPixels_ = width;
        heightInPixels_ = height;
        right_ = width/2;
        left_ = -right_;
        top_ = height/2;
        bottom_ = -top_;
        near_ = near;
        far_ = far;

        this->perspective_(0,0) = 2 * near_ / (right_-left_);
        this->perspective_(0,1) = 0;
        this->perspective_(0,2) = (right_+left_) / (right_-left_);
        this->perspective_(0,3) = 0;
        this->perspective_(1,0) = 0;
        this->perspective_(1,1) = 2 * near_ /(top_-bottom_);
        this->perspective_(1,2) = (top_+bottom_)/(top_-bottom_);
        this->perspective_(1,3) = 0;
        this->perspective_(2,0) = 0;
        this->perspective_(2,1) = 0;
        this->perspective_(2,2) = -(far_+near_)/(far_-near_);
        this->perspective_(2,3) = -2*far_*near_/(far_-near_);
        this->perspective_(3,0) = 0;
        this->perspective_(3,1) = 0;
        this->perspective_(3,2) = -1;
        this->perspective_(3,3) = 0;
      }

    protected:
      double widthInPixels_;
      double heightInPixels_;
      double near_;
      double far_;
      double left_;
      double top_;
      double bottom_;
      double right_;
  };

  typedef Camera<float> Cameraf;

}

#endif
