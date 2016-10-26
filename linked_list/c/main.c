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
