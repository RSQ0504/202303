#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_malloc.h"

Block* free_curr_root = NULL;
Block* used_curr_root = NULL;
Block* head_block_in_memory = NULL;


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
        insert_block->left = NULL;
        insert_block->right = NULL;
        insert_block->height = 1;
        insert_block->free = true;
        insert_block->depth = NULL;
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

            Block* new_root = root->depth;

            root->depth = NULL;
            root->free = false;
            root->left = NULL;
            root->right = NULL;
            root->height = -1;

            return new_root;
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
            Block* temp = root->right;
            Block* prev = root;

            while (temp->left != NULL) {
                prev = temp;
                temp = temp->left;
            }

            Block* new_malloc = (Block*)malloc(sizeof(Block));
            new_malloc->height = temp->height;
            new_malloc->right = temp->right;
            new_malloc->left = temp->left;
            new_malloc->size = temp->size;
            new_malloc->depth = NULL;
            if (prev == root){
                root->right = new_malloc;
            }else{
                prev->left = new_malloc;
            }

            temp->height = root->height;
            temp->left = root->left;
            temp->right = root->right;

            root->depth = NULL;
            root->free = false;
            root->left = NULL;
            root->right = NULL;
            root->height = -1;
            root = temp;

            root->right = free_tree_delete(root->right, new_malloc);
            free(new_malloc);
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

Block* used_tree_insert(Block* root, Block* insert_block) {
    if (root == NULL) {
        insert_block->left = NULL;
        insert_block->right = NULL;
        insert_block->height = 1;
        insert_block->free = false;
        insert_block->depth = NULL;
        return insert_block;
    }
    if (insert_block->start < root->start) {
        root->left = used_tree_insert(root->left, insert_block);
    } else if (insert_block->start > root->start) {
        root->right = used_tree_insert(root->right, insert_block);
    } else {
        return root;
    }

    root->height = 1 + fmax(get_height(root->left), get_height(root->right));

    int balance = get_balance(root);
    if (balance > 1 && insert_block->start < root->left->start) {
        return right_rotation(root);
    }
    if (balance < -1 && insert_block->start > root->right->start) {
        return left_rotation(root);
    }
    if (balance > 1 && insert_block->start > root->left->start) {
        root->left = left_rotation(root->left);
        return right_rotation(root);
    }
    if (balance < -1 && insert_block->start < root->right->start) {
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }
    return root;
}

