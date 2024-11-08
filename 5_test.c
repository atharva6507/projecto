#include <stdio.h>

#define MAX_PR 5
#define RESOURCE 3

int main(){
    int n = MAX_PR;
    int A, B, C;

    printf("Enter the Available Total Resources (A B C): ");
    scanf("%d %d %d", &A, &B, &C);

    int alloc[MAX_PR][RESOURCE] = {0};
    printf("Enter allocated resources for each Process\n");
    for(int i = 0; i < n; i++){
        printf("Enter allocated resources for P%d\n", i+1);
        for(int j = 0; j < RESOURCE; j++){
            scanf("%d", &alloc[i][j]);
        }
    }

    int maxreq[MAX_PR][RESOURCE] = {0};
    printf("Enter maximum required resources for each Process\n");
    for(int i = 0; i < n; i++){
        printf("Enter required resources for P%d: ", i+1);
        for(int j = 0; j < RESOURCE; j++){
            scanf("%d", &maxreq[i][j]);
        }
    }

    printf("Enter currently available resources of each type (A B C): \n");
    int avla, avlb, avlc;
    scanf("%d %d %d", &avla, &avlb, &avlc);

    int required[MAX_PR][RESOURCE] = {0};
    for(int i = 0; i < MAX_PR; i++){
        for(int j = 0; j < RESOURCE; j++){
            required[i][j] = maxreq[i][j] - alloc[i][j];
        }
    }

    printf("\nAllocation Matrix:\nP\tA\tB\tC\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i + 1);
        for (int j = 0; j < RESOURCE; j++) {
            printf("%d\t", alloc[i][j]);
        }
        printf("\n");
    }

    printf("Maximum Resource Requirement Matrix:\nP\tA\tB\tC\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i + 1);
        for (int j = 0; j < RESOURCE; j++) {
            printf("%d\t", maxreq[i][j]);
        }
        printf("\n");
    }

    printf("Remaining Requirement Matrix:\nP\tA\tB\tC\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i + 1);
        for (int j = 0; j < RESOURCE; j++) {
            printf("%d\t", required[i][j]);
        }
        printf("\n");
    }

    int completed = 0;
    int processes[MAX_PR] = {0};
    int found;

    while(completed != n){
        found = 0;
        for(int i = 0; i < n; i++){
            if((required[i][0] <= avla && required[i][0] != -1) && 
               (required[i][1] <= avlb && required[i][1] != -1) && 
               (required[i][2] <= avlc && required[i][2] != -1)){
                completed++;
                processes[completed-1] = i + 1;
                avla += alloc[i][0];
                avlb += alloc[i][1];
                avlc += alloc[i][2];

                for(int j = 0; j < RESOURCE; j++){
                    required[i][j] = -1;
                }
                found = 1;
            }
        }

        if (!found) {
            printf("The system is in an unsafe state.\n");
            return -1;
        }
    }

    printf("The system is in a safe state.\n");
    printf("Process Sequence is: \n");
    for(int i = 0; i < n; i++){
        printf("P%d->", processes[i]);
    }
    printf("\n");

    printf("Current Available Resources:\nA - %d, B - %d, C - %d\n", avla, avlb, avlc);

    return 0;
}