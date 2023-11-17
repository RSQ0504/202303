#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "my_malloc.h"
int main(){
    Block* block1 = (Block*)malloc(sizeof(Block));
    block1->size =1;
    Block* block2 = (Block*)malloc(sizeof(Block));
    block2->size =10;
    Block* block3 = (Block*)malloc(sizeof(Block));
    block3->size =5;
    Block* block4 = (Block*)malloc(sizeof(Block));
    block4->size =20;
    Block* block5 = (Block*)malloc(sizeof(Block));
    block5->size =15;
    Block* block6 = (Block*)malloc(sizeof(Block));
    block6->size =12;
    Block* block7 = (Block*)malloc(sizeof(Block));
    block7->size =16;
    Block* block8 = (Block*)malloc(sizeof(Block));
    block8->size =8;
    
    Block* root = NULL;
    root = free_tree_insert(root,block1);
    root = free_tree_insert(root,block2);
    root = free_tree_insert(root,block3);
    root = free_tree_insert(root,block4);
    root = free_tree_insert(root,block5);
    root = free_tree_insert(root,block6);
    root = free_tree_insert(root,block7);
    root = free_tree_insert(root,block8);
    

    printDotFormat(root);
    printf("\n\n\n");
    
    root = free_tree_delete(root, block4);
    printDotFormat(root);
    printf("\n\n\n");
    root = free_tree_delete(root, block5);
    printDotFormat(root);


    free(block1);
    free(block2);
    free(block3);
    free(block4);
    free(block5);
    free(block6);
    free(block7);
    free(block8);


    return 0;
}