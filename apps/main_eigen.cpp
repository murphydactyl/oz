#include <iostream>
#include <Eigen/Dense>
#include <time.h>
#include "Math/Math.h"

using namespace std;

int main()
{

  Eigen::MatrixXf A;
  A.resize(10,3);
  A.row(2) << 1, 2, 3;
  cout << A << endl;
  return 0;
}

