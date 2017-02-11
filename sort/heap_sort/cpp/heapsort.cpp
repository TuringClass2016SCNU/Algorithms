#include <iostream>
using namespace std;
int n;
int *arr;
bool build(int *);
bool swap(int &, int &);
bool heapify(int *, int);
int heapsort(int *, int);
int main() {
  int length;
  cin >> length;
  n = length;
  arr = new int[n + 1];
  for (int i = 1; i < n + 1; i++) {
    cin >> arr[i];
  }

  heapsort(arr, length);
  for (int i = 0; i < length; i++) {
    arr[i] = arr[i + 1];
    cout << arr[i] << " ";
  }
  return 0;
}
bool heapify(int *arr, int k) {
  int temp;
  int size = n;
  int l = 2 * k;
  int r = 2 * k + 1;

  if (l <= size && arr[l] > arr[k]) {
    temp = l;
  } else
    temp = k;
  if (r <= size && arr[r] > arr[temp]) {
    temp = r;
  }
  if (temp != k) {
    swap(arr[k], arr[temp]);
    heapify(arr, temp);
  }
  return 1;
}
bool build(int *arr) {
  for (int i = n / 2; i > 0; i--) {
    heapify(arr, i);
  }
  return 1;
}
int heapsort(int *arr, int k) {
  build(arr);
  for (int i = k; i > 1; i--) {
    swap(arr[1], arr[i]);
    n--;
    heapify(arr, 1);
  }
  return 1;
}
bool swap(int &a, int &b) {
  int temp;
  temp = b;
  b = a;
  a = temp;
  return 1;
}
