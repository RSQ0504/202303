#include <stdio.h>
#include "my_malloc.h"

int main() {
    mem_init();

    // 基本分配测试
    void* ptr = (void*)my_malloc(10);
    printf("Address of allocated 10 bytes: %p\n", ptr);
    void* ptr1 = (void*)my_malloc(1);
    printf("Address of allocated 1 byte: %p\n", ptr1);
    void* ptr2 = (void*)my_malloc(1024);
    printf("Address of allocated 1024 bytes: %p\n", ptr2);

    // 释放并重新分配内存
    my_free(ptr);
    ptr = my_malloc(5);
    printf("Address after reallocating 5 bytes: %p\n", ptr);

    // 大块内存分配和释放
    void* ptr3 = my_malloc(2048);
    printf("Address of allocated 2048 bytes: %p\n", ptr3);
    my_free(ptr3);

    // 小块内存的频繁分配和释放
    for (int i = 0; i < 10; i++) {
        void* temp = my_malloc(15);
        printf("Address of allocated 15 bytes: %p\n", temp);
        my_free(temp);
    }

    // 释放非连续内存块
    my_free(ptr1);
    void* ptr4 = my_malloc(500);
    printf("Address of allocated 500 bytes: %p\n", ptr4);

    // 释放所有内存
    my_free(ptr);
    my_free(ptr2);
    my_free(ptr4);

    return 0;
}
