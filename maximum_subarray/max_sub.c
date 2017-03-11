/*
 * Copyright (c) 2017 Deng, Liming <myosmanthustree@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>

#define MAX( a, b, c ) \
        ( ( a ) >= ( b ) ) ? ( ( a ) >= ( c ) ? ( a ) : ( c ) ) : ( ( b ) >= ( c ) ? ( b ) : ( c ) )

typedef struct _IndexTuple {
        int *low;
        int *high;
} IndexTuple;

static int find_cross_max_sub ( int *begin, int *mid, int *end, IndexTuple *ret ) {

        int l_max_sum = 0;
        for ( int *l = mid, sum = 0; l > begin - 1; --l ) {

                sum += *l;

                if ( l == mid || sum > l_max_sum ) {
                        l_max_sum = sum;
                        ret->low = l;
                }
        }

        int r_max_sum = 0;
        for ( int *r = mid + 1, sum = 0; r < end; ++r ) {

                sum += *r;

                if ( r == ( mid + 1 ) || sum > r_max_sum ) {
                        r_max_sum = sum;
                        ret->high = r;
                }
        }

        return l_max_sum + r_max_sum;
}

int find_max_sub ( int *base, size_t size, IndexTuple *ret ) {
        if ( size == 1 ) {
                ret->low = ret->high = base;
                return *base;
        }

        int *mid = base + ( size >> 1 ) - 1, *end = base + size;

        IndexTuple tuple_set[ 3 ];

        int mid_max_sum = find_cross_max_sub ( base, mid, end, tuple_set );
        int l_max_sum = find_max_sub ( base, size >> 1, tuple_set + 1 );
        int r_max_sum = find_max_sub ( mid + 1, size - ( size >> 1 ), tuple_set + 2 );

        int max_sum = MAX ( mid_max_sum, l_max_sum, r_max_sum );

        if ( mid_max_sum == max_sum )
                *ret = tuple_set[ 0 ];
        else if ( l_max_sum == max_sum )
                *ret = tuple_set[ 1 ];
        else if ( r_max_sum == max_sum )
                *ret = tuple_set[ 2 ];

        return max_sum;
}

int main ( void ) {
        IndexTuple tuple_a;
        int a[] = {-1, 2, -3, 5, 4, -5, 6};

        printf ( "%d\n", find_max_sub ( a, sizeof ( a ) / sizeof ( a[ 0 ] ), &tuple_a ) );
        printf ( "\n" );

        for ( int *iter = tuple_a.low; iter < tuple_a.high + 1; ++iter )
                printf ( "%d\n", *iter );

        return 0;
}
