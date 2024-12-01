#include <stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int fragment[m];

    // Initialize all allocations to -1 (unallocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Perform allocation for each process
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        // Allocate the process to the worst-fitting block
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    // Display the allocation result
    printf("\nProcess No.\tProcess Size\tBlock No.\tFragment\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            fragment[allocation[i]] = blockSize[allocation[i]];
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1, fragment[allocation[i]]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\t-\n", i + 1, processSize[i]);
        }
    }
    printf("---------------------------------------------------------\n");
}

int main() {
    int m, n;

    printf("Enter the number of blocks: ");
    scanf("%d", &m);

    int blockSize[m];
    printf("Enter the sizes of the blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processSize[n];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    worstFit(blockSize, m, processSize, n);

    return 0;
}