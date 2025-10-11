#include <stdio.h>
#include <stdlib.h>
struct Job {
    char id;       
    int deadline;  
    int profit;    
};
int compare(const void *a, const void *b) {
    struct Job *job1 = (struct Job *)a;
    struct Job *job2 = (struct Job *)b;
    return (job2->profit - job1->profit); 
}
int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);
    struct Job jobs[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Job ID, Deadline, and Profit for Job %d: ", i + 1);
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }
    qsort(jobs, n, sizeof(struct Job), compare);
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    int slot[maxDeadline];
    for (int i = 0; i < maxDeadline; i++)
        slot[i] = -1;  
    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;     
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }
    printf("\nSelected Jobs: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] != -1)
            printf("%c ", jobs[slot[i]].id);
    }
    printf("\nTotal Profit: %d\n", totalProfit);
    return 0;
}
