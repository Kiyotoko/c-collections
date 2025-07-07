#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

BinaryNode* binary_node_create(void* element, int element_size) {
    BinaryNode* created = calloc(1, sizeof(BinaryNode));

    created->value = malloc(element_size);
    memcpy(created->value, element, element_size);

    created->height = 1;
    created->left = NULL;
    created->right = NULL;
    return created;
}

void binary_node_destroy(BinaryNode* node) {
    if (node->left) {
        binary_node_destroy(node->left);
    }
    if (node->right) {
        binary_node_destroy(node->right);
    }
    free(node->value);
    free(node);
}

void binary_node_update_height(BinaryNode* node) {
    int height_left = node->left ? node->left->height : 0;
    int height_right = node->right ? node->right->height : 0;
    node->height = (height_left > height_right ? height_left : height_right) + 1;
}

void binary_node_rotate_right(BinaryNode* node) {
    // Swap values around
    void* root = node->value;
    node->value = node->left->value;
    node->left->value = root;

    // Move subtrees
    BinaryNode* rotate1 = node->right;
    BinaryNode* rotate2 = node->left->right;
    node->right = node->left;
    node->right->right = rotate1;
    rotate1 = node->left->left;
    node->right->left = rotate2;
    node->left = rotate1;

    binary_node_update_height(node->left);
    binary_node_update_height(node->right);
    binary_node_update_height(node);
}

void binary_node_rotate_left(BinaryNode* node) {
    // Swap values around
    void* root = node->value;
    node->value = node->right->value;
    node->right->value = root;

    // Move subtrees
    BinaryNode* rotate1 = node->left;
    BinaryNode* rotate2 = node->right->left;
    node->left = node->right;
    node->left->left = rotate1;
    rotate1 = node->right->right;
    node->left->right = rotate2;
    node->right = rotate1;

    binary_node_update_height(node->left);
    binary_node_update_height(node->right);
    binary_node_update_height(node);
}

int binary_node_get_balance_factor(BinaryNode* node) {
    int height_left = node->left ? node->left->height : 0;
    int height_right = node->right ? node->right->height : 0;
    return height_left - height_right;
}

void binary_node_add(BinaryTree* tree, BinaryNode* node, void* e) {
    int c = tree->comperator(tree->root->value, e);
    if (c == 0) return;

    // Pointer to the node we want to check.
    BinaryNode** relevant_child = (c  > 0) ? &(node->right) : &(node->left);
    
    if ((*relevant_child) == NULL) {
        *relevant_child = binary_node_create(e, tree->element_size);
    } else {
        binary_node_add(tree, *relevant_child, e);
    }
    binary_node_update_height(node);
    int balance_factor = binary_node_get_balance_factor(node);
    if (balance_factor > 1) {
        if (binary_node_get_balance_factor(node->left) < 0) binary_node_rotate_left(node->left);
        binary_node_rotate_right(node);
    } else if (balance_factor < -1) {
        if (binary_node_get_balance_factor(node->right) > 0) binary_node_rotate_right(node->right);
        binary_node_rotate_left(node);
    }
}

bool binary_node_contains(BinaryTree* tree, BinaryNode* node, void* e) {
    int c = tree->comperator(node->value, e);
    if (c == 0) return true;

    // Pointer to the node we want to check.
    BinaryNode** relevant_child = (c  > 0) ? &(node->right) : &(node->left);
    
    if ((*relevant_child) == NULL) {
        return false;
    } else {
        return binary_node_contains(tree, *relevant_child, e);
    }
}

void binary_node_traverse(BinaryNode* node, Consumer consumer) {
    if (node->left) binary_node_traverse(node->left, consumer);
    consumer(node->value);
    if (node->right) binary_node_traverse(node->right, consumer);
}

BinaryTree* binary_tree_create(int element_size, Comperator comperator) {
    BinaryTree* created = calloc(1, sizeof(BinaryTree));
    created->element_size = element_size;
    created->comperator = comperator;
    return created;
}

void binary_tree_destroy(BinaryTree* tree) {
    if (tree->root) binary_node_destroy(tree->root);

    free(tree);
}

void binary_tree_add(BinaryTree* tree, void* e) {
    if (tree->root == NULL) {
        tree->root = binary_node_create(e, tree->element_size);
    } else {
        binary_node_add(tree, tree->root, e);
    }
}

bool binary_tree_contains(BinaryTree* tree, void* e) {
    if (tree->root == NULL) return false;

    return binary_node_contains(tree, tree->root, e);
}

void binary_tree_traverse(BinaryTree* tree, Consumer consumer) {
    if (tree->root) binary_node_traverse(tree->root, consumer);
}
