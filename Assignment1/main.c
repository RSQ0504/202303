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
    List_insert_before(a,&(num[8]));
    print_list(a);
    return 0;
}