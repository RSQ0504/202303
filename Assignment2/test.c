#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "list.h"

#define MSG_MAX_LEN 1024
#define LOCAL_PORT 22110
#define REMOTE_PORT 22110
#define REMOTE_IP "192.168.10.147"

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
char current_send[MSG_MAX_LEN] = "";
bool new_item_added;
List* string_list;

void* enter_str(void* arg){
    while (1){

        char new_str[MSG_MAX_LEN];
        fgets(new_str,sizeof(new_str),stdin);

        if (new_str!=""){
            char* temp = (char *)malloc(strlen(new_str)+1);
            strcpy(temp,new_str);
            pthread_mutex_lock(&counter_mutex);
            new_item_added = true;
            List_append(string_list,temp);
            strcpy(current_send,new_str);
            pthread_mutex_unlock(&counter_mutex);
        }
    }
}

void* screen_print(void* arg){
    while (1){
        if (new_item_added){
            system("clear");
            char *temp = List_first(string_list);
            while (temp != NULL)
            {
                printf("<< %s \n",temp);
                temp = List_next(string_list);
            }
            pthread_mutex_lock(&counter_mutex);
            new_item_added = false;
            pthread_mutex_unlock(&counter_mutex);
        }
    }
}

void* listening(void* arg){
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(LOCAL_PORT);

    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket_descriptor,(struct sockaddr*) &sin,sizeof(sin));
    char pre_message[MSG_MAX_LEN];

    while (1){
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char message[MSG_MAX_LEN];
        

        int bytesRx = recvfrom(socket_descriptor, message, MSG_MAX_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);
        int terminateId = (bytesRx < MSG_MAX_LEN) ? bytesRx : MSG_MAX_LEN - 1;
        message[terminateId] = 0;
        if(strcmp(message,pre_message)!=0){
            char* temp = (char *)malloc(terminateId+1);
            strcpy(temp,message);
            pthread_mutex_lock(&counter_mutex);
            new_item_added = true;
            List_append(string_list,temp);
            pthread_mutex_unlock(&counter_mutex);
            
            strcpy(pre_message,message);
        }

        //int incMe = atoi (messageRx);
        //char messageTx[MSG_MAX_LEN];
        //sprintf (messageTx, "Math: %d + 1 = %d\n", incMe, incMe + 1);
    }
}

void* sender(void* arg){
    struct sockaddr_in sin, sinRemote;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(LOCAL_PORT);

    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket_descriptor,(struct sockaddr*) &sin,sizeof(sin));

    memset(&sinRemote, 0, sizeof(sinRemote));
    sinRemote.sin_family = AF_INET;
    sinRemote.sin_port = htons(REMOTE_PORT);
    inet_pton(AF_INET, REMOTE_IP, &(sinRemote.sin_addr));

    while (1){
        int message_len = strlen(current_send);
        pthread_mutex_lock(&counter_mutex);
        sendto(socket_descriptor, current_send, message_len, 0, (struct sockaddr*)&sinRemote, sizeof(sinRemote));
        pthread_mutex_unlock(&counter_mutex);
    }
}

int main(int argCount, char** args){
        for(int i =0; i< argCount;i++){
        printf("Arg %d : %s\n",i,args[i]);
    }
    string_list= List_create();
    pthread_t listener_thread,sender_thread,enter_thread,screen_thread;
    //pthread_mutex_lock(&counter_mutex);
    //......
    //pthread_mutex_unlock(&counter_mutex);
    pthread_create(&listener_thread, NULL, listening, NULL);
    pthread_create(&sender_thread, NULL, sender, NULL);
    pthread_create(&enter_thread, NULL, enter_str, NULL);
    pthread_create(&screen_thread, NULL, screen_print, NULL);


    //pthread_cancel(listener_thread);
    //pthread_cancel(sender_thread);
    //pthread_cancel(enter_thread);
    //pthread_cancel(screen_thread);

    pthread_join(listener_thread, NULL);
    pthread_join(sender_thread, NULL);
    pthread_join(enter_thread, NULL);
    pthread_join(screen_thread, NULL);

    pthread_mutex_destroy(&counter_mutex);
}