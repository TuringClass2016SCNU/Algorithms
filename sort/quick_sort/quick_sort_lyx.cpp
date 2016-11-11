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

/* sort int array from low to high by quick sort
  @param (int []) the array to be sorted
  @oaram (int) the first pos of the array
  @param (int) the last pos of the array
  @return (int) status code (0 - success, other - fail)
  @note the array will be changed
*/
int quick_sort(int arr[], int first, int last){
  // if only 1 int in the array
  if(first + 1 >= last){
    return 0;
  }

  int key = arr[first];
  int i = first + 1, j = last - 1;

  while(i != j){
    // find disordered int
    while(i != j && arr[j] >= key){
      --j;
    }
    while(i != j && arr[i] < key){
      ++i;
    }

    if(i != j){
      // swap the found int
      int tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
    }
  }

  // swap the last found less one and key
  if(key > arr[i]){
    arr[first] = arr[i];
    arr[i] = key;
    quick_sort(arr, first, i);
    quick_sort(arr, i + 1, last);
  }
  else{
    quick_sort(arr, i, last);
  }

  return 0;
}

int main(){
  int arr[] = {1, 8, 7, 5, 6, 9, 37, 51, 99, 68, 3, 7, 21, 23, 36, 6, 48, 8, 54, 44};
  int length = 20;

  print(arr, length);
  quick_sort(arr, 0, length);
  print(arr, length);

  return 0;
}
