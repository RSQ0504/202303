#include <stdio.h>
#include "list.h"

void print_list(List* pList){
    int* temp = List_first(pList);
    while (temp != NULL)
    {
        printf("%d",*temp);
        temp = List_next(pList);
    }
    printf("\n");
    temp = List_last(pList);
    while (temp != NULL)
    {
        printf("%d",*temp);
        temp = List_prev(pList);
    }
    printf("\n");
    printf("%d\n",List_count(pList));
}

void freeitem(void* pItem) {
    int * temp;
    if (pItem != NULL) {
        temp = pItem;
        printf("delete %d\n",*temp);
    }
}

bool compare_item(void* pItem, void* pComparisonArg){
    if(pItem==pComparisonArg){
        return true;
    }else{
        return false;
    }
}

int main(){
    List * a = List_create();
    List * b = List_create();
    List * c = List_create();
    List * d = List_create();
    List * e = List_create();
    List * f = List_create();
    List * g = List_create();
    List * h = List_create();
    List * i = List_create();
    List * io = List_create();
    List * re = List_create();
    List * OO = List_create();
    if (OO==NULL){
        printf("out of list");
    }
    int num[10] = {1,2,3,4,5,6,7,8,9,10};
    List_prepend(a,&(num[1]));
    List_append(a,&(num[2]));
    List_append(a,&(num[3]));
    List_append(a,&(num[4]));
    List_append(b,&(num[5]));
    List_append(b,&(num[6]));
    List_append(b,&(num[7]));
    List_append(b,&(num[8]));
    print_list(a);
    print_list(b);
    List_concat(a,b);
    print_list(a);
    
    List_last(a);
    List_remove(a);
    print_list(a);
    List_first(a);
    List_remove(a);
    print_list(a);

    List_remove(b);
    print_list(b);

    int* hi = List_search(a,compare_item,&(num[3]));
    printf("hi: %d\n",*hi);

    List_free(a,freeitem);
    print_list(a);

    OO = List_create();
    if (OO==NULL){
        printf("out of list");
    }
    return 0;
}