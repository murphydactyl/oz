#ifndef __OZ__MATH__TRANSFORMBASEADDONS__H__
#define __OZ__MATH__TRANSFORMBASEADDONS__H__

  inline void translate(Scalar x, Scalar y, Scalar z) {
    translate(VectorType(x, y, z));
  }

  inline void rotateX(Scalar rads) {
    rotate(AngleAxis<Scalar>(rads, VectorType(1,0,0)));
  }

  inline void rotateY(Scalar rads) {
    rotate(AngleAxis<Scalar>(rads, VectorType(0,1,0)));
  }

  inline void rotateZ(Scalar rads) {
    rotate(AngleAxis<Scalar>(rads, VectorType(0,0,1)));
  }

  inline void setRotationX(Scalar rads) {
    VectorType t = translation();
    setIdentity();
    rotateX(rads);
    pretranslate(t);
  }

  inline void setRotationY(Scalar rads) {
    VectorType t = translation();
    setIdentity();
    rotateY(rads);
    pretranslate(t);
  }

  inline void setRotationZ(Scalar rads) {
    VectorType t = translation();
    setIdentity();
    rotateZ(rads);
    pretranslate(t);
  }


#endif
