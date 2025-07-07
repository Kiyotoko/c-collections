#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdint.h>
#include <stdbool.h>
#include "functions.h"

typedef struct BinaryNode {
    void* value;
    struct BinaryNode* left;
    struct BinaryNode* right;
    int height;
} BinaryNode;

typedef struct {
    BinaryNode* root;
    int element_size;
    Comperator comperator;
} BinaryTree;

BinaryTree* binary_tree_create(int element_size, Comperator comperator);

void binary_tree_destroy(BinaryTree* tree);

void binary_tree_add(BinaryTree* tree, void* e);

bool binary_tree_contains(BinaryTree* tree, void* e);

void binary_tree_traverse(BinaryTree* tree, Consumer consumer);

#endif