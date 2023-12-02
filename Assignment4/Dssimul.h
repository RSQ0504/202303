#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tuple T;
struct Tuple
{
    int* result;
    int* delay;
    int number_of_tracks_traversed;
};

void free_T(T* t);

void stat_delay(T* t,int size);

int* FCFS(int* raw, int size);

T* SSTF(int* raw, int size);