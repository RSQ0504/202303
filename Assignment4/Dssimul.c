#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Dssimul.h"

int* FCFS(int* raw, int size){
    int* result = (int *)malloc((size) * sizeof(int));
    for(int i =0; i< size; i++){
        result[i] = raw[i];
    }
    return result;
}