#include <stdio.h>

//迭代的乘法
long multiply ( long a, size_t b ) {

        long i = 0, j = a;
        // b删完后循环结束
        while ( b != 0 ) {
                //判断最后一比特是否为1
                if ( b & 1 )
                        i += j, --b;
                else
                        j += j, b >>= 1;
        }
        return i;
}

//求a的b次幂,迭代
long power ( long a, size_t b ) {
        long i = 1, j = a;
        while ( b != 0 ) {
                //判断奇偶
                if ( b & 1 )
                        i *= j, --b;
                else
                        j *= j, b >>= 1;
        }
        return i;
}

int main () {
        printf ( "25*25= %d\n", multiply ( 25, 25 ) );
        printf ( "5^3= %d\n", power ( 5, 3 ) );
        return 0;
}
