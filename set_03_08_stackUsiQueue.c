// #include <stdio.h>
// #include <stdlib.h>

// #define SIZE 100

// struct Queue {
//     int arr[SIZE];
//     int front, rear;
// };

// void initQueue(struct Queue* q) {
//     q->front = q->rear = -1;
// }

// int isEmpty(struct Queue* q) {
//     return q->front == -1;
// }

// void enqueue(struct Queue* q, int value) {
//     if (q->rear == SIZE - 1) {
//         printf("Queue Overflow\n");
//         return;
//     }
//     if (isEmpty(q))
//         q->front = 0;
//     q->arr[++q->rear] = value;
// }

// int dequeue(struct Queue* q) {
//     if (isEmpty(q)) {
//         printf("Queue Underflow\n");
//         return -1;
//     }
//     int val = q->arr[q->front];
//     if (q->front == q->rear)
//         q->front = q->rear = -1;
//     else
//         q->front++;
//     return val;
// }

// void copyQueue(struct Queue* dest, struct Queue* src) {
//     while (!isEmpty(src)) {
//         enqueue(dest, dequeue(src));
//     }
// }

// void swapQueues(struct Queue* q1, struct Queue* q2) {
//     struct Queue temp = *q1;
//     *q1 = *q2;
//     *q2 = temp;
// }

// // Stack using two queues
// struct Stack {
//     struct Queue q1, q2;
// };

// void initStack(struct Stack* s) {
//     initQueue(&s->q1);
//     initQueue(&s->q2);
// }

// void push(struct Stack* s, int value) {
//     enqueue(&s->q2, value);
//     while (!isEmpty(&s->q1)) {
//         enqueue(&s->q2, dequeue(&s->q1));
//     }
//     swapQueues(&s->q1, &s->q2);
//     printf("Pushed: %d\n", value);
// }

// void pop(struct Stack* s) {
//     if (isEmpty(&s->q1)) {
//         printf("Stack Underflow\n");
//         return;
//     }
//     printf("Popped: %d\n", dequeue(&s->q1));
// }

// void display(struct Stack* s) {
//     if (isEmpty(&s->q1)) {
//         printf("Stack is Empty\n");
//         return;
//     }
//     printf("Stack (top to bottom): ");
//     for (int i = s->q1.front; i <= s->q1.rear; i++) {
//         printf("%d ", s->q1.arr[i]);
//     }
//     printf("\n");
// }

// // MAIN FUNCTION
// int main() {
//     printf("=== Stack Using Two Queues (Costly Enqueue) ===\n");
//     struct Stack s;
//     initStack(&s);

//     push(&s, 10);
//     push(&s, 20);
//     push(&s, 30);
//     display(&s);
//     pop(&s);
//     display(&s);
//     push(&s, 40);
//     display(&s);
//     pop(&s);
//     pop(&s);
//     pop(&s); // underflow
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

struct Queue {
    int arr[SIZE];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == SIZE - 1) {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmpty(q))
        q->front = 0;
    q->arr[++q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

void swapQueues(struct Queue* q1, struct Queue* q2) {
    struct Queue temp = *q1;
    *q1 = *q2;
    *q2 = temp;
}

// Stack using two queues
struct Stack {
    struct Queue q1, q2;
};

void initStack(struct Stack* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void push(struct Stack* s, int value) {
    enqueue(&s->q1, value);
    printf("Pushed: %d\n", value);
}

void pop(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack Underflow\n");
        return;
    }

    // Move all but last
    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    int popped = dequeue(&s->q1);
    printf("Popped: %d\n", popped);

    swapQueues(&s->q1, &s->q2);
}

void display(struct Stack* s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is Empty\n");
        return;
    }
    printf("Stack (bottom to top): ");
    for (int i = s->q1.front; i <= s->q1.rear; i++) {
        printf("%d ", s->q1.arr[i]);
    }
    printf("\n");
}

// MAIN FUNCTION
int main() {
    printf("\n=== Stack Using Two Queues (Costly Dequeue) ===\n");
    struct Stack s;
    initStack(&s);

    push(&s, 100);
    push(&s, 200);
    push(&s, 300);
    display(&s);
    pop(&s);
    display(&s);
    push(&s, 400);
    display(&s);
    pop(&s);
    pop(&s);
    pop(&s); // Underflow
    return 0;
}
