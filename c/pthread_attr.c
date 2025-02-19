#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *start_routine(void *arg){
    while(1){
        sleep(1);
        printf("In thread loop ...\n");
    }

    return NULL;
}

int main(){

    pthread_t thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread, &attr, start_routine, NULL);

    printf("Main thread start\n");
    sleep(10);

    pthread_attr_destroy(&attr);
    printf("End of the main");
}