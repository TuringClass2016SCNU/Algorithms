#include <stdio.h>

/**
 * 二分查找算法，递归
 * @param  arr  数组的引用
 * @param  low  查找数组最低的位置
 * @param  high 查找数组最高的位置
 * @param  n    要查找的元素的值
 * @return      找到的元素在数组中的下标，没找到就返回 -1
 */
int binary_search_digui(int arr[], int low, int high, int n){
    //不用(high + low) / 2 是为了避免两者相加的数字过大
    int mid = low + (high - low) / 2;
    //不断缩小查找范围直到low与high相等
    if(low <= high){
        //目标恰好在中间位置
        if(n == arr[mid]){
            return mid;
        }
        //将中间位置设置为下一次递归的最高位置，由于目标不在中间位置所以要排除它
        else if(n < arr[mid]){
            return binary_search_digui(arr, low, mid - 1, n);
        }
        //n > arr[mid]，将中间位置设置为下一次递归的最低位置，由于目标不在中间位置所以要排除它
        else{
            return binary_search_digui(arr, mid + 1, high, n);
        }
    }else{
        //找不到的情况
        return -1;
    }
}

/**
 * 二分查找算法，递归
 * @param  arr  数组的引用
 * @param  high 数组的最高位置的下标
 * @param  n    要查找的元素
 * @return      查找到的元素的下标，没找到的话则返回 -1
 */
int binary_search_diedai(int arr[], int high, int n){
    int low = 0;
    int mid;
    //不断缩小查找范围直到low与high相等
    while(low <= high){
        //不用(high + low) / 2 是为了避免两者相加的数字过大
        mid =  low + (high - low) / 2;
        //目标恰好在中间位置
        if(n == arr[mid]){
            return mid;
        }
        //将中间位置设置为下一次查找的最高位置，由于目标不在中间位置所以要排除它
        else if(n < arr[mid]){
            high = mid - 1;
        }
        //n > arr[mid]，将中间位置设置为下一次递归的最低位置，由于目标不在中间位置所以要排除它
        else{
            low = mid + 1;
        }
    }
    //找不到的情况
    return -1;
}

int main(){
    int len = 100;
    int mubiao = 50;
    int arr[len];
    int key;
    //生成数组
    for(int i=0; i<len; i++){
        arr[i] = 2 * i;
    }
    //递归
    printf("Digui\n");
    key = binary_search_digui(arr, 0, len - 1, mubiao);
    if(key != -1)
        printf("Value %d Found!!, key is %d\n", mubiao, key);
    else
        printf("Value %d not found...\n\n", mubiao);
    //迭代
    printf("Diedai\n");
    key = binary_search_diedai(arr, len - 1, mubiao);
    if(key != -1)
        printf("Value %d Found!!, key is %d\n", mubiao, key);
    else
        printf("Value %d not found...\n", mubiao);
    return 0;
}
