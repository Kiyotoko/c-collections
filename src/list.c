#include <stdlib.h>
#include <string.h>
#include "list.h"

BilinkedNode* bilinked_node_create(void* element, size_t element_size) {
    // Allocate a new node that we later add to the list first.
    BilinkedNode* created = calloc(1, sizeof(BilinkedNode));
    if (!created) {
        return false;
    }
    created->value = malloc(element_size);
    created->next = NULL;
    created->prev = NULL;
    if (element != NULL) {
        memcpy(created->value, element, element_size);
    }

    return created;
}

void bilinked_node_destroy(BilinkedNode* node) {
    if (node->value) {
        free(node->value);
    }
    free(node);
}

void bilinked_node_destroy_recursive(BilinkedNode* node) {
    if (node->next) {
        bilinked_node_destroy_recursive(node->next);
    }
    bilinked_node_destroy(node);
}

List* list_create(size_t element_size) {
    List* created = (List*) calloc(1, sizeof(List));
    if (!created) return NULL;
    created->element_size = element_size;

    return created;
}

void list_destroy(List* list) {
    if (list->head != NULL) {
        bilinked_node_destroy_recursive(list->head);
    }
    free(list);
}

void list_push(List* list, void* value) {
    BilinkedNode* created = bilinked_node_create(value, list->element_size);
    if (list->head) {
        created->next = list->head;
        list->head->prev = created;
    } else {
        list->tail = created;
    }
    list->head = created;
    // Increase the size of the list;
    list->len++;
}

void list_add(List* list, void* value) {
    BilinkedNode* created = bilinked_node_create(value, list->element_size);
    if (list->head) {
        list->tail->next = created;
        created->prev = list->tail;
    } else {
        list->head = created;
    }
    list->tail = created;
    // Increase the size of the list;
    list->len++;
}

int list_first(List* list, void* buffer) {
    if (list->head) {
        memcpy(buffer, list->head->value, list->element_size);
        return 0;
    }
    return 1;
}

int list_last(List* list, void* buffer) {
    if (list->tail) {
        memcpy(buffer, list->tail->value, list->element_size);
        return 0;
    }
    return 1;
}

int list_get(List* list, size_t index, void* buffer) {
    // Check for index out of bounds.
    if (0 <= index && index < list->len) {
        BilinkedNode* p = list->head;
        for (size_t i = 0; i < index; i++) {
            p = p->next;
        }
        memcpy(buffer, p->value, list->element_size);
        return 0;
    }
    return 1;
}

void list_foreach(List* list, Consumer consumer) {
    BilinkedNode* p = list->head;
    if (p) {
        while (p->next) {
            consumer(p->value);
            p = p->next;
        }
        consumer(p->value);
    }
}

List* list_filter(List* list, Test test) {
    BilinkedNode* node = list->head;
    List* created = list_create(list->element_size);
    while (node) {
        if (test(node)) list_add(created, node->value);
        node = node->next;
    }
    return created;
}

int list_peek(List* list, void* buffer) {
    return list_first(list, buffer);
}

int list_pop(List* list, void* buffer) {
    if (list->head != NULL) {
        BilinkedNode* head = list->head;
        if (buffer) memcpy(buffer, head->value, list->element_size);
        head->next->prev = NULL;
        list->head = head->next;
        list->len--;
        bilinked_node_destroy(head);
        return 0;
    }
    return 1;
}

bool list_remove(List* list, size_t index) {
    if (index >= list->len)
        // We return here because the index is out of bounds.
        return false;
    else if (index == 0) {
        // Remove the head of the list.
        list_pop(list, NULL);
    } else if (list->head != NULL) {
        // Loop througt the list starting at the head to find the node at
        // the given index.
        BilinkedNode* p = list->head;
        for (size_t i = 1; i < index; i++) {
            p = p->next;
        }

        // Cache the deleted note so that we can later free it.
        BilinkedNode* deleted = p->next;

        if (index == list->len -1) {
            // Remove the tail of the list.
            list->tail = p;
            p->next = NULL;
        } else {
            p->next = deleted->next;
            p->next->prev = p;
        }
        list->len--;
        bilinked_node_destroy(deleted);
    }
    return true;
}

void list_remove_if(List* list, Test test) {
    BilinkedNode* previous = NULL;
    BilinkedNode* node = list->head;
    while (node) {
        BilinkedNode* next = node->next;
        if (test(node->value)) {
            // Check if removed element was head or tail.
            if (node == list->head) {
                list->head = node->next;
            }
            if (node == list->tail) {
                list->tail = previous;
            }
            // Change linking.
            if (previous) {
                previous->next = node->next;
            }
            // Decrease len of the list.
            list->len--;
            // Free allocated memory.
            bilinked_node_destroy(node);
        } else {
            previous = node;
        }
        node = next;
    }
}

BilinkedNode** list_iter(List* list) {
    return &(list->head);
}

bool list_iter_has_next(BilinkedNode** iter) {
    return *iter != NULL;
}

void* list_iter_next(BilinkedNode** iter) {
    void* value = (*iter)->value;
    *iter = (*iter)->next;
    return value;
}

void* list_iter_peek(BilinkedNode** iter) {
    return (*iter)->value;
}
