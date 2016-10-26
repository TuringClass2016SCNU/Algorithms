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

#define neo_list_new_1() (NeoList *)( malloc ( sizeof ( NeoList ) ) )

typedef void *npointer;
typedef const void *nconstpointer;

typedef struct __linked_list NeoList;
struct __linked_list {
        npointer data;
        struct __linked_list *prev;
        struct __linked_list *next;
};

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
static NeoList *neo_list_allocate ();
static NeoList *neo_list_insert_sorted_real ( NeoList *list, npointer data,
                                              int ( *NeoCompareFunc ) ( nconstpointer a,
                                                                        nconstpointer b ),
                                              npointer user_data );
static NeoList *neo_list_remove_real ( NeoList *list, npointer data,
                                       int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ),
                                       void ( *NeoDestroyFunc ) ( npointer data ) );

static NeoList *neo_list_remove_all_real ( NeoList *list, npointer data,
                                           int ( *NeoCompareFunc ) ( nconstpointer a,
                                                                     nconstpointer b ),
                                           void ( *NeoDestroyFunc ) ( npointer data ) );

static NeoList *neo_list_allocate () {
        NeoList *new_element = neo_list_new_1 ();
        new_element->prev = new_element->next = NULL;
        return new_element;
}

NeoList *neo_list_append ( NeoList *list, npointer data ) {
        NeoList *new_element = neo_list_allocate ();
        new_element->data = data;

        if ( !list ) {
                return new_element;
        }

        NeoList *last = neo_list_last ( list );
        last->next = new_element;
        new_element->prev = last;

        return list;
}

NeoList *neo_list_prepend ( NeoList *list, npointer data ) {
        NeoList *new_element = neo_list_allocate ();
        new_element->data = data;
        if ( !list )
                return new_element;
        new_element->next = list;
        list->prev = new_element;
        return new_element;
}

NeoList *neo_list_insert ( NeoList *list, npointer data, int position ) {
        /* consider this situation as meeting for the end */
        if ( position < 0 )
                return neo_list_append ( list, data );

        NeoList *iterator = list;
        while ( position-- && iterator )
                iterator = iterator->next;

        /* meets for the end */
        if ( !iterator )
                return neo_list_append ( list, data );

        NeoList *new_element = neo_list_allocate ();
        new_element->data = data;

        /* deal the link relationship */
        new_element->next = iterator;
        new_element->prev = iterator->prev;
        if ( iterator->prev )
                iterator->prev->next = new_element;
        iterator->prev = new_element;

        /* Judge if the new element is the new head of the list */
        if ( !new_element->prev )
                return new_element;
        else
                return list;
}

NeoList *neo_list_insert_before ( NeoList *list, NeoList *before, npointer data ) {
        if ( !list || !before )
                return neo_list_append ( list, data );

        NeoList *iterator = list;
        while ( iterator != before )
                iterator = iterator->next;

        /* deal the link relationship */
        NeoList *new_element = neo_list_allocate ();
        new_element->data = data;

        new_element->next = before;
        new_element->prev = before->prev;
        if ( before->prev )
                before->prev->next = new_element;
        before->prev = new_element;

        if ( !new_element->prev )
                return new_element;
        else
                return list;
}

static NeoList *neo_list_insert_sorted_real ( NeoList *list, npointer data,
                                              int ( *NeoCompareFunc ) ( nconstpointer a,
                                                                        nconstpointer b ),
                                              npointer user_data ) {
        if ( !list )
                return neo_list_append ( list, data );

        if ( !NeoCompareFunc )
                return list;

        npointer cmp_data = ( !user_data ) ? data : user_data;

        NeoList *iterator = list;
        while ( iterator && NeoCompareFunc ( iterator->data, cmp_data ) < 0 )
                iterator = iterator->next;
        free ( user_data );
        return neo_list_insert_before ( list, iterator, data );
}

NeoList *neo_list_insert_sorted ( NeoList *list, npointer data,
                                  int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) ) {
        return neo_list_insert_sorted_real ( list, data, NeoCompareFunc, NULL );
}

NeoList *neo_list_insert_sorted_with_data ( NeoList *list, npointer data,
                                            int ( *NeoCompareFunc ) ( nconstpointer a,
                                                                      nconstpointer b ),
                                            npointer user_data ) {
        return neo_list_insert_sorted_real ( list, data, NeoCompareFunc, user_data );
}

