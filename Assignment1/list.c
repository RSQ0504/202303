#include <stdio.h>
#include "list.h"
int count = 0; 
List* List_create(){
    count += 1;
    List a[10];
    if (count > 10){
        return NULL;
    }
    return &(a[count-1]);
}