/*
/*
 * Summary Table of Real-World Use Cases for pthread_cancel
 *
 * +---------------------+-----------------------------------------------------------+
 * | Use Case            | Real-World Example                                       |
 * +---------------------+-----------------------------------------------------------+
 * | Timeout management  | Canceling file downloads, database queries, or video      |
 * |                     | buffer threads.                                           |
 * | User cancellations  | Stopping uploads/downloads, canceling filters in          |
 * |                     | Photoshop, or terminating AI training.                   |
 * | Server requests     | Canceling threads handling disconnected clients in web    |
 * |                     | servers.                                                 |
 * | Task queue systems  | Terminating worker threads for canceled or obsolete jobs. |
 * | IoT control         | Stopping monitoring of IoT devices when removed from the  |
 * |                     | system.                                                  |
 * +---------------------+-----------------------------------------------------------+
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *arg){

    printf("From the thread function\n");

    for (int i = 0; i < 10; i++){
        printf("Sleep ...\n");
        sleep(1);
    }

    printf("thread function exit\n");
    return NULL;

}

int main(){

    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);

    // Let the thread work for 3 seconds
    sleep(3);

    // cancel the thread 

    if(pthread_cancel(thread) != 0)
    {
        printf("pthread cancel fail \n");
    }

    // wait for thread to terminarte 
    if (pthread_join(thread, NULL) != 0){
        printf("pthread join fail \n");
    }
    printf("Thread has been cancelled.\n");

    printf("Main thread exit \n");
    return 0;
}

