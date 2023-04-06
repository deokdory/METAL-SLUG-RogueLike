#include "Framework.h"
#include "RealRandom.h"

double randfrom(double min, double max) {
  if (max < min) std::swap(min, max);
  double range = max - min;
  double div = RAND_MAX / range;
  double temp[5];

  temp[0] = rand() / div;
  temp[1] = rand() / div;
  temp[2] = rand() / div;
  temp[3] = rand() / div;
  temp[4] = rand() / div;
    
  return temp[rand() % 5];
}