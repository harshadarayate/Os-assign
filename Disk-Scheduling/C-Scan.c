#include <stdio.h>
#include <stdlib.h> // For abs()

void cscanDiskScheduling(int requests[], int n, int head, int diskSize) {
    int totalSeekTime = 0, currentPosition = head;
    int sequence[n + 2], seqCount = 0;

    // Sort the requests for proper traversal
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    printf("\nRequest Sequence and Head Movement:\n");
    printf("-------------------------------------------------\n");
    printf("Step\tCurrent Head\tNext Request\tSeek Time\n");
    printf("-------------------------------------------------\n");

    // First service requests greater than the head
    for (int i = 0; i < n; i++) {
        if (requests[i] >= head) {
            sequence[seqCount++] = requests[i];
        }
    }

    // Add the end of the disk
    sequence[seqCount++] = diskSize - 1;

    // Jump to the beginning of the disk
    sequence[seqCount++] = 0;

    // Service the remaining requests
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            sequence[seqCount++] = requests[i];
        }
    }

    // Calculate total seek time and print the sequence
    for (int i = 0; i < seqCount; i++) {
        int seekTime = abs(sequence[i] - currentPosition);
        totalSeekTime += seekTime;
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, currentPosition, sequence[i], seekTime);
        currentPosition = sequence[i];
    }

    printf("-------------------------------------------------\n");
    printf("Total Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float)totalSeekTime / n);
}

int main() {
    int n, head, diskSize;

    printf("Enter the total disk size (number of cylinders): ");
    scanf("%d", &diskSize);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    cscanDiskScheduling(requests, n, head, diskSize);

    return 0;
}