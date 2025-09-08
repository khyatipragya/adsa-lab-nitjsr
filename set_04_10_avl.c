#include <stdio.h>
#include <stdlib.h>

// Node structure for AVL tree
typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Utility functions
int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

AVLNode* newNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return node;
}

// Right rotate
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor
int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Insert key in AVL tree
AVLNode* insertItem(AVLNode* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else // Equal keys not allowed
        return node;

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Check balance factor
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Find node with minimum key (used in delete)
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a key
AVLNode* deleteItem(AVLNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                // No child
                temp = root;
                root = NULL;
            } else
                *root = *temp; // Copy the contents

            free(temp);
        } else {
            // Node with two children
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Get balance factor
    int balance = getBalance(root);

    // Balance the tree

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search key in AVL tree
AVLNode* searchItem(AVLNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchItem(root->left, key);
    else
        return searchItem(root->right, key);
}

// Delete entire tree
void deleteTree(AVLNode* root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Create an empty AVL Tree
AVLNode* createTree() {
    return NULL;
}

// Inorder traversal (utility)
void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Driver code to test the above functions
int main() {
    AVLNode* root = createTree();

    // Insert nodes
    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 40);
    root = insertItem(root, 50);
    root = insertItem(root, 25);

    printf("Inorder traversal of AVL tree: ");
    inorder(root);
    printf("\n");

    // Search for a key
    int key = 30;
    AVLNode* found = searchItem(root, key);
    if (found != NULL)
        printf("Key %d found in the AVL tree.\n", key);
    else
        printf("Key %d not found in the AVL tree.\n", key);

    // Delete a key
    root = deleteItem(root, 40);
    printf("Inorder traversal after deleting 40: ");
    inorder(root);
    printf("\n");

    // Delete entire tree
    deleteTree(root);
    root = NULL;

    return 0;
}
