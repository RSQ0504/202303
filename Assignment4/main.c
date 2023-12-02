#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Dssimul.h"

bool isUnique(int track, int* tracks, int count) {
    for (int i = 0; i < count; i++) {
        if (tracks[i] == track) {
            return false;
        }
    }
    return true;
}

int main(int argCount, char** args) {
    int num_tracks = 0;
    int *track_raw = NULL;

    if (argCount > 1) {
        char *inputCopy = strdup(args[1]);
        char *value = strtok(inputCopy, ",");
        while (value != NULL) {
            num_tracks ++;
            value = strtok(NULL, ",");
        }
        free(inputCopy);
        track_raw = (int *)malloc((num_tracks) * sizeof(int));
        track_raw[0] = atoi(strtok(args[1], ","));
        for(int i = 1; i < num_tracks; i++){
            value = strtok(NULL, ",");
            track_raw[i] = atoi(value);
        }
    } else {
        num_tracks = 50;
        track_raw = (int *)malloc((num_tracks) * sizeof(int));
        for (int i = 0; i < num_tracks; i++) {
            int track = rand() % 200;
            while(!isUnique(track, track_raw, i)){
                track = rand() % 200;
            }
            track_raw[i] = track;
        }
    }
    if (num_tracks<3) {
        fprintf(stderr, "Error: Invalid input. Please enter three numbers.\n");
        return 1;
    }

    printf("Total number: %d\n",num_tracks);
    printf("track_raw: ");
    for(int i = 0; i < num_tracks; i++){
            printf("%d ",track_raw[i]);
        }
    printf("\n");

    int* track_FCFS = FCFS(track_raw,num_tracks);
    printf("track_FCFS: ");
    for(int i = 0; i < num_tracks; i++){
            printf("%d ",track_FCFS[i]);
        }
    printf("\n");

    int* track_SSTF = SSTF(track_raw,num_tracks);
    printf("track_SSTF: ");
    for(int i = 0; i < num_tracks; i++){
            printf("%d ",track_SSTF[i]);
        }
    printf("\n");


    free(track_raw);
    free(track_FCFS);
    return 0;
}
