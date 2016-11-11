#include <iostream>

/* print a int array
  @param (int []) the array to be printed
  @param (int) the length of the array
  @return (int) status code (0 - success, other - fail)
*/
int print(int arr[], int length){
  for(int i = 0; i < length; ++i){
    std::cout << arr[i];
    if(i != length - 1){
      std::cout << ' ';
    }
  }
  std::cout << std::endl;
  return 0;
}

/* sort int array from low to high by bubble sort
  @param (int []) the array to be sorted
  @oaram (int) the length of the array
  @return (int) status code (0 - success, other - fail)
  @note the array will be changed
*/
int bubble_sort(int arr[], int length){
  for(int i = 0; i < length - 1; ++i){
    // bool flag follows if everything is in order in next loop
    bool flag = true;
    for(int j = length - 1; j > i; --j){
      if(arr[j] < arr[j - 1]){
        // swap the wrong ordered int
        int tmp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = tmp;

        // set flag true for marking something is changed in this loop
        flag = true;
      }
    }

    // if everything is in order in the last loop
    if(flag == false){
      break;
    }
  }

  return 0;
}

int main(){
  int arr[] = {5, 4, 7, 12, 4, 9, 2, 1, 13, 2};
  int length = 10;

  print(arr, length);
  bubble_sort(arr, length);
  print(arr, length);

  return 0;
}
