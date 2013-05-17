#include <iostream>
#include <Eigen/Dense>
#include <time.h>
#include "Math/Math.h"

using namespace std;

struct T {
 const int nChannels = 2;
 float a = 2;
 float b = 3;
};

int main()
{

  T t;
  cout << "sizeof T: " << sizeof(t) << endl;

  return 0;
}

