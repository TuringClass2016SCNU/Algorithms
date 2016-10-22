#include <malloc.h>
#include <stdio.h>
#include <string.h>

void *_tmp_hook = NULL;
#define data_to_pointer( data, type ) \
        ( _tmp_hook = malloc ( sizeof ( type ) ), *(type *)_tmp_hook = data, _tmp_hook )

#define mem_clean()       \
        if ( !_tmp_hook ) \
        free ( _tmp_hook )

/* the declaration of binary_search function */
int *binary_search_recursion ( const int elm, int *array, const size_t asize );
int *binary_search_iteration ( const int elm, int *array, const size_t asize );
void *binary_search ( const void *data, void *array, const size_t msize, const size_t asize,
                      int ( *compare ) ( const void *a, const void *b ) );

int compare ( const void *a, const void *b ) { return *(int *)a - *(int *)b; }

int main ( void ) {
        int a[ 10 ];

        /* Initialize the array */
        for ( size_t cnt = 0; cnt < 10; ++cnt )
                a[ cnt ] = cnt;
        int *find = binary_search ( data_to_pointer ( 1, int ), a, sizeof ( int ),
                                    sizeof ( a ) / sizeof ( a[ 0 ] ), compare );
        mem_clean ();
        if ( find != NULL )
                printf (
                    "addr:	%p\n"
                    "value:	%d",
                    find, *find );
        else
                printf ( "element not found\n" );
        return 0;
}

int *binary_search_recursion ( const int elm, int *array, const size_t asize ) {

        /*
         * if the length of the array is 1 and the only element isn't equal to elm
         * return NULL, or return its pointer
         *
         * */
        if ( asize == 1 )
                return ( elm == array[ 0 ] ) ? array : NULL;

        /* get the middle position */
        size_t mid = asize >> 1;

        /* save the mid pointer */
        int *pmid = array + mid;

        if ( elm == *pmid )
                return pmid;
        /*
         * if elm is lower than the middle element,
         * recur to find in the left part of the array
         *
         * */

        if ( elm < *pmid )
                return binary_search_recursion ( elm, array, mid );

        /*
         *
         * find element in the right part of the array.
         *
         * */
        return binary_search_recursion ( elm, pmid + 1, asize - mid - 1 );
}

int *binary_search_iteration ( const int elm, int *array, const size_t asize ) {

        /* same principle as above function */
        size_t len = asize;
        while ( len > 0 ) {
                size_t mid = len >> 1;
                int *pmid = array + mid;
                if ( elm == *pmid )
                        return pmid;
                else {
                        if ( elm < *pmid )
                                len = mid;
                        else {
                                len -= mid + 1;
                                array = pmid + 1;
                        }
                        len = mid;
                }
        }
        return NULL;
}

/* You can use the following function to deal with any type array */
void *binary_search ( const void *data, void *array, const size_t msize, const size_t asize,
                      int ( *compare ) ( const void *a, const void *b ) ) {
        size_t len = asize;
        while ( len > 0 ) {
                size_t mid = len >> 1;
                void *pmid = (char *)array + msize * mid;
                int cmp = compare ( data, pmid );
                if ( cmp == 0 )
                        return pmid;
                else {
                        if ( cmp < 0 )
                                len = mid;
                        else {
                                len -= mid + 1;
                                array = (char *)pmid + msize;
                        }
                }
                len = mid;
        }
        return NULL;
}
