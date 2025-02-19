#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

void enqueue(int element) {
    if ((rear + 1) % SIZE == front) {
        printf("Queue is full! Cannot enqueue %d\n", element);
        return;
    }
    if (front == -1) front = 0;
    rear = (rear + 1) % SIZE;
    queue[rear] = element;
    printf("Enqueued: %d\n", element);
    printf("front:%d, rear:%d \n", front, rear);

}

void dequeue() {
    if (front == -1) {
        printf("Queue is empty! Cannot dequeue\n");
        return;
    }
    printf("Dequeued: %d\n", queue[front]);
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
    printf("front:%d, rear:%d \n", front, rear);
}

void display() {
    if (front == -1) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display();

    dequeue();
    dequeue();
    display();

    enqueue(60);
    enqueue(70);
    display();

    return 0;
}

/*
Enqueue Example:

Queue Size: SIZE = 5

Step	Operation	front	rear	Queue Array	Comment
1	Initialize	-1	-1	[_, _, _, _, _]	Queue is empty
2	Enqueue(10)	0	0	[10, _, _, _, _]	First element added
3	Enqueue(20)	0	1	[10, 20, _, _, _]	Add 20 to rear
4	Enqueue(30)	0	2	[10, 20, 30, _, _]	Add 30 to rear
5	Enqueue(40)	0	3	[10, 20, 30, 40, _]	Add 40 to rear
6	Enqueue(50)	0	4	[10, 20, 30, 40, 50]	Add 50 to rear
7	Enqueue(60)	0	4	[10, 20, 30, 40, 50]	Queue is full


Dequeue Example:

Starting with the queue after the above enqueue operations:
Queue = [10, 20, 30, 40, 50], front = 0, rear = 4.

Step	Operation	front	rear	Queue Array	Comment
1	Dequeue(10)	1	4	[10, 20, 30, 40, 50]	Remove 10
2	Dequeue(20)	2	4	[10, 20, 30, 40, 50]	Remove 20
3	Enqueue(60)	2	0	[60, 20, 30, 40, 50]	Add 60, rear wraps to index 0
4	Enqueue(70)	2	1	[60, 70, 30, 40, 50]	Add 70, rear moves to index 1


| Feature               | Normal Queue                                         | Circular Queue**                                 |
|-----------------------|------------------------------------------------------|--------------------------------------------------|
| Memory Utilization    | Wastes memory after dequeuing (space is unused).     | Efficient: Reuses space after dequeuing elements.|
| Overflow Condition    | Queue becomes full when `rear == SIZE - 1`.          | Queue becomes full when `rear + 1 == front`.     |
| Enqueue Operation     | Fails if the array is full, but no memory reuse.     | Wraps around to the front if space is available. |
| Dequeue Operation     | Removes from the front, but doesn’t free memory.     | Removes from the front and frees the space.      |
| Example Use Case      | Jobs in a printer (fixed number of jobs).            | Real-time systems (buffering, task scheduling).  |

*/