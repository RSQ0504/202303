#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "my_malloc.h"
int main(){
    mem_init();
    void* ptr = (void*)my_malloc(10);
    printf("Initial address: %p\n", (void*)ptr);
    void* ptr1 = (void*)my_malloc(1);
    printf("Initial address: %p\n", (void*)ptr1);
    void* ptr2 = (void*)my_malloc(1024);
    printf("Initial address: %p\n", (void*)ptr2);

    return 0;
}