Block* used_tree_delete(Block* root, Block* picked) {
    if (root == NULL) {
        return NULL;
    }
    if (picked->start < root->start) {
        root->left = used_tree_delete(root->left, picked);
    } else if (picked->start > root->start) {
        root->right = used_tree_delete(root->right, picked);
    } else {
        // Case 1: Node with one child or no child
        if (root->left == NULL || root->right == NULL) {
            Block* temp = (root->left != NULL) ? root->left : root->right;
            // No child case
            if (temp == NULL) {
                root->depth = NULL;
                root->free = true;
                root->left = NULL;
                root->right = NULL;
                root->height = -1;
                root = NULL;
            } else {
                // One child case
                root->depth = NULL;
                root->free = true;
                root->left = NULL;
                root->right = NULL;
                root->height = -1;
                root = temp;
            }
        } else {
            // Case 2: Node with two children
            Block* temp = root->right;
            Block* prev = root;

            while (temp->left != NULL) {
                prev = temp;
                temp = temp->left;
            }

            Block* new_malloc = (Block*)malloc(sizeof(Block));
            new_malloc->height = temp->height;
            new_malloc->right = temp->right;
            new_malloc->left = temp->left;
            new_malloc->start = temp->start;
            new_malloc->depth = NULL;
            if (prev == root){
                root->right = new_malloc;
            }else{
                prev->left = new_malloc;
            }

            temp->height = root->height;
            temp->left = root->left;
            temp->right = root->right;

            root->depth = NULL;
            root->free = true;
            root->left = NULL;
            root->right = NULL;
            root->height = -1;
            root = temp;

            root->right = used_tree_delete(root->right, new_malloc);
            free(new_malloc);
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

void printDotFormat(Block *root) {
    if (root != NULL) {
        if (root->left != NULL) {
            printf("%zu -> %zu;\n", root->size, root->left->size);
            printDotFormat(root->left);
        }
        if (root->right != NULL) {
            printf("%zu -> %zu;\n", root->size, root->right->size);
            printDotFormat(root->right);
        }
    }
}
void printTree(Block *root, int level) {
    if (root != NULL) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("   ");
        }
        printf("%zu\n", root->size);
        printTree(root->left, level + 1);
    }
}

void mem_init() {
    void* memory = (void*)malloc(INITIAL_BLOCK_SIZE);
    if (!memory) return;

    Block* new_block = (Block*)malloc(sizeof(Block));
    if (!new_block) {
        free(memory);
        return;
    }

    new_block->start = memory;
    new_block->size = INITIAL_BLOCK_SIZE;
    new_block->free = true;
    new_block->prev = NULL;
    new_block->next = NULL;

    head_block_in_memory = new_block;
    free_curr_root = free_tree_insert(free_curr_root, new_block);
}

void free_block(Block* curr_free){
    curr_free->free = true;

    if(curr_free->prev!=NULL){
        if (curr_free->prev->free){
            Block* prev_block = curr_free->prev;
            free_curr_root = free_tree_delete(free_curr_root,prev_block);

            curr_free->start = prev_block->start;
            curr_free->size = curr_free->size + prev_block->size;

            curr_free->prev = prev_block->prev;
            if (prev_block->prev!=NULL) {prev_block->prev->next = curr_free;}
            if (prev_block == head_block_in_memory){head_block_in_memory = curr_free;}
            free(prev_block);
        }
    }
    if(curr_free->next!=NULL){
        if (curr_free->next->free){
            Block* next_block = curr_free->next;
            free_curr_root = free_tree_delete(free_curr_root,next_block);
            
            curr_free->size = curr_free->size + next_block->size;

            curr_free->next = next_block->next;
            if (next_block->next!=NULL) {next_block->next->prev = curr_free;}
            free(next_block);
        }
    }

    free_curr_root = free_tree_insert(free_curr_root,curr_free);
}

void* my_malloc(size_t size){
    Block* result = NULL;
    Block* temp_root = free_curr_root;
    while (temp_root) {
        if (temp_root->size == size) {
            result = temp_root;
        } else if (temp_root->size > size) {
            result = temp_root;
            temp_root = temp_root->left;
        } else {
            temp_root = temp_root->right;
        }
    }

    if (result == NULL){
        printf("malloc failed, there is no free block");
        return result;
    }
    free_curr_root = free_tree_delete(free_curr_root, result);
    result->free = false;


    if (result->size>size && result->size - size > 4){
        Block* new_block = (Block*)malloc(sizeof(Block));
        new_block->start = result->start + size;
        new_block->size = result->size - size;
        new_block->free = true;

        result->size = size;

        new_block->prev = result;
        new_block->next = result->next;
        if(result->next!=NULL) {result->next->prev = new_block;}
        result->next = new_block;

        free_block(new_block);
    }
    //printf("%zu\n",result->size);
    used_curr_root = used_tree_insert(used_curr_root,result);
    // printf("\n");
    // printDotFormat(used_curr_root);
    return result->start;
}

void my_free(void *ptr) {
    if (ptr == NULL) return;

    Block* block_to_free = used_curr_root;
    while (block_to_free != NULL && block_to_free->start != ptr) {
        if (ptr < block_to_free->start) {
            block_to_free = block_to_free->left;
        } else {
            block_to_free = block_to_free->right;
        }
    }
    //printf("%zu\n",block_to_free->size);
    
    if (block_to_free == NULL) {
        printf("Error: Attempted to free a non-allocated block\n");
        return;
    }
    used_curr_root = used_tree_delete(used_curr_root,block_to_free);
    // printf("\n");
    // printDotFormat(used_curr_root);
    free_block(block_to_free);
}