#include <stdio.h>
#include "list.h"

int main(){
    List * a = List_create();
    int num[10] = {1,2,3,4,5,6,7,8,9,10};
    List_insert_after(a, &num);
    int* curr = List_curr(a);
    printf("%d\n",* curr);
    List_insert_after(a, &(num[1]));
    curr = List_curr(a);
    printf("%d\n",* curr);
    List_insert_after(a, &(num[2]));
    curr = List_curr(a);
    printf("%d\n",* curr);
    //num = 4;
    //List_insert_after(a, &num);
    //curr = List_curr(a);
    //printf("%d\n",* curr);

    printf("%d\n",List_count(a));
    int* first = List_first(a);
    printf("%d\n",* first);
    int* last = List_last(a);
    printf("%d\n",* last);

    return 0;
}