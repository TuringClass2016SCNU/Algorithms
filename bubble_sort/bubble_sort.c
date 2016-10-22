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
