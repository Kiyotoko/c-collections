#ifndef BIbilinked_list_H
#define BIbilinked_list_H

#include <stdbool.h>
#include <stddef.h>
#include "functions.h"

/**
 * Two sided directional linked node.
 */
typedef struct bilinked_node {
    void* value;
    struct bilinked_node* prev;
    struct bilinked_node* next;
} linked_node;

/**
 * Implementation of the linked list with one directional
 * linking. Supports null values.
 */
typedef struct {
    linked_node* head;
    linked_node* tail;
    size_t len;
    size_t element_size;
} bilinked_list;

/**
 * Iterator for the linked list.
 */
typedef struct {
    linked_node* node;
} bilinked_list_iterator;

/**
 * Creates and returns a new linked list without a head.
 */
bilinked_list* bilinked_list_create(size_t element_size);

/**
 * Destroys the linked list by freeing the memory of
 * the head if present and then itself.
 */
void bilinked_list_destroy(bilinked_list* list);

/**
 * Adds the value to the start of the linked list. This
 * will increase the len of the list and creates a new
 * node with the given value which then adds the node to
 * the start of the list.
 * 
 * Time complexity: O(1)
 */
void bilinked_list_push(bilinked_list* list, void* value);

/**
 * Adds the value to the end of the linked list. This
 * will increase the len of the list and creates a new
 * node with the given value which then adds the node to
 * the end of the list.
 * 
 * Time complexity: O(1)
 */
void bilinked_list_add(bilinked_list* list, void* value);

/**
 * Returns the first value of the list or null if this list
 * is empty.This is equal to calling the 'bilinked_list_peek'
 * function.
 * 
 * Time complexity: O(1)
 */
void* bilinked_list_first(bilinked_list* list);

/**
 * Returns the last value of the list or null if this
 * list is empty.
 * 
 * Time complexity: O(1)
 */
void* bilinked_list_last(bilinked_list* list);

/**
 * Executes the given consumer for all elements in the list.
 * 
 * Time complexity: O(n)
 */
void bilinked_list_foreach(bilinked_list* list, consumer consumer);

/**
 * Creates a new linked list from the given list and adds all
 * elements that statisfy the filter. This method will not
 * change the supplied list.
 * 
 * Time complexity: O(n)
 */
bilinked_list* bilinked_list_filter(bilinked_list* list, test test);

/**
 * Returns the value at the given index of the list. If the
 * index is out of bounds, then null will be returned. The
 * value may also be null if you added null values to the list.
 * 
 * Time complexity: O(n)
 */
void* bilinked_list_get(bilinked_list* list, size_t index);

/**
 * Returns the first value of the list or null if this list
 * is empty.This is equal to calling the 'bilinked_list_first'
 * function.
 * 
 * Time complexity: O(1)
 */
void* bilinked_list_peek(bilinked_list* list);

/**
 * Returns and removes the first element of the list. If
 * the list is empty, it will return null instead.
 * 
 * Time complexity: O(1)
 */
void* bilinked_list_pop(bilinked_list* list);

/**
 * Removes the element at the given index. Returns true on
 * success or false if it was index out of bounds.
 * 
 * Time complexity: O(n)
 */
bool bilinked_list_remove(bilinked_list* list, size_t index);

/**
 * Removes all elements of the list that statisfy the test.
 * 
 * Time complexity: O(n)
 */
void bilinked_list_remove_if(bilinked_list* list, test test);

/**
 * Creates a new iterator from the given list. You should
 * free the memory by calling the 'bilinked_list_iter_destroy'
 * function.
 */
bilinked_list_iterator* bilinked_list_iter(bilinked_list* list);

/**
 * Checks if there are any values left.
 */
bool bilinked_list_iter_has_next(bilinked_list_iterator* iter);

/**
 * Returns the current value and continue the iterator to
 * the next node. It should be always checked first if
 * there are any values left by checking the
 * 'bilinked_list_iter_has_next' function. If this is not
 * done, then this may result in null pointer exceptions.
 */
void* bilinked_list_iter_next(bilinked_list_iterator* iter);

/**
 * Returns only the current value of the iterator. This
 * will not continue the iterator to the next node. If you
 * want to go to the next node, you should call
 * 'bilinked_list_iter_next'.
 */
void* bilinked_list_iter_peek(bilinked_list_iterator* iter);

/**
 * Frees all allocated memory of the supplied iterator.
 * You should not call any methods of the iterator after
 * destroying it.
 */
void bilinked_list_iter_destroy(bilinked_list_iterator* iter);

#endif
