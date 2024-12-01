#include <stdio.h>
#include <stdlib.h> // For abs()

void sstfDiskScheduling(int requests[], int n, int head) {
    int totalSeekTime = 0, completed = 0;
    int visited[n]; // To track processed requests
    int currentPosition = head;

    // Initialize all requests as not visited
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("\nRequest Sequence and Head Movement:\n");
    printf("-------------------------------------------------\n");
    printf("Step\tCurrent Head\tNext Request\tSeek Time\n");
    printf("-------------------------------------------------\n");

    while (completed < n) {
        int shortestDistance = 1e9, nextRequest = -1;

        // Find the nearest unvisited request
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int distance = abs(requests[i] - currentPosition);
                if (distance < shortestDistance) {
                    shortestDistance = distance;
                    nextRequest = i;
                }
            }
        }

        // Process the nearest request
        if (nextRequest != -1) {
            visited[nextRequest] = 1; // Mark as visited
            totalSeekTime += shortestDistance;
            printf("%d\t%d\t\t%d\t\t%d\n", completed + 1, currentPosition, requests[nextRequest], shortestDistance);
            currentPosition = requests[nextRequest];
            completed++;
        }
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

    sstfDiskScheduling(requests, n, head);

    return 0;
}