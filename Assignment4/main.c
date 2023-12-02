#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Dssimul.h"


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
            // printf("%d\n", atoi(value));
            track_raw[i] = atoi(value);
        }
    } else {
        num_tracks = 50;
        track_raw = (int *)malloc((num_tracks) * sizeof(int));
        for (int i = 0; i < num_tracks; ++i) {
            track_raw[i] = rand() % 200;
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

    
    free(track_raw);
    free(track_FCFS);
    return 0;
}
