#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "array_list.h"

#define DEFAULT_CAPACITY 16
#define MIN_CAPACITY 4

array_list* array_list_create(size_t element_size) {
    array_list* created = calloc(1, sizeof(array_list));
    if (!created) return NULL;

    // Allocate a new array with the default capacity.
    int* array = calloc(DEFAULT_CAPACITY, element_size);
    if (!array) {
        free(created);
        return NULL;
    }
    created->data = array;
    created->capacity = DEFAULT_CAPACITY;
    created->element_size = element_size;
    
    return created;
}

void array_list_destroy(array_list* list) {
    free(list->data);
    free(list);
}

void array_list_add(array_list* list, void* e) {
    // Check if we have any capacity left. If not, grow the array and then continue.
    if (list->len >= list->capacity) {
        array_list_grow(list);
    }
    memcpy(list->data + list->len * list->element_size, e, list->element_size);
    list->len++;
}

void* array_list_get(array_list* list, size_t index) {
    return list->data+index*list->element_size;
}

void array_list_grow(array_list* list) {
    // Calculate new capacity. The new capacity is the current capacity doubled.
    int new_capacity = list->capacity * 2;
    if (new_capacity < MIN_CAPACITY) new_capacity = MIN_CAPACITY;
    
    // Allocate a new array with the new capacity, then copy the memory from the
    // old array to the new array and finally free the memory of the old array.
    int* array = calloc(new_capacity, list->element_size);
    // Failed to allocate memore, return.
    if (!array) return;
    memcpy(array, list->data, list->element_size * list->len);
    free(list->data);

    list->data = array;
    list->capacity = new_capacity;
}

void array_list_shrink(array_list* list) {

}

int array_list_len(array_list* list) {
    return list->len;
}
