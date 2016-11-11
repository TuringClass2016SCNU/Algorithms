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

/* merge two ordered arrays to one array
  @param (int []) the array
  @param (int) the first pos of the first array
  @param (int) the last pos of the first array
  @param (int) the last pos of the second array
  @return (int) status code (0 - success, other - fail)
  @note the array will be changed
*/
int merge(int arr[], int first, int mid, int last){
  int i = 0, j = 0;

  // copy two arrays
  int *left, *right;
  left = (int *)malloc(sizeof(int) * (mid - first));
  right = (int *)malloc(sizeof(int) * (last - mid));

  for(int it = first; it < mid; ++it){
    left[it - first] = arr[it];
  }
  for(int it = mid; it < last; ++it){
    right[it - mid] = arr[it];
  }

  int curr = first;
  while(i < mid - first || j < last - mid){
    // if the j reached the last of the array right
    // or i did not reach the last of the array left and the int is less
    if(j == last - mid || (i < mid - first && left[i] < right[j])){
      arr[curr++] = left[i++];
    }
    // else for j did not reach the last of the array right
    // and i reached the last of the array left or the int is more
    else{
      arr[curr++] = right[j++];
    }
  }

  // free the temp array
  free(left);
  free(right);

  return 0;
}

/* sort int array from low to high by merge sort
  @param (int []) the array to be sorted
  @oaram (int) the first pos of the array
  @param (int) the last pos of the array
  @return (int) status code (0 - success, other - fail)
  @note the array will be changed
*/
int merge_sort(int arr[], int first, int last){
  // if only 1 int in the array
  if(first + 1 == last){
    return 0;
  }

  int mid = first + (last - first) / 2; // prevent reaching INT_MAX
  merge_sort(arr, first, mid);
  merge_sort(arr, mid, last);
  merge(arr, first, mid, last);

  return 0;
}

int main(){
  int arr[] = {5, 4, 7, 12, 4, 9, 2, 1, 13, 2};
  int length = 10;

  print(arr, length);
  merge_sort(arr, 0, length);
  print(arr, length);

  return 0;
}
