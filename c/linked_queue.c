#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for the queue
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Queue structure
typedef struct {
    Node *front;  // Pointer to the front of the queue
    Node *rear;   // Pointer to the rear of the queue
} LinkedQueue;

// Function Prototypes
void initQueue(LinkedQueue *q);
bool isEmpty(LinkedQueue *q);
void enqueue(LinkedQueue *q, int value);
int dequeue(LinkedQueue *q, int *outValue);
void displayQueue(LinkedQueue *q);
void freeQueue(LinkedQueue *q);

// Initialize the queue
void initQueue(LinkedQueue *q) {
    q->front = q->rear = NULL;  // Both front and rear are NULL for an empty queue
}

// Check if the queue is empty
bool isEmpty(LinkedQueue *q) {
    return (q->front == NULL);
}

// Enqueue operation: Add an element to the rear of the queue
void enqueue(LinkedQueue *q, int value) {
    // Create a new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);  // Exit if memory allocation fails
    }
    newNode->data = value;
    newNode->next = NULL;

    // If the queue is empty, both front and rear point to the new node
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        // Otherwise, add the new node at the rear and update the rear pointer
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("Enqueued: %d\n", value);
}

// Dequeue operation: Remove an element from the front of the queue
// Returns 0 on success and -1 if the queue is empty.
int dequeue(LinkedQueue *q, int *outValue) {
    if (isEmpty(q)) {
        printf("Queue is empty, nothing to dequeue.\n");
        return -1;  // Indicate failure
    }

    // Remove the front node
    Node *temp = q->front;
    *outValue = temp->data;     // Store the dequeued value in the output parameter
    q->front = q->front->next;  // Move the front pointer to the next node

    // If the queue becomes empty, update the rear pointer to NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);  // Free the memory of the removed node
    printf("Dequeued: %d\n", *outValue);
    return 0;  // Indicate success
}

// Display the elements in the queue
void displayQueue(LinkedQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    Node *temp = q->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);  // Print the data of each node
        temp = temp->next;
    }
    printf("\n");
}

// Free all memory allocated to the queue
void freeQueue(LinkedQueue *q) {
    int tempValue;
    while (!isEmpty(q)) {
        dequeue(q, &tempValue);  // Dequeue all elements to free memory
    }
    printf("Queue has been cleared and memory freed.\n");
}

// Main function
int main() {
    LinkedQueue queue;
    initQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    displayQueue(&queue);

    int value;
    if (dequeue(&queue, &value) == 0) {
        printf("Successfully dequeued value: %d\n", value);
    }

    if (dequeue(&queue, &value) == 0) {
        printf("Successfully dequeued value: %d\n", value);
    }

    displayQueue(&queue);

    freeQueue(&queue);  // Clean up all allocated memory
    return 0;
}
