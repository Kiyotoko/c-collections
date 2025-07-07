#include <stdio.h>
#include <stdlib.h>
#include "src/assertations.h"
#include "src/array_list.h"
#include "src/linked_list.h"
#include "src/binary_tree.h"

#define println printf("\n")

void print_integer(void* value) {
    printf("%i, ", *(int*)value);
}

bool remove_if_in_range(void* pointer) {
    int deref = *(int*) pointer;
    return 1 < deref && deref < 7;
}

void array_list_test() {
    array_list* array = array_list_create(sizeof(int));
    for (int i = 0; i < 64; i++) {
        array_list_add(array, &i);
    }
    for (int i = 0; i < array->len; i++) {
        printf("%i, ", *(int*)array_list_get(array, i));
    }
    println;
    array_list_destroy(array);
}

int compere(void* left, void* right) {
    return *(int*)right - *(int*)left;
}

void binary_tree_test() {
    BinaryTree* tree = binary_tree_create(sizeof(int), compere);
    int test_value = 3;
    for (int i = 0; i<32; i++) {
        binary_tree_add(tree, &i);
    }
    binary_tree_traverse(tree, &print_integer);
    println;
    assert_equals(6, tree->root->height);
    binary_tree_destroy(tree);
}

void linked_list_test() {
    LinkedList* created = linked_list_create(sizeof(int));
    LinkedNode** iter = linked_list_iter(created);
    while (linked_list_iter_has_next(iter)) {
        fail;
    }
    for (int i = 0; i < 16; i++) {
        linked_list_add(created, &i);
    }
    linked_list_foreach(created, &print_integer);
    println;
    linked_list_remove(created, 8);
    linked_list_remove_if(created, &remove_if_in_range);
    linked_list_foreach(created, &print_integer);
    println;
    iter = linked_list_iter(created);
    while (linked_list_iter_has_next(iter)) {
        void* next = linked_list_iter_next(iter);
        print_integer(next);
    }
    println;
    linked_list_add(created, NULL);
    linked_list_destroy(created);
}

int main() {
    array_list_test();
    binary_tree_test();
    linked_list_test();

    return 0;
}
