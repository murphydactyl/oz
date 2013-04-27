#include <iostream>
#include <Eigen/Dense>

#include "Math/Math.h"

using namespace std;

int main()
{

  Vec4f a;
  a(0) = 1;
  a(1) = 2;
  a(2) = 3;
  a(3) = 4;
  Vec4f b = a;
  cout << a.x() << " " << a.y() << " " << a.z() << " " << a.w() << endl;
  cout << b << endl;

  Eigen::Matrix4d A;
  A(1,1) = 2;
  auto f = 1 + 2;
  cout << "f: " << f << endl;
  cout << "A is " << A << endl;
  cout << "Hello World! How are you?" << endl;
  return 0;
}

