# Assignment3 Report

### Team member: Hanxi Chen, Rongsheng Qian

## Overall: 

##### In this assignment, we use AVL Tree to manage the memory blocks when we my_malloc or my_free memory. In order to reduce the fragmentation we use AVL tree to find the most suitable memory block (will be explained below). <span style="color:red;">AVL Tree managment </span> is used both in my_malloc and my_free. So the time complexity of these two functions is in<span style="color:red;"> O(log n) </span>with the <span style="color:red;">low fragmentation </span>(as low as using best fit algorithm). We have a defined constant in `my_malloc.h` file for the size of the initial memory block.<span style="color:red;">`#define INITIAL_BLOCK_SIZE 4096`</span>

## Structure:

##### I split the whole memory into several blocks which can support variable number of tasks and form them into `struct`.

##### There are two AVL tree. One is for storing free blocks in memory where its key is `size_t size`. Another is for storing used blocks in memory where its key is `void* start`. Each block can only be stored exactly in one tree (either tree for free blocks or tree for used blocks).

##### **`bool free`: This variable records the status which is to determine whether the block should be in the used block tree or the free block tree.**

##### **`Block* depth`: Traditional AVL tree doesn’t support duplicate keys. However it is possible to have free blocks with the same size. So we invent this varible to allow blocks with the same size store in the same position in the tree by creating a 3D tree, which is similar with `pop` in `stack`.**

##### **` Block* prev;`, `Block* next`: It is Used to check whether adjacent blocks are free, and merge them if they are when we invoke my_free function.**

##### `Block* free_curr_root`, `Block* used_curr_root`: This two global varible in .c file is stored the roots of two tree (free block tree and used block tree).

```C
typedef struct Block_mem Block;
struct Block_mem
{   
    void* start;
    size_t size;
    bool free;
    // for AVL tree
    Block* right;
    Block* left;
    int height;
    Block* depth; // store the same size block in the same position in tree
    Block* prev;//Used to check whether adjacent blocks are free, and merge them if they are
    Block* next;//Used to check whether adjacent blocks are free, and merge them if they are
};
```

## Algorithm Explanation: (in next page)

#### mem_init: `void mem_init();`

* **Malloc the whole memory into one block according to the `define INITIAL_BLOCK_SIZE 4096`**
* **Set its `bool free = ture` and insert it into the free block tree.**

#### my_allocate: `void* my_malloc(size_t size);`

* **Using AVL Tree Search to find best block which is free and have the smallest size bigger thant the size that is needed, remove this block from free block tree.**
* **if the block size is greater than required, I will split the block into two blocks. The first block has `size = required_size`  and the second block has `size = result->size - required_size`. **
* **Insert second block (if existed) into free block tree after merging adjacent free blocks and insert first block into used block tree. Return the first block’s `void* start` <span style="color:red;">Time complexity: O(log n)</span>**

#### my_free: `void my_free(void *ptr);`

* **Search for the block using the given pointer in the used block tree.**
* **Delete the block from the used block tree and update its `free` status to true.**
* **Merge adjacent free blocks if necessary, to minimize fragmentation.**
* **Reinsert the block into the free block tree to make it available for future allocations.**
* **Efficient management of memory via AVL trees ensures reduced fragmentation and balanced tree structure, maintaining <span style="color:red;">O(log n)</span> time complexity for both allocations and deallocations.**

## Evaluation:

#### Performance:

* **Our approach is designed to achieve a balance between time efficiency and fragmentation reduction. The AVL tree structure allows for fast search, insertion, and deletion operations, all of which occur in <span style="color:red;">O(log n) </span>.**
* **The strategy of merging adjacent free blocks upon deallocation helps in reducing fragmentation significantly.**

#### Fragmentation:

* **One of the major challenges in memory management is minimizing fragmentation. Our use of AVL trees for both allocation and deallocation effectively addresses this issue.**
* **By always choosing the smallest available block that fits the request, we prevent unnecessary allocation of larger blocks, thus reducing internal fragmentation.**

#### Conclusion:

* **This memory management system, based on AVL trees, provides an efficient way of allocating and freeing memory. It minimizes fragmentation and ensures quick allocation and deallocation of memory blocks, thereby optimizing overall memory usage in dynamic applications.**
