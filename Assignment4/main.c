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
void print_info(T* t, int size){
    for(int i = 0; i < size; i++){
            printf("%d ",t->result[i]);
        }
    printf("\n");
    printf("The total number of tracks traversed by the r/w arm for each algorithm: %d\n",t->number_of_tracks_traversed);
    stat_delay(t, size);
    printf("\n");
    printf("\n");
    printf("\n");
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
            if (track_raw[i]>199){
                fprintf(stderr, "Error: Invalid input. input %d is greater than 199.\n",track_raw[i]);
                return 1;
            }else if(!isUnique(track_raw[i], track_raw, i)){
                fprintf(stderr, "Error: Invalid input. input %d is duplicated.\n",track_raw[i]);
                return 1;
            }
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
    printf("\n");
    printf("\n");

    int* track_FCFS = FCFS(track_raw,num_tracks);
    printf("track_FCFS: ");
    for(int i = 0; i < num_tracks; i++){
            printf("%d ",track_FCFS[i]);
        }
    printf("\n");
    printf("\n");
    printf("\n");

    T* track_SSTF = SSTF(track_raw,num_tracks);
    printf("track_SSTF: ");
    print_info(track_SSTF,num_tracks);

    T* track_SCAN = SCAN(track_raw,num_tracks);
    printf("track_SCAN: ");
    print_info(track_SCAN,num_tracks);

    
    free(track_raw);
    free(track_FCFS);
    free_T(track_SSTF);
    free_T(track_SCAN);
    return 0;
}
