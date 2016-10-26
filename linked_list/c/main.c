#include "neo_list.h"

int compare ( nconstpointer a, nconstpointer b ) { return *(int *)a - *(int *)b; }

int main ( void ) {
        int a[] = {3, 3, 1, 7, 4, 6, 5, 2, 8, 10, 9, 10};
        NeoList *list = NULL;

        for ( int cnt = 0; cnt < sizeof ( a ) / sizeof ( int ); ++cnt )
                list = neo_list_append ( list, neo_data_to_npointer ( a[ cnt ], int ) );

        list = neo_list_sort ( list, compare );

        for ( NeoList *iterator = list; iterator != NULL; iterator = iterator->next ) 
                printf ( "%d\n", neo_npointer_to_data ( iterator->data,int ) );

        neo_list_free_full ( list, free );
        return 0;
}
