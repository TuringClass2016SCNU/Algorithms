#include <stdio.h>

//迭代的乘法
int multiply(int a,int b){
  int result = 0;
  //b删完后循环结束
  while (b != 0) {
    //判断最后一比特是否为1
    if(b % 2)
      result = result + a;
    //删去一比特
    b = b / 2;
    //b每删掉一比特a应该乘一个2
    a = a * 2;
  }
  return result;
}

//求a的b次幂,迭代
int power(int a,int b){
  int result = 1;
  while (b != 0) {
    result = multiply(result, a);
    b--;
  }
  return result;
}


int main(){
  printf("25*25= %d\n", multiply(25, 25));
  printf("5^3= %d\n", power(5,3));
  return 0;
}
