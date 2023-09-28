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
}

int main(){
    List * a = List_create();
    List * b = List_create();
    List * c = List_create();
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

    return 0;
}