#include <stdio.h>

/**
 * 递归乘法
 * @param  a 操作数a
 * @param  b 操作数b
 * @return   a*b的结果
 */
int multiply(int a, int b){
    if (b == 0)
        return 0;
    //终止条件
    if (b == 1)
        return a;
    //判断奇偶，每一位的结果只能是0或者a
    if (b % 2 == 0)
        return 2 * multiply(a, b/2);
    else
        return 2 * multiply(a, b/2) + a;
}

/**
 * 乘方的递归实现
 * @param  a 底数
 * @param  b 指数
 * @return   a^b的结果
 */
int power(int a, int b){
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    //判断奇偶
    if (b % 2 == 0)
        //构造a^2^(b/2)，实现b随着递归的进行越来越小的目的
        return power(multiply(a, a), b/2);
    else
        //当b是奇数时候，转化成偶数次幂的运算
        return multiply(a, power(a, b - 1));
}

int main(){
    printf("25*25= %d\n", multiply(25, 25));
    printf("5^3= %d\n", power(5,3));
    return 0;
}
