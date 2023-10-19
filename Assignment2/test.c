#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define MSG_MAX_LEN 1024
#define PORT 22110
void* listening(void* arg){
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    //inet_pton(AF_INET, "127.0.0.1", &(sin.sin_addr))
    sin.sin_port = htons(PORT);

    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket_descriptor,(struct sockaddr*) &sin,sizeof(sin));

    while (1){
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);

        char message[MSG_MAX_LEN];
        int bytesRx = recvfrom(socket_descriptor, message, MSG_MAX_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);
        
        int terminateId = (bytesRx < MSG_MAX_LEN) ? bytesRx : MSG_MAX_LEN - 1;
        message[terminateId] = 0;
        printf (">>'%s'\n", message);
        //int incMe = atoi (messageRx);
        //char messageTx[MSG_MAX_LEN];
        //sprintf (messageTx, "Math: %d + 1 = %d\n", incMe, incMe + 1);
    }
}

int main(int argCount, char** args){
        for(int i =0; i< argCount;i++){
        printf("Arg %d : %s\n",i,args[i]);
    }

    pthread_t listener_thread;
    pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
    //pthread_mutex_lock(&counter_mutex);
    //......
    //pthread_mutex_unlock(&counter_mutex);
    pthread_create(&listener_thread, NULL, listening, NULL);
    pthread_join(listener_thread, NULL);
    pthread_mutex_destroy(&counter_mutex);
}