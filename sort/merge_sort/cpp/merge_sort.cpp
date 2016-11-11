#include <cmath>
#include <iostream>
using namespace std;
void merge_sort(int argv[], int pre, int r);
void merge(int argv[], int pre, int mid, int r);
int *argv;
/*
 *  file: merge_sort.cpp
 *  brief: Input an array of certain numbers, sorting it by merge;
 *
 *      The merge sort algorithm uses the divide and conquer algorithms.
 *  Firstly devide the array into several parts. When it is devided into
 *  the small ones(only one complement), the broken array start to sort up.
 *  It uses the recursive method to solve the problem.
 *      At the beginning, the main function get the count of the array and
 * create the array. Then input the pointer and array into the sort function.
 * When the sub-arrays contains more than 1 element, they are devided into 2
 * parts repeatedly.
 *
 */
int main() {
  int n;
  cin >> n; // Input the count;
  argv = new int[n + 1];
  for (int i = 0; i < n; i++) {
    cin >> argv[i]; // Input every element;
  }
  merge_sort(argv, 0, n - 1);
  for (size_t i = 0; i < n; i++) {
    cout << argv[i] << " ";
  }
  delete[] argv;
  return 0;
}
void merge_sort(int argv[], int pre, int r) {
  // parameters: argv[]: the main array;
  //             pre   : the first one of the sub-array;
  //             r     : the last one of the sub-array;
  if (pre < r) {
    int mid = (pre + r) / 2;
    merge_sort(argv, pre, mid);
    merge_sort(argv, mid + 1, r);
    merge(argv, pre, mid, r);
  }
}
void merge(int argv[], int pre, int mid, int r) {
  /*  parameters:
   *    argv[]: the main array;
   *    pre:    the first one of the sub-array;
   *    mid:    the middium one of it;
   *    r  :    the last one.
   *
   *  output: partically sorted array.
   */

  int n_1 = mid - pre + 1;
  int n_2 = r - mid;
  int *Lt = new int[n_1];
  // new and store(or define as)the Left sight of the array;
  int *Rt = new int[n_2];
  // new and store(or define as)the Right sight of the array;
  int i, j;
  // Do as iterator and pointer;

  for (i = 0; i < mid - pre + 1; i++) {
    Lt[i] = argv[pre + i];
  }
  for (i = 0; i < r - mid; i++) {
    Rt[i] = argv[mid + i + 1];
  }
  // Temperorily store the two sizes of number;

  i = 0; //
  j = 0; // Initalize the pointer;
  int k = pre;
  while (k <= r && i < n_1 && j < n_2) { /// TEST CODE if (i < n_1 && j < n_2)
    {
      if (Lt[i] < Rt[j]) {
        argv[k] = Lt[i];
        i++;
      } else { /// TEST CODE (Lt[i] > Rt[j])
        argv[k] = Rt[j];
        j++;
      }
    }
    k++;
  }
  /*  ///TEST CODE
    if (i >= n_1 && j < n_2) {
      argv[k] = Rt[j];
      j++;
    }
    if (j >= n_2 && i < n_1) {
      argv[k] = Lt[i];
      i++;
    }
    k++;
    for (size_t gg = 0; gg <= k; gg++) {
      cout << "---" << argv[gg] << "---" << endl;
    }
    cout << endl;
  }*/
  while (j < n_2) {
    argv[k++] = Rt[j++];
  }
  while (i < n_1) {
    argv[k++] = Lt[i++];
  }
  delete[] Rt;
  delete[] Lt;
}
