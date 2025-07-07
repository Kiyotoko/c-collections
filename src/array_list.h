#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdint.h>

typedef struct {
    void* data;
    size_t len;
    size_t capacity;
    size_t element_size;
} array_list;

array_list* array_list_create(size_t elment_size);

void array_list_destroy(array_list* list);

void array_list_add(array_list* list, void* e);

void* array_list_get(array_list* list, size_t index);

void array_list_grow(array_list* list);

void array_list_shrink(array_list* list);

int array_list_len(array_list* list);


#endif
