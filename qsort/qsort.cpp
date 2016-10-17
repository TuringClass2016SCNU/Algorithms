#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
/* Quick sort's optimization;
 * Procedure:
 * 0.1 Input:line 1:n:stand for the count of the number;
             line 2:n number;
 * 0.2 Output: sorted sequence;
 *
 * 1.Create a random number, then set as a mid number;  (n>100)
 * 2.qs..........................................
 * 完啦。。。略略略。。*/
using namespace std;
int *sequence;
int random(double start, double end);
void qs(int n, int argv[], int former,
        int latter); // amount, sequence, former_pointer, latter_pointer;
void swap(int &a, int &b);
int main() {
  int n; // amount;

  cin >> n;

  sequence = new int[n];
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
  int temp_former = former, temp_latter = latter;
  int mid = (former + latter) / 2;
  int choose;

  if (latter - former > 100) {
    choose = random(n * 0.382, n * 0.618);
    swap(argv[mid], argv[choose]);
  }

  int mid_d = argv[(former + latter) / 2];
  do {
    while (argv[temp_former] < mid_d) {
      temp_former++;
    }

    while (mid_d < argv[temp_latter]) {
      temp_latter--;
    }
    if (temp_former <= temp_latter) {
      swap(argv[temp_former], argv[temp_latter]);
      temp_former++;
      temp_latter--;
    }
  } while (temp_former <= temp_latter);
  if (former < temp_latter)
    qs(n, argv, former, temp_latter);
  if (temp_former < latter)
    qs(n, argv, temp_former, latter);
}

int random(double start, double end) {
  srand(unsigned(time(0)));
  return start + (end - start) * rand() / (RAND_MAX + 1.0);
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}
