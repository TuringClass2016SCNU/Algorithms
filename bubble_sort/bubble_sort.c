/*
 * Copyright (c) 2016 Deng, Liming <myosmanthustree@gmail.com>
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


#include <malloc.h>
#include <stdio.h>
#include <string.h>

void bubble_sort ( void *base, size_t nmemb, size_t msize,
                   int ( *compare ) ( const void *a, const void *b ) );
void voidp_swap ( void *block_a, void *block_b, size_t buf_size ) {
        void *buf = malloc ( buf_size );
        memcpy ( buf, block_a, buf_size );
        memcpy ( block_a, block_b, buf_size );
        memcpy ( block_b, buf, buf_size );
}

int compare ( const void *a, const void *b ) { return *(int *)a - *(int *)b; }

int main ( void ) {
        int t[ 10 ] = {2, 1, 9, 6, 3, 8, 7, 5, 4, 0};
        bubble_sort ( t, sizeof ( t ) / sizeof ( t[ 0 ] ), sizeof ( int ), compare );
        for ( size_t cnt = 0; cnt < sizeof ( t ) / sizeof ( t[ 0 ] ); ++cnt )
                printf ( "%d ", t[ cnt ] );
        printf ( "\n" );
        return 0;
}

void bubble_sort ( void *base, size_t nmemb, size_t msize,
                   int ( *compare ) ( const void *a, const void *b ) ) {
        void *end = base + nmemb * msize;
        for ( size_t i = 0; i < nmemb - 1; ++i, end = (char *)end - msize ) {
                void *prev = base;
                for ( void *j = base + msize; j < end;
                      j = (char *)j + msize, prev = (char *)prev + msize ) {
                        if ( compare ( prev, j ) > 0 )
                                voidp_swap ( prev, j, msize );
                }
        }
}
