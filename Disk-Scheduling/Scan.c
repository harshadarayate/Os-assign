#include <stdio.h>
#include <stdlib.h> // For abs()

void scanDiskScheduling(int requests[], int n, int head, int diskSize, char direction) {
    int totalSeekTime = 0, currentPosition = head;
    int serviced[n], sequence[n + 2], seqCount = 0;

    // Initialize all requests as not serviced
    for (int i = 0; i < n; i++) {
        serviced[i] = 0;
    }

    // Sort the requests for proper SCAN traversal
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

    // SCAN movement
    if (direction == 'r') { // Towards the end of the disk (right)
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                sequence[seqCount++] = requests[i];
                serviced[i] = 1;
            }
        }
        sequence[seqCount++] = diskSize - 1; // Add the end of the disk
        for (int i = n - 1; i >= 0; i--) {
            if (!serviced[i]) {
                sequence[seqCount++] = requests[i];
            }
        }
    } else { // Towards the start of the disk (left)
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                sequence[seqCount++] = requests[i];
                serviced[i] = 1;
            }
        }
        sequence[seqCount++] = 0; // Add the start of the disk
        for (int i = 0; i < n; i++) {
            if (!serviced[i]) {
                sequence[seqCount++] = requests[i];
            }
        }
    }

    // Calculate total seek time and print sequence
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
    char direction;

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

    printf("Enter the initial direction of head movement (l for left, r for right): ");
    scanf(" %c", &direction); // Note the space before %c to consume any whitespace

    scanDiskScheduling(requests, n, head, diskSize, direction);

    return 0;
}
