#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "list.h"

#define MSG_MAX_LEN 1024

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool new_item_added;
bool running = true;  // Global variable indicating running state
List* string_list;
List* need_to_send;

int REMOTE_PORT;
int LOCAL_PORT;
char REMOTE_IP[100];  // Assuming IP address < 100 characters

void* enter_str(void* arg) {
    while (running) {
        char new_str[MSG_MAX_LEN];
        fgets(new_str, sizeof(new_str), stdin);

        if (strlen(new_str) != 0) {
            char* temp = (char *)malloc(strlen(new_str) + 1);
            strcpy(temp, new_str);
            pthread_mutex_lock(&counter_mutex);
            new_item_added = true;
            List_append(need_to_send, temp);
            if (strcmp(new_str, "!\n") == 0) {
                running = false;
            }
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&counter_mutex);
        }
    }
    return NULL;
}

void* screen_print(void* arg) {
    while (1) {
        if (new_item_added) {
            pthread_mutex_lock(&counter_mutex);
            char *temp = List_trim(string_list);
            if (temp != NULL) {
                fputs(">> ", stdout);
                fputs(temp, stdout);
            }
            new_item_added = false;
            pthread_mutex_unlock(&counter_mutex);
            free(temp);
        }
        if(running==false) break;
    }
    return NULL;
}

void* listening(void* arg) {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(LOCAL_PORT);

    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket_descriptor, (struct sockaddr*) &sin, sizeof(sin));

    while (running) {
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char message[MSG_MAX_LEN];

        int bytesRx = recvfrom(socket_descriptor, message, MSG_MAX_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);
        int terminateId = (bytesRx < MSG_MAX_LEN) ? bytesRx : MSG_MAX_LEN - 1;
        message[terminateId] = 0;

        char* temp = (char *)malloc(terminateId + 1);
        strcpy(temp, message);
        pthread_mutex_lock(&counter_mutex);
        new_item_added = true;
        List_append(string_list, temp);
        if (strcmp(temp, "!\n") == 0) {
                running = false;
            }
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

void* sender(void* arg) {
    struct sockaddr_in sin, sinRemote;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(LOCAL_PORT);

    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket_descriptor, (struct sockaddr*) &sin, sizeof(sin));

    memset(&sinRemote, 0, sizeof(sinRemote));
    sinRemote.sin_family = AF_INET;
    sinRemote.sin_port = htons(REMOTE_PORT);
    inet_pton(AF_INET, REMOTE_IP, &(sinRemote.sin_addr));

    while (1) {
        pthread_mutex_lock(&counter_mutex);
        pthread_cond_wait(&cond, &counter_mutex);
        pthread_mutex_unlock(&counter_mutex);

        char* current_send = List_trim(need_to_send);
        if (current_send == NULL) {
            continue;
        }
        int message_len = strlen(current_send);
        pthread_mutex_lock(&counter_mutex);
        sendto(socket_descriptor, current_send, message_len, 0, (struct sockaddr*)&sinRemote, sizeof(sinRemote));
        pthread_mutex_unlock(&counter_mutex);
        free(current_send);
        if(running==false) break;
    }
    return NULL;
}

void initializeGlobalsFromArgs(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <LOCAL_PORT> <REMOTE_IP> <REMOTE_PORT>\n", argv[0]);
        exit(1);
    }

    LOCAL_PORT = atoi(argv[1]);
    strncpy(REMOTE_IP, argv[2], sizeof(REMOTE_IP));
    REMOTE_PORT = atoi(argv[3]);
}

int main(int argCount, char** args) {
    
    initializeGlobalsFromArgs(argCount, args);

    string_list = List_create();
    need_to_send = List_create();
    pthread_t listener_thread, sender_thread, enter_thread, screen_thread;

    pthread_create(&listener_thread, NULL, listening, NULL);
    pthread_create(&sender_thread, NULL, sender, NULL);
    pthread_create(&enter_thread, NULL, enter_str, NULL);
    pthread_create(&screen_thread, NULL, screen_print, NULL);

    // Wait for threads to finish using the running state
    while (running) {
        sleep(1);
    }

    // Cancel the threads after running state is set to false
    pthread_cancel(listener_thread);
    pthread_cancel(sender_thread);
    pthread_cancel(enter_thread);
    pthread_cancel(screen_thread);

    // Join the threads
    pthread_join(listener_thread, NULL);
    pthread_join(sender_thread, NULL);
    pthread_join(enter_thread, NULL);
    pthread_join(screen_thread, NULL);

    pthread_mutex_destroy(&counter_mutex);
    return 0;
}