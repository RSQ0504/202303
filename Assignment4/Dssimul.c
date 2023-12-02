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

int* SSTF(int* raw, int size) {
    int* result = (int *)malloc((size) * sizeof(int));

    int visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    int current_track = raw[0];
    result[0] = current_track;
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
        result[i] = current_track;
    }

    return result;
}