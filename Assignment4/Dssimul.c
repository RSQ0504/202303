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
    tuple->number_of_tracks_traversed = 0;
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
        tuple->number_of_tracks_traversed += abs(tuple->result[i] - tuple->result[i-1]);
        // printf("%d ",tuple->number_of_tracks_traversed);
        if (i > index){
            tuple->delay[i] = i - index;
        }else{
            tuple->delay[i] = 0; // NO delays
        }
    }

    return tuple;
}

T* SCAN(int* raw, int size) {
    T* tuple = (T*)malloc(sizeof(T));
    tuple->number_of_tracks_traversed = 0;
    tuple->result = (int *)malloc((size) * sizeof(int));
    tuple->delay = (int *)malloc((size) * sizeof(int));

    int temp_raw[size];
    int start_index = 0;
    for (int i = 0; i < size; i++) {
        temp_raw[i] = raw[i];
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (temp_raw[j] > temp_raw[j + 1]) {
                if (j == start_index){
                    start_index++;
                }
                int temp = temp_raw[j];
                temp_raw[j] = temp_raw[j + 1];
                temp_raw[j + 1] = temp;
            }
        }
    }

    int current_track = temp_raw[start_index];
    int result_index = 0;
    tuple->result[result_index] = current_track;

    for (int i = start_index - 1; i >= 0; i--) {
        result_index ++;
        tuple->result[result_index] = temp_raw[i];
        tuple->number_of_tracks_traversed += abs(tuple->result[result_index] - tuple->result[result_index-1]);
    }

    tuple->number_of_tracks_traversed += 2 * tuple->result[result_index];

    for (int i = start_index+1; i < size; i++) {
        result_index ++;
        tuple->result[result_index] = temp_raw[i];
        tuple->number_of_tracks_traversed += abs(tuple->result[result_index] - tuple->result[result_index-1]);
    }
    return tuple;
}