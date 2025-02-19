#include <stdio.h>
#define SIZE 5
int queue[SIZE];
int front = -1, rear = -1;

void enqueue(int element) {
    
    if(rear == SIZE -1){
        printf("Queue is Full \n");
        return;
    }

    if(front == -1) 
        front = 0;

    queue[++rear] = element;
    printf("Enqueued %d \n", element);
}

void dequeue() {

    if(front == -1){
        printf("Queue is Empty \n");
        return;
    }
    printf("Dequeued %d \n", queue[front]);
    front++;
    if(front > rear)
    {
        front = rear = -1;
    }
}

void display() {

    if(front == -1) {
        printf("Queue is Empty \n");
        return;
    }
    printf("List of elements in the queue:\n");
    for(int i = front; i <= rear ; i++) {
        printf("queue[%d] -> %d \n", i , queue[i]);
    }
}


int main() {

    enqueue(10);  // front = 0, rear = 0
    enqueue(20);  // front = 0, rear = 1
    enqueue(30);  // front = 0, rear = 2
    enqueue(40);  // front = 0, rear = 3
    enqueue(50);  // front = 0, rear = 4
    enqueue(60); // Queue is full;

    display();

    dequeue(); // 10 front = 1, rear = 4
    dequeue(); // 20 front = 2, rear = 4

    display(); // 30, 40, 50

    dequeue(); // 30 front = 3, rear = 4
    dequeue(); // 40 front = 4, rear = 4
    dequeue(); // 50 front = 5, rear = 4

    dequeue(); // Queue is empty 

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
1	Dequeue()	1	4	[10, 20, 30, 40, 50]	Remove 10, move front forward
2	Dequeue()	2	4	[10, 20, 30, 40, 50]	Remove 20, move front forward
3	Dequeue()	3	4	[10, 20, 30, 40, 50]	Remove 30, move front forward
4	Dequeue()	4	4	[10, 20, 30, 40, 50]	Remove 40, move front forward
5	Dequeue()	5	4	[10, 20, 30, 40, 50]	Remove 50, reset the queue and set rear and front to -1

| Feature               | Normal Queue                                         | Circular Queue**                                 |
|-----------------------|------------------------------------------------------|--------------------------------------------------|
| Memory Utilization    | Wastes memory after dequeuing (space is unused).     | Efficient: Reuses space after dequeuing elements.|
| Overflow Condition    | Queue becomes full when `rear == SIZE - 1`.          | Queue becomes full when `rear + 1 == front`.     |
| Enqueue Operation     | Fails if the array is full, but no memory reuse.     | Wraps around to the front if space is available. |
| Dequeue Operation     | Removes from the front, but doesn’t free memory.     | Removes from the front and frees the space.      |
| Example Use Case      | Jobs in a printer (fixed number of jobs).            | Real-time systems (buffering, task scheduling).  |

*/