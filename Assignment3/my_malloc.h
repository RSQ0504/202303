#include <stdbool.h>
#include <stdio.h>



#define INITIAL_BLOCK_SIZE 1024


typedef struct Block_mem Block;

struct Block_mem
{   
    //开始地址和内存块大小
    void* start;
    size_t size;

    bool free;

    // for tree
    // 为AVL tree设计的结构
    Block* right;
    Block* left;
    int height;

    // store the same size block in the same position in tree
    // by creating a 3D depth
    // 由于 AVL 不允许出现重复的key 为了存储同样size的free block 我增加了第三维度.
    Block* depth;

    //用来检查相邻的block是否是free的,如果是就合并
    Block* prev;
    Block* next;
};


int get_balance(Block * node);

int get_height(Block * node);

Block* right_rotation(Block* y);

Block* left_rotation(Block* x);

Block* free_tree_insert(Block* root, Block* insert);



void* mem_init();

void* my_malloc(size_t size);

void my_free(void *ptr);