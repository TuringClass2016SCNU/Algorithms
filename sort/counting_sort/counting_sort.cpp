#include <cstring>
#include <iostream>
using namespace std;
int *csort(int *arr, int n, int k);
// input:  an array with non-negative elements;
// output: sorted array;
int main(int argc, char const *argv[]) {
  int *rw;
  int n, temp = -888888;
  // require all elements are non-negative
  // temp:load the largest one.
  cin >> n;
  int *arr = new int[n];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    if (arr[i] < 0) {
      cerr << "Error." << endl;
      return 0;
    }
    if (arr[i] >= temp)
      temp = arr[i];
  }
  rw = csort(arr, n, temp);
  for (int i = 0; i < n; i++) {
    cout << rw[i] << " ";
  }
  cout << endl;
  delete[] arr;
  return 0;
}

int *csort(int *arr, int n, int k) {
  int i;
  int *res = new int[n];
  int *temp = new int[k + 1];
  memset(temp, 0, sizeof(int) * (k + 1));
  for (i = 0; i < n; i++)
    temp[arr[i]]++;
  // the amount of each element;
  for (i = 1; i < k + 1; i++)
    temp[i] += temp[i - 1];
  // wrap up the sum of amount;
  for (i = n - 1; i > -1; i--) {
    res[temp[arr[i]] - 1] = arr[i];
    temp[arr[i]]--;
  }
  return res;
}
