#include <stdio.h>
#include <stdlib.h> // For abs()

void fcfsDiskScheduling(int requests[], int n, int head) {
    int totalSeekTime = 0;
    int currentPosition = head;

    printf("\nRequest Sequence and Head Movement:\n");
    printf("-------------------------------------------------\n");
    printf("Step\tCurrent Head\tNext Request\tSeek Time\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int seekTime = abs(requests[i] - currentPosition); // Calculate seek time
        totalSeekTime += seekTime;
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, currentPosition, requests[i], seekTime);
        currentPosition = requests[i];
    }

    printf("-------------------------------------------------\n");
    printf("Total Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float)totalSeekTime / n);
}

int main() {
    int n, head;

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

    fcfsDiskScheduling(requests, n, head);

    return 0;
}