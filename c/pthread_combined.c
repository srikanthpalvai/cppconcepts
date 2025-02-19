/*
|-------------------------------------------------------------------------------------|
| Function          | Description                                                    |
|-------------------|-----------------------------------------------------------------|
| pthread_join      | Waits for the thread to finish and retrieves its return value.  |
|                   | Ensures the thread's resources are cleaned up after it ends.   |
|-------------------|-----------------------------------------------------------------|
| pthread_detach    | Allows a background thread to run independently.               |
|                   | Automatically cleans up resources once the thread finishes.    |
|-------------------|-----------------------------------------------------------------|
| pthread_cancel    | Sends a cancellation request to stop a running thread.         |
|                   | Only works if the thread reaches a cancellation point (e.g.,   |
|                   | sleep, read, or pthread_testcancel).                           |
|-------------------------------------------------------------------------------------|
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *compute_square(void *arg) {
    int *input = (int *)arg;
    int *result = malloc(sizeof(int));
    *result = (*input) * (*input);  // Compute the square of the input
    printf("Thread computing square of %d\n", *input);
    return (void *)result;  // Return the result
}

void *background_task(void *arg) {
    while (1) {
        printf("Background task is running...\n");
        sleep(2);  // Simulate periodic work
    }
    return NULL;
}

void *process_request(void *arg) {
    printf("Processing request...\n");
    sleep(5);  // Simulate a long-running operation (5 seconds)
    printf("Request processed.\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;
    void *result;
    int input = 4;

    // Example of pthread_join (waiting for a thread to finish and getting its result)
    pthread_create(&thread1, NULL, compute_square, &input);
    pthread_join(thread1, &result);
    printf("The square of %d is %d\n", input, *((int *)result));
    free(result);  // Free the dynamically allocated memory for the result

    // Example of pthread_detach (running a detached background task)
    pthread_create(&thread2, NULL, background_task, NULL);
    pthread_detach(thread2);  // Detach the background thread

    // Example of pthread_cancel (cancel the request-processing thread)
    pthread_create(&thread3, NULL, process_request, NULL);

    // Let the request-processing thread run for 2 seconds before canceling it
    sleep(2);
    printf("Request is taking too long, canceling thread...\n");
    pthread_cancel(thread3);  // Cancel the request-processing thread

    // Wait for the background thread to run for a while, then exit
    sleep(5);  // Let the detached background task run for 5 seconds

    printf("Main thread exiting.\n");
    return 0;
}
