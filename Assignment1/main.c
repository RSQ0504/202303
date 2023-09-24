#include <stdio.h>
#include "list.h"

int main(){
    List * a = List_create();
    for(int i = 0; i<100;i++){
        printf("%p\n",a);
    }
    return 0;
}