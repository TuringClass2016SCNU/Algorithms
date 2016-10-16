#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

/* Quick sort's optimization;
 * Procedure:
 * 0.1 Input:line 1:n:stand for the count of the number;
             line 2:n number;
 * 0.2 Output: sorted sequence;
 *
 * 1.Create a random number, then set as a mid number;  (n>100)
 * 2.qs..........................................
 * 完啦。。。略略略。。*/
int random(double start, double end);
void qs(int n, int argv[], int former,
        int latter); // amount, sequence, former_pointer, latter_pointer;
int main() {
  int n; // amount;

  cin >> n;

  int *sequence = new int[n];
  for (int itor = 0; itor < n; itor++) {
    cin >> sequence[itor];
  }

  qs(n, sequence, 0, n - 1);
  for (int itor = 0; itor < n; itor++) {
    cout << sequence[itor] << " ";
  }
  delete[] sequence;
  return 0;
}

void qs(int n, int argv[], int former, int latter) {
  int i = former, j = latter;
  int mid = (former + latter) / 2;
  int choose;
  int swap_temp;
  if (latter - former > 100) {
    choose = random(n * 0.382, n * 0.618);
    swap_temp = argv[mid];
    argv[mid] = argv[choose];
    argv[choose] = swap_temp;
  }

  int mid_d = argv[(former + latter) / 2];
  do {
    while (argv[i] < mid_d) {
      i++;
    }

    while (mid_d < argv[j]) {
      j--;
    }
    if (i <= j) {
      swap_temp = argv[i];
      argv[i] = argv[j];
      argv[j] = swap_temp;
      i++;
      j--;
    }
  } while (i <= j);
  if (former < j)
    qs(n, argv, former, j);
  if (i < latter)
    qs(n, argv, i, latter);
}

int random(double start, double end) {
  srand(unsigned(time(0)));
  return start + (end - start) * rand() / (RAND_MAX + 1.0);
}