static NeoList *neo_list_remove_real ( NeoList *list, npointer data,
                                       int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ),
                                       void ( *NeoDestroyFunc ) ( npointer data ) ) {
        if ( !list )
                return NULL;

        if ( !NeoCompareFunc )
                return list;

        NeoList *iterator = list;
        while ( iterator ) {
                if ( !NeoCompareFunc ( iterator->data, data ) )
                        break;
                iterator = iterator->next;
        }
        if ( iterator->prev )
                iterator->prev->next = iterator->next;
        if ( iterator->next )
                iterator->next->prev = iterator->prev;

        NeoList *new_list = ( iterator == list ) ? ( iterator->next ) : ( list );

        if ( NeoDestroyFunc )
                NeoDestroyFunc ( iterator->data );
        free ( iterator );
        free ( data );

        return new_list;
}

NeoList *neo_list_remove ( NeoList *list, npointer data,
                           int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) ) {
        return neo_list_remove_real ( list, data, NeoCompareFunc, NULL );
}

NeoList *neo_list_remove_full ( NeoList *list, npointer data,
                                int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ),
                                void ( *NeoDestroyFunc ) ( npointer data ) ) {
        return neo_list_remove_real ( list, data, NeoCompareFunc, NeoDestroyFunc );
}

NeoList *neo_list_remove_link ( NeoList *list, NeoList *llink ) {
        if ( !list )
                return NULL;
        if ( !llink )
                return list;

        NeoList *iterator = list;
        while ( iterator && iterator != llink )
                iterator = iterator->next;

        if ( !iterator )
                return list;
        NeoList *new_list = ( iterator == list ) ? ( iterator->next ) : ( list );
        if ( iterator->prev )
                iterator->prev->next = iterator->next;
        if ( iterator->next )
                iterator->next->prev = iterator->prev;
        iterator->prev = iterator->next = NULL;

        return new_list;
}

NeoList *neo_list_delete_link ( NeoList *list, NeoList *link_ ) {
        return neo_list_remove_link ( list, link_ );
}

static NeoList *neo_list_remove_all_real ( NeoList *list, npointer data,
                                           int ( *NeoCompareFunc ) ( nconstpointer a,
                                                                     nconstpointer b ),
                                           void ( *NeoDestroyFunc ) ( npointer data ) ) {
        if ( !list )
                return NULL;
        if ( !NeoCompareFunc )
                return list;

        NeoList *new_list = list;

        NeoList *iterator = list;
        while ( iterator ) {
                if ( !NeoCompareFunc ( iterator->data, data ) ) {
                        if ( iterator->prev )
                                iterator->prev->next = iterator->next;
                        if ( iterator->next )
                                iterator->next->prev = iterator->prev;
                        NeoList *next = iterator->next;

                        if ( iterator == new_list )
                                new_list = next;

                        if ( NeoDestroyFunc )
                                NeoDestroyFunc ( iterator->data );
                        free ( iterator );
                        iterator = next;
                } else {
                        iterator = iterator->next;
                }
        }

        free ( data );
        return new_list;
}

NeoList *neo_list_remove_all ( NeoList *list, npointer data,
                               int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ) ) {
        return neo_list_remove_all_real ( list, data, NeoCompareFunc, NULL );
}

NeoList *neo_list_remove_all_full ( NeoList *list, npointer data,
                                    int ( *NeoCompareFunc ) ( nconstpointer a, nconstpointer b ),
                                    void ( *NeoDestroyFunc ) ( npointer data ) ) {
        return neo_list_remove_all_real ( list, data, NeoCompareFunc, NeoDestroyFunc );
}

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

NeoList *neo_list_first ( NeoList *element ) {
        if ( !element )
                return NULL;
        NeoList *iterator = element;
        while ( iterator->prev )
                iterator = iterator->next;
        return iterator;
}

NeoList *neo_list_last ( NeoList *element ) {
        if ( !element )
                return NULL;
        NeoList *iterator = element;

        while ( iterator->next )
                iterator = iterator->next;

        return iterator;
}

void neo_list_free_1_real ( NeoList *element, void ( *NeoDestroyFunc ) ( npointer data ) ) {
        if ( !element ) {
                NeoDestroyFunc ( element->data );
                free ( element );
        }
}

void neo_list_free ( NeoList *list ) {
        if ( !list )
                return;

        NeoList *iterator = list, *next_element = NULL;
        while ( iterator ) {
                next_element = iterator->next;
                free ( iterator );
                iterator = next_element;
        }
}

void neo_list_free_full ( NeoList *list, void ( *NeoDestroyFunc ) ( npointer data ) ) {
        if ( !list )
                return;

        NeoList *iterator = list, *next_element = NULL;
        while ( iterator ) {
                next_element = iterator->next;
                NeoDestroyFunc ( iterator->data );
                free ( iterator );
                iterator = next_element;
        }
}
