// #include <stdio.h>
// #define SIZE 5

// int queue[SIZE];
// int front = -1, rear = -1;

// void enqueue(int value) {
//     if ((rear + 1) % SIZE == front) {
//         printf("Queue is Full\n");
//         return;
//     }
//     if (front == -1) front = 0;
//     rear = (rear + 1) % SIZE;
//     queue[rear] = value;
// }

// void dequeue() {
//     if (front == -1) {
//         printf("Queue is Empty\n");
//         return;
//     }
//     printf("Deleted: %d\n", queue[front]);
//     if (front == rear) {
//         front = rear = -1; // Queue becomes empty
//     } else {
//         front = (front + 1) % SIZE;
//     }
// }

// void display() {
//     if (front == -1) {
//         printf("Queue is Empty\n");
//         return;
//     }
//     printf("Queue: ");
//     int i = front;
//     while (1) {
//         printf("%d ", queue[i]);
//         if (i == rear) break;
//         i = (i + 1) % SIZE;
//     }
//     printf("\n");
// }

// int main() {
//     enqueue(10);
//     enqueue(20);
//     enqueue(30);
//     enqueue(40);
//     enqueue(50); // Queue should be full here
//     display();
//     dequeue();
//     dequeue();
//     display();
//     enqueue(60);
//     enqueue(70);
//     display();
//     return 0;
// }
 #include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node *front = NULL, *rear = NULL;

void enqueue(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
        rear->next = front; // Circular link
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front; // Maintain circular link
    }
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is Empty\n");
        return;
    }

    if (front == rear) {
        printf("Deleted: %d\n", front->data);
        free(front);
        front = rear = NULL;
    } else {
        struct Node* temp = front;
        printf("Deleted: %d\n", temp->data);
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

void display() {
    if (front == NULL) {
        printf("Queue is Empty\n");
        return;
    }

    struct Node* temp = front;
    printf("Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    dequeue();
    display();
    enqueue(40);
    enqueue(50);
    display();
    return 0;
}
