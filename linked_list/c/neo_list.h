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
