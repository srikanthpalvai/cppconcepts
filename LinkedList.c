/*
A Linked List is a linear data structure. Every linked list has two parts,
the data section and the address section that holds the address of the next element in the list, which is called a node

A linked list is a linear data structure that includes a series of connected nodes.
Here, each node stores the data and the address of the next node. For example,

Why Linked list?
Arrays can be used to store linear data of similar types, but arrays have the following limitations:
1. The size of the arrays is fixed. 
2. Insertion of a new element / Deletion of a existing element in an array of elements is expensive

Advantages:
1. There is no need to define an initial size
2. Items can be added or removed from the middle of the list

Disadvantages:
1. Random access is not allowed. We have to access elements sequentially starting from the first node(head node)
2. Extra memory space for a pointer is required with each element of the list.
3. Dynamic memory allocation and pointers are required, which complicates the code and increases the risk of memory leaks and segment faults


The notations O(1), O(n), and O(log n) are used to describe the time complexity or order of growth of an algorithm.
They provide an upper bound on the growth of the number of operations required to solve a problem as the size of the input increases.

Here's how you can calculate each of these notations:

O(1): A constant time algorithm is one whose time complexity does not depend on the size of the input. For example,
accessing an element in an array using an index is a constant time operation. The number of operations is constant, regardless of the size of the input. So, in this case, the time complexity is O(1).

O(n): A linear time algorithm is one whose time complexity is directly proportional to the size of the input.
For example, iterating over all elements of an array and performing a constant time operation on each element would result in a linear time complexity of O(n), where n is the size of the array.

O(log n): A logarithmic time algorithm is one whose time complexity increases logarithmically with the size of the input.
For example, finding an element in a binary search tree has a time complexity of O(log n), where n is the number of elements in the tree. The logarithmic nature of the time complexity results from the fact that at each level of the tree, the search space is halved until the target element is found.

It's important to note that these notations provide an upper bound on the time complexity of an algorithm and do not represent the exact number of operations. They are used to compare algorithms and determine which one is more efficient for a given problem size

//fast != NULL && fast->next != NULL 
//Typically to check whether it is safe to access the "next" element in a linked list, where "fast" is a pointer to the current element being processed.
*/
// Insert node at first, last and middle of the linked list and Remove node first,last and middle of the linked list
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  int data;
  struct node *next;
};

void printList(struct node* head){
	struct node *temp = head;
	printf("\n\nList elements are - \n");
	while(temp != NULL) {
	  printf("%d --->",temp->data);
	  temp = temp->next;
	}
}
void insertFirst(struct node** head, int val){
	struct node *newnode;
	newnode = (struct node *)malloc(sizeof(struct node));
	newnode->data = val;	
	newnode->next = *head;
	*head = newnode;
}

void insertLast(struct node** head, int val){
	// Create New node
	struct node *newnode;
    printf("check ..1");
	// This new node is going to be the last node, so make next of it as NULL
	newnode = (struct node *)malloc(sizeof(struct node));
	newnode->data = val;
	newnode->next = NULL;
	printf("check ..2");
	// If the Linked List is empty, then make the new node as head
	if(*head == NULL){
		*head = newnode;
		printf("check ..3");
		return;
	}else{
		struct node *lastnode = *head;
		printf("check ..4");
		//Traverse till the last node
		while(lastnode->next != NULL){
			lastnode = lastnode->next;
			printf("check ..5");
		}
		lastnode->next = newnode;		
		printf("check ..6");
	}
	printf("check ..7");
}
void insertMiddle(struct node** head, int val, int position){
	// Create New node
	struct node *newnode, *temp;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = val;
	
	temp = *head;
	for(int i=2;i<position;i++){
		if(temp->next!=NULL){
			temp = temp->next;
		}
	}
	//Change next pointers to include new node in between
	newnode->next = temp->next;
	temp->next = newnode;
	
}
void removeFirst(struct node** head){
	struct node *temp;
	temp = *head;
	*head = temp->next;
}
void removeLast(struct node** head){
	// Create node 
	struct node* second_last;
	second_last = *head;

	// Here we are trying to check the next of next. With this we can reduce number of iterations
	while(second_last->next->next!=NULL){
		second_last = second_last->next;
	}
	second_last->next = NULL;	
}

