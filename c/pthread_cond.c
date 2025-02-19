#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_data_ready = PTHREAD_COND_INITIALIZER;
int shared_data = 0;
int data_ready = 0;

void *producer_thread(void *arg){

    printf("In producer thread ...\n");
    
    while(1) {

        pthread_mutex_lock(&mutex);
        shared_data++;
        data_ready = 1;

        printf("Producer: Data ready, signaling consumer.\n");
        pthread_cond_signal(&cond_data_ready); //// Signal the consumer

        pthread_mutex_unlock(&mutex);   

        sleep(2); // Simulate processing delay

        // Simulate more production cycles 
    }
    return NULL;
}

void *consumer_thread(void *){
    printf("In Consumer thread ...\n");

    while(1) {
        pthread_mutex_lock(&mutex);

        while(!data_ready){
            printf("Consumer: Waiting for data...\n");
            pthread_cond_wait(&cond_data_ready, &mutex);
        }
        printf("Consumer: Consumed data.\n");
        data_ready = 0; // Mark data as consumed
        pthread_mutex_unlock(&mutex);

        sleep(2); // Simulate processing delay

    }

    return NULL; 
}
int main() {

    pthread_t producer, consumer;

    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_data_ready);
    return 0;
}