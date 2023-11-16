#include <stdio.h>
#include <math.h>
#include "list.h"
#include "my_malloc.h"

Block* curr_root = NULL;

Block* findMin(Block* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

int get_height(Block* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int get_balance(Block* node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

Block* right_rotation(Block* y) {
    Block* x = y->left;
    Block* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + fmax(get_height(y->left), get_height(y->right));
    x->height = 1 + fmax(get_height(x->left), get_height(x->right));

    return x;
}

Block* left_rotation(Block* x) {
    Block* y = x->right;
    Block* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + fmax(get_height(x->left), get_height(x->right));
    y->height = 1 + fmax(get_height(y->left), get_height(y->right));

    return y;
}

Block* free_tree_insert(Block* root, Block* insert_block) {
    if (root == NULL) {
        return insert_block;
    }
    if (insert_block->size < root->size) {
        root->left = free_tree_insert(root->left, insert_block);
    } else if (insert_block->size > root->size) {
        root->right = free_tree_insert(root->right, insert_block);
    } else {
        Block* temp_d = root;
        while (temp_d->depth!=NULL){
            temp_d = temp_d->depth;
        }
        temp_d->depth = insert_block;
        return root;
    }

    root->height = 1 + fmax(get_height(root->left), get_height(root->right));

    int balance = get_balance(root);
    if (balance > 1 && insert_block->size < root->left->size) {
        return right_rotation(root);
    }
    if (balance < -1 && insert_block->size > root->right->size) {
        return left_rotation(root);
    }
    if (balance > 1 && insert_block->size > root->left->size) {
        root->left = left_rotation(root->left);
        return right_rotation(root);
    }
    if (balance < -1 && insert_block->size < root->right->size) {
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }
    return root;
}

Block* free_tree_delete(Block* root, Block* picked) {
    if (root == NULL) {
        return NULL;
    }
    if (picked->size < root->size) {
        root->left = free_tree_delete(root->left, picked);
    } else if (picked->size > root->size) {
        root->right = free_tree_delete(root->right, picked);
    } else {
        if(root->depth!=NULL){
            root->depth->left = root->left;
            root->depth->right = root->right;
            root->depth->height = root->height;

            new_root = root->depth

            root->depth = NULL;
            root->free = false;
            root->left = NULL;
            root->right = NULL;
            root->height = -1;

            return new_root
        }
        // Case 1: Node with one child or no child
        if (root->left == NULL || root->right == NULL) {
            Block* temp = (root->left != NULL) ? root->left : root->right;
            // No child case
            if (temp == NULL) {
                root->depth = NULL;
                root->free = false;
                root->left = NULL;
                root->right = NULL;
                root->height = -1;
                root = NULL;
            } else {
                // One child case
                root->depth = NULL;
                root->free = false;
                root->left = NULL;
                root->right = NULL;
                root->height = -1;
                root = temp;
            }
        } else {
            // Case 2: Node with two children
            Block* temp = findMin(root->right);
            root->size = temp->size;
            root->depth = temp->depth;
            root->right = free_tree_delete(root->right, temp);
        }
    }

    if (root == NULL) {
        return NULL;
    }

    root->height = 1 + fmax(get_height(root->left), get_height(root->right));

    int balance = get_balance(root);
    if (balance > 1 && get_balance(root->left) >= 0) {
        return right_rotation(root);
    }
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotation(root->left);
        return right_rotation(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0) {
        return left_rotation(root);
    }
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }
    return root;
}