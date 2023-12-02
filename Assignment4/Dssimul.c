#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Dssimul.h"

void free_T(T* t){
    free(t->delay);
    free(t->result);
    free(t);
}

void stat_delay(T* t, int size){
    float count = 0;
    float total = 0;
    int max_delay = 0;
    int max_delay_track = 0;
    for(int i = 0; i < size; i++){
            if(t->delay[i]!=0){
                int track = t->result[i];
                int delay = t->delay[i];
                if (delay>max_delay){
                    max_delay = delay;
                    max_delay_track = track;
                }
                count ++;
                total += delay;
                //printf("track: %d delay: %d; ",track,delay);
            }
        }
    printf("longest delay track: %d longest delay: %d; ",max_delay_track,max_delay);
    printf("\n");
    printf("avg delay: %f", total/count);
}

int* FCFS(int* raw, int size){
    int* result = (int *)malloc((size) * sizeof(int));
    for(int i =0; i< size; i++){
        result[i] = raw[i];
    }
    return result;
}

T* SSTF(int* raw, int size) {
    T* tuple = (T*)malloc(sizeof(T));
    tuple->result = (int *)malloc((size) * sizeof(int));
    tuple->delay = (int *)malloc((size) * sizeof(int));

    int visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    int current_track = raw[0];
    tuple->result[0] = current_track;
    visited[0] = 1;


    for (int i = 1; i < size; i++) {
        int min_distance = 999999;
        int index = -1;

        for (int j = 0; j < size; j++) {
            if (!visited[j]) {
                int distance = abs(raw[j] - current_track);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }
        visited[index] = 1;
        current_track = raw[index];
        tuple->result[i] = current_track;

        if (i > index){
            tuple->delay[i] = i - index;
        }else{
            tuple->delay[i] = 0; // NO delays
        }
    }

    return tuple;
}