void removeMiddle(struct node** head, int position){
	struct node *temp;	
	temp = *head;
	for(int i=2;i<position;i++){
		if(temp->next!=NULL){
			temp = temp->next;
		}
	}
	temp->next = temp->next->next;
	
}

bool hasCycle(struct node** head){
	if(*head == NULL){
		return false;
	}
	struct node *slow = *head;
	struct node *fast = *head;
	while(fast != NULL && fast->next != NULL)
	{

		fast = fast->next->next;
		slow = slow->next;			
		if(fast == slow){
			return true;
		}
	}
	return false;
}

void makeloop(struct node** head, int k)
{
    //initialize 'temp' with the first node
    struct node* temp = *head;
    int count = 1;
    //run a while loop till 'count' is
    //less than 'k'
    while (count < k) {
        temp = temp->next;
        count++;
    }
 
    //save the Kth node in a variable
    struct node* kth_node = temp;
 
    //traverse the list till we reach
    //the tail node 
    while (temp->next != NULL)
        temp = temp->next;
 
    //join the last node with the Kth node
    temp->next = kth_node;
}

int countNode(struct node *slow){
	struct node *tmp = slow;
	int count = 1;
	while(tmp->next != slow){
		count++;
		tmp = tmp->next;
	}
	return count;
}

int countNodesinLoop(struct node** head){
	struct node *slow = *head;
	struct node *fast = *head;
	while(slow && fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast){
			printf("countNodesinLoop present \n");
			return countNode(slow);
		}
	}
	return 0;
}
struct node* middleelement(struct node** head){
	struct node *slow = *head;
	struct node *fast = *head;
	
	while(fast !=NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

int main(){

	/* Initialize nodes */
	struct node *head = NULL;
	struct node *one = NULL;
	struct node *two = NULL;
	struct node *three = NULL;	
	
	/* Allocate memory */
	one = (struct node *)malloc(sizeof(struct node));
	two = (struct node *)malloc(sizeof(struct node));
	three = (struct node *)malloc(sizeof(struct node));

	/* Assign data values */
	one->data = 1;
	two->data = 2;
	three->data=3;
		
	/* Connect nodes */
	one->next = two;
	two->next = three;
	three->next = NULL;	

	/* Save address of first node in head */
	head = one;
	printList(head); 	// 1 --->2 --->3 --->

	insertFirst(&head, 0);
	printList(head);	// 0--->1 --->2 --->3 --->
	
	insertLast(&head, 4);
	printList(head);	// 0--->1 --->2 --->3 --->4

	insertMiddle(&head,5,4);
	printList(head); // 0 --->1 --->2 --->5 --->3 --->4 --->

	removeFirst(&head);
	printList(head); // 1 --->2 --->5 --->3 --->4 --->

	removeLast(&head);
	printList(head); // 1 --->2 --->5 --->3 --->

	insertLast(&head, 6);
	insertLast(&head, 7); //1 --->2 --->5 --->3 --->6 --->7
	printList(head);
	
	hasCycle(&head) ? printf("Loop present \n") : printf("Loop not present \n");

	struct node* middle = middleelement(&head);
	printf("middle->data: %d\n", middle->data);

	makeloop(&head, 3); //1 --->2 --->5 --->3 --->6 --->7 --->5 --->3 --->6 --->7
	hasCycle(&head) ? printf("Loop present \n") : printf("Loop not present \n");
	int n = countNodesinLoop(&head);
	printf("loop count:%d \n", n); 
	//printList(head); //Infinate loop  //1 --->2 --->5 --->3 --->6 --->7 --->5 --->3 --->6 --->7 --->5 --->3 --->6 --->7 --->5 --->3 --->6 --->7
	return 0;
}