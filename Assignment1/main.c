#include <stdio.h>
#include "list.h"

int main(){
    for(int i = 0; i<100;i++){
        List * a = List_create();
        if (a == NULL){
            return 0;
        }
        printf("%p\n",a);
    }
    return 0;
}