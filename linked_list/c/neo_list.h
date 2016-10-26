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


#ifndef __LIBNEOLIST_H_
#define __LIBNEOLIST_H_
#include <malloc.h>

typedef void *npointer;
typedef const void *nconstpointer;
typedef struct __linked_list NeoList;
struct __linked_list {
        npointer data;
        struct __linked_list *prev;
        struct __linked_list *next;
};

void *__tmp_hook = NULL;

#define neo_data_to_npointer( data, type ) \
        ( __tmp_hook = malloc ( sizeof ( type ) ), *(type *)__tmp_hook = ( data ), __tmp_hook )

#define neo_npointer_to_data( data, type ) *(type *)data

NeoList *neo_list_append ( NeoList *list, npointer data );
NeoList *neo_list_prepend ( NeoList *list, npointer data );
NeoList *neo_list_insert ( NeoList *list, npointer data, int position );
NeoList *neo_list_insert_before ( NeoList *list, NeoList *before, npointer data );
NeoList *neo_list_insert_sorted ( NeoList *list, npointer data,
                                  int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) );
NeoList *neo_list_insert_sorted_with_data ( NeoList *list, npointer data,
                                            int ( *NeoCompareFunc ) ( nconstpointer a,
                                                                      nconstpointer b ),
                                            npointer user_data );
NeoList *neo_list_remove ( NeoList *list, npointer data,
                           int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) );
NeoList *neo_list_remove_full ( NeoList *list, npointer data,
                                int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ),
                                void ( *NeoDestroyFunc ) ( npointer data ) );
NeoList *neo_list_remove_link ( NeoList *list, NeoList *llink );
NeoList *neo_list_remove_all ( NeoList *list, npointer data,
                               int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) );
NeoList *neo_list_remove_all_full ( NeoList *list, npointer data,
                                    int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ),
                                    void ( *NeoDestroyFunc ) ( npointer data ) );
NeoList *neo_list_sort ( NeoList *list,
                         int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) );
NeoList *neo_list_first ( NeoList *element );
NeoList *neo_list_last ( NeoList *element );
void neo_list_free ( NeoList *list );
void neo_list_free_full ( NeoList *list, void ( *NeoDestroyFunc ) ( npointer data ) );

#endif /* libneolist.h */
