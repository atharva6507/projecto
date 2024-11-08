#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>  // Added for `wait()`
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void callbubble(int array[15], int n);  // Added function declaration

int main()
{
    int i, a[15], n;
    char *arg[10], str[15], str2[15];  // Changed str2 to an array instead of pointer
    pid_t parent_id, child_id, id;

    printf("\nEnter the size of the input array: ");
    scanf("%d", &n);

    printf("\nEnter the elements of the input array: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    parent_id = getpid();
    printf("\n\nIn parent id -> %d\n", parent_id);

    printf("\n\nSorting Numbers\n");
    callbubble(a, n);

    id = fork();
    if (id == 0) {
        // Child process
        child_id = getpid();
        printf("\n\nIn child id -> %d\n", child_id);
        printf("\n\nThe Sorted Numbers are: ");
        for (i = 0; i < n; i++) {
            sprintf(str, "%d", a[i]);
            arg[i] = malloc(sizeof(str));
            strcpy(arg[i], str);
        }
        arg[i] = NULL;  // NULL-terminate the argument list

        printf("\nEnter String: ");
        scanf("%s", str2);

        printf("\n\nExecuting execve Statement\n");
        execve("./2b2", arg, NULL);  // Pass `arg` instead of `str2` for the arguments
        printf("\n\nexecve Completed\n");
        printf("\n\nChild Complete. Now Child Exits\n\n");
    }
    else if (id > 0) {
        // Parent process
        printf("\n\nIn Parent\n\nNow Waiting\n\n");
        wait(NULL);
        printf("\n\nParent Complete. Now Parent Exits\n\n");
    }

    return 0;
}

void callbubble(int array[15], int n)
{
    int d, swap, c;
    for (c = 0; c < (n - 1); c++) {
        for (d = 0; d < n - c - 1; d++) {
            if (array[d] > array[d + 1]) {  // For decreasing order use <
                swap = array[d];
                array[d] = array[d + 1];
                array[d + 1] = swap;
            }
        }
    }
}
