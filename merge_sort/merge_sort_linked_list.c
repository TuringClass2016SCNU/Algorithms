#include <malloc.h>
typedef const void * nconstpointer;
typedef void * npointer;
typedef struct _NeoList {
        npointer data;
        struct _NeoList *prev;
        struct _NeoList *next;
} NeoList;

static NeoList *neo_list_merge ( NeoList *list_src, NeoList *list_dest,
                                 int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) ) {
        NeoList new_list, *new = &new_list;

        NeoList *new_tail = &new_list;
        NeoList *iterator_left = list_src, *iterator_right = list_dest;
        while ( iterator_left && iterator_right ) {
                NeoList *lower =
                    ( NeoCompareFunc ( iterator_left->data, iterator_right->data ) < 0 )
                        ? ( iterator_left )
                        : ( iterator_right );

                new_tail->next = lower;
                lower->prev = new_tail;
                new_tail = lower;

                if ( lower == iterator_left )
                        iterator_left = iterator_left->next;
                else
                        iterator_right = iterator_right->next;
        }

        if ( !iterator_left ) {
                new_tail->next = iterator_right;
                iterator_right->prev = new_tail;
        } else {
                new_tail->next = iterator_left;
                iterator_left->prev = new_tail;
        }
        return new->next;
}

NeoList *neo_list_sort ( NeoList *list,
                         int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) ) {
        if ( !list )
                return NULL;
        if ( !NeoCompareFunc )
                return list;

        /*
         * divide the list into two pieces.
         */

        /* As a matter of facts,
         * when an object moves in a speed=v,
         * another object moves in a speed=2v.
         * if the latter reach the end (s==x)
         * the former will reach the middle (s==x/2).
         * According to the law above,
         * we can create an algorithm described in the following codes:
         */

        if ( !list->next )
                return list;

        /* avoid the waste of the next recursion */
        if ( !( list->next->next ) ) {
                if ( NeoCompareFunc ( list->data, list->next->data ) > 0 ) {
                        NeoList tmp, *t = &tmp;
                        t->data = list->data;
                        list->data = list->next->data;
                        list->next->data = t->data;
                }
                return list;
        }

        NeoList *left_list = list, *right_list = NULL;

        NeoList *right_list_end = list, *left_list_end = list;
        while ( right_list_end->next ) {
                right_list_end = right_list_end->next;
                if ( !right_list_end->next )
                        break;
                right_list_end = right_list_end->next;
                left_list_end = left_list_end->next;
        }

        right_list = left_list_end->next;
        left_list_end->next = NULL;

        return neo_list_merge ( neo_list_sort ( left_list, NeoCompareFunc ),
                                neo_list_sort ( right_list, NeoCompareFunc ), NeoCompareFunc );
}
