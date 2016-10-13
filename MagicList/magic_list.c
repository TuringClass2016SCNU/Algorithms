#include <malloc.h>
#include <stdio.h>

void print_m_list_1 ( size_t n ); /* Fermat Theory */
void print_m_list_2 ( size_t n );  /* Print the second list*/
size_t ipow ( size_t a, size_t b ); /* ... */
void print_m_list_3 ( size_t n ); /* Euler Theorem */
size_t gcd ( size_t a, size_t b );

int main ( void ) {
	/* Here we do not invoke any function,
	 * you can invoke any function here as you like*/
        return 0;
}
void print_m_list_1 ( size_t n ) {
        for ( size_t i = 1; i < n; ++i ) {
                for ( size_t j = 1; j < n; ++j )
                        printf ( "%lu ", ( i * j ) % n );
                printf ( "\n" );
        }
}
void print_m_list_2 ( size_t n ) {
        for ( size_t i = 1; i < n - 1; ++i ) {
                printf ( "%lu:	", i );
                for ( size_t j = 1; j < n; ++j )
                        printf ( "%lu ", ipow ( i, j ) % n );
                printf ( "\n" );
        }
}
size_t ipow ( size_t a, size_t b ) {
        size_t t = 1;
        while ( b-- )
                t *= a;
        return t;
}

size_t gcd ( size_t a, size_t b ) {
        if ( a == 0 || b == 0 )
                return 0;
	/* swap the number if a< b */
        if ( a < b )
                a ^= b, b ^= a, a ^= b;
        while ( a % b ) {
                size_t r = a % b;
                a = b;
                b = r;
        }
        return b;
}
void print_m_list_3 ( size_t n ) {
	/* Dynamically construct a 2d arrary */
        size_t **phi_list = (size_t **)malloc ( sizeof ( size_t * ) * n );
        for ( size_t cnt = 0, **rphi_list = phi_list; cnt < n; ++cnt )
                *rphi_list++ = (size_t *)malloc ( sizeof ( size_t ) * n );

	/* calculate the width of the list */
        size_t s = 0;

	/* generate the first row */
        for ( size_t i = 1; i < n; ++i )
                if ( gcd ( n, i ) == 1 )
                        phi_list[ 0 ][ s++ ] = i;

	/* generate the first column */
        for ( size_t j = 1; j < s; ++j )
                phi_list[ j ][ 0 ] = phi_list[ 0 ][ j ];

	/* generate the rest of the list */
        for ( size_t i = 1; i < s; ++i )
                for ( size_t j = 1; j < s; ++j )
                        phi_list[ i ][ j ] = ( i * j ) % n;

	/* print it */
        for ( size_t i = 0; i < s; ++i ) {
                for ( size_t j = 0; j < s; ++j )
                        printf ( "%lu ", phi_list[ i ][ j ] );
                printf ( "\n" );
        }
	
	/* free the list */
        for ( size_t i = 0; i < s; ++i )
                free ( phi_list[ i ] );
        free ( phi_list );
}
