// #include <stdio.h>
// #include <stdlib.h>

// #define SIZE 100

// // Stack structure
// struct Stack {
//     int arr[SIZE];
//     int top;
// };

// // Initialize a stack
// void initStack(struct Stack* s) {
//     s->top = -1;
// }

// // Check if stack is empty
// int isEmpty(struct Stack* s) {
//     return s->top == -1;
// }

// // Check if stack is full
// int isFull(struct Stack* s) {
//     return s->top == SIZE - 1;
// }

// // Push to stack
// void push(struct Stack* s, int value) {
//     if (isFull(s)) {
//         printf("Stack Overflow\n");
//         return;
//     }
//     s->arr[++(s->top)] = value;
// }

// // Pop from stack
// int pop(struct Stack* s) {
//     if (isEmpty(s)) {
//         printf("Stack Underflow\n");
//         return -1;
//     }
//     return s->arr[(s->top)--];
// }

// // Peek top of stack
// int peek(struct Stack* s) {
//     if (isEmpty(s)) {
//         return -1;
//     }
//     return s->arr[s->top];
// }

// // Queue using two stacks
// struct Queue {
//     struct Stack s1, s2;
// };

// // Initialize the queue
// void initQueue(struct Queue* q) {
//     initStack(&(q->s1));
//     initStack(&(q->s2));
// }

// // Costly push operation
// void enqueue(struct Queue* q, int value) {
//     // Move all elements from s1 to s2
//     while (!isEmpty(&q->s1)) {
//         push(&q->s2, pop(&q->s1));
//     }

//     // Push new element to s1
//     push(&q->s1, value);

//     // Move everything back to s1 from s2
//     while (!isEmpty(&q->s2)) {
//         push(&q->s1, pop(&q->s2));
//     }

//     printf("Enqueued: %d\n", value);
// }

// // Cheap dequeue operation
// void dequeue(struct Queue* q) {
//     if (isEmpty(&q->s1)) {
//         printf("Queue is Empty\n");
//         return;
//     }
//     int removed = pop(&q->s1);
//     printf("Dequeued: %d\n", removed);
// }

// // Display queue
// void display(struct Queue* q) {
//     if (isEmpty(&q->s1)) {
//         printf("Queue is Empty\n");
//         return;
//     }
//     printf("Queue: ");
//     for (int i = 0; i <= q->s1.top; i++) {
//         printf("%d ", q->s1.arr[i]);
//     }
//     printf("\n");
// }

// // Main function
// int main() {
//     struct Queue q;
//     initQueue(&q);

//     enqueue(&q, 10);
//     enqueue(&q, 20);
//     enqueue(&q, 30);
//     display(&q);

//     dequeue(&q);
//     display(&q);

//     enqueue(&q, 40);
//     display(&q);

//     dequeue(&q);
//     dequeue(&q);
//     dequeue(&q);
//     dequeue(&q);  // Underflow test

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Stack structure
struct Stack {
    int arr[SIZE];
    int top;
};

// Initialize a stack
void initStack(struct Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(struct Stack* s) {
    return s->top == SIZE - 1;
}

// Push to stack
void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

// Pop from stack
int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

// Peek top of stack
int peek(struct Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->arr[s->top];
}

// Queue using two stacks
struct Queue {
    struct Stack s1, s2;
};

// Initialize the queue
void initQueue(struct Queue* q) {
    initStack(&(q->s1));
    initStack(&(q->s2));
}

// Costly push operation
void enqueue(struct Queue* q, int value) {
    // Move all elements from s1 to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }

    // Push new element to s1
    push(&q->s1, value);

    // Move everything back to s1 from s2
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }

    printf("Enqueued: %d\n", value);
}

// Cheap dequeue operation
void dequeue(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is Empty\n");
        return;
    }
    int removed = pop(&q->s1);
    printf("Dequeued: %d\n", removed);
}

// Display queue
void display(struct Queue* q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is Empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i <= q->s1.top; i++) {
        printf("%d ", q->s1.arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    struct Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);

    dequeue(&q);
    display(&q);

    enqueue(&q, 40);
    display(&q);

    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);  // Underflow test

    return 0;
}
