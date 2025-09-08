#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure for stack node
struct StackNode {
    struct Node* treeNode;
    struct StackNode* next;
};

// Stack operations
void push(struct StackNode** top_ref, struct Node* t) {
    struct StackNode* new_node = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!new_node) {
        printf("Stack Overflow\n");
        exit(1);
    }
    new_node->treeNode = t;
    new_node->next = (*top_ref);
    (*top_ref) = new_node;
}

int isEmpty(struct StackNode* top) {
    return (top == NULL);
}

struct Node* pop(struct StackNode** top_ref) {
    struct Node* res;
    struct StackNode* top;

    if (isEmpty(*top_ref)) {
        printf("Stack Underflow\n");
        exit(1);
    } else {
        top = *top_ref;
        res = top->treeNode;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

// Function to create a new tree node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Preorder traversal without recursion
void preorder(struct Node* root) {
    if (root == NULL)
        return;

    struct StackNode* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        struct Node* current = pop(&stack);
        printf("%d ", current->data);

        // Push right first so left is processed first
        if (current->right)
            push(&stack, current->right);
        if (current->left)
            push(&stack, current->left);
    }
}

// Sample usage
int main() {
    /*
            1
           / \
          2   3
         / \   \
        4   5   6
    */

    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Preorder traversal (non-recursive): ");
    preorder(root);
    printf("\n");

    return 0;
}
