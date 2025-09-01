#include <stdio.h>
#include <stdlib.h>

// Define node structure for linked list (used in buckets)
struct Node {
    int data;
    struct Node* next;
};

// Hash function to map values into buckets
int hash_function(int value, int max_value, int num_buckets) {
    return (int)(((double)value / max_value) * num_buckets);
}

// Insert an element into the bucket in sorted order
void insert_into_bucket(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL || data < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL && current->next->data < data) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Concatenate all buckets back into the array
void concatenate_buckets(struct Node** buckets, int num_buckets, int* arr, int n) {
    int arr_index = 0;
    for (int i = 0; i < num_buckets; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[arr_index++] = current->data;
            struct Node* temp = current;
            current = current->next;
            free(temp); // Free allocated memory
        }
    }
}

// Main sorting function
void address_calculation_sort(int* arr, int n, int num_buckets) {
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Create buckets
    struct Node* buckets[num_buckets];
    for (int i = 0; i < num_buckets; i++) {
        buckets[i] = NULL;
    }

    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int bucket_index = hash_function(arr[i], max_val, num_buckets);
        insert_into_bucket(&buckets[bucket_index], arr[i]);
    }

    // Collect elements back from buckets
    concatenate_buckets(buckets, num_buckets, arr, n);
}

// Driver code
int main() {
    int arr[] = {25, 57, 48, 37, 12, 92, 86, 33};
    int n = sizeof(arr) / sizeof(arr[0]);
    int num_buckets = 10; // Example number of buckets

    printf("Unsorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    address_calculation_sort(arr, n, num_buckets);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
