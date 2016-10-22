#include <stdio.h>

/**
 * 迭代乘法
 * @param  a 第一个操作数
 * @param  b 第二个操作数
 * @return   a*b的结果
 */
int multiply(int a,int b){
    int result = 0;
    //b删完后循环结束
    while (b != 0) {
        //判断最后一比特是否为1
        if(b % 2)
            result = result + a;
        //删去一比特
        b = b >> 1;
        //b每删掉一比特a应该乘一个2
        a = a << 1;
    }
    return result;
}

/**
 * 迭代乘方
 * @param  a 底数
 * @param  b 指数
 * @return   a^b的结果
 */
int power(int a, int b){
    int result = 1;
    while (b != 0) {
        //判断奇偶
        if(b % 2){
            //奇数的情况
            result = result * a;
            b--;
        }else{
            //偶数的情况
            result = result * result;
            b = b / 2;
        }
    }
    return result;
}


int main(){
    printf("25*25= %d\n", multiply(25, 25));
    printf("5^3= %d\n", power(5,3));
    return 0;
}
