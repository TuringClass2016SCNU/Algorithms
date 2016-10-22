#include <cmath>
#include <cstdlib>
#include <ctime>




int random(double start, double end) {
  srand(unsigned(time(0)));
  return start + (end - start) * rand() / (RAND_MAX + 1.0);
}
