#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function to check if the system is in a safe state
bool is_safe(int processes[], int avail[], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES], int n, int m)
{
    int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0};
    int safe_seq[MAX_PROCESSES], index = 0; // Array to store safe sequence of processes

    // Initialize work with available resources
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    // Try to find a safe sequence
    for (int count = 0; count < n; count++)
    {
        bool found = false; // Flag to check if any process can proceed in this iteration

        for (int p = 0; p < n; p++)
        { // Iterate through all processes
            if (!finish[p])
            {
                bool can_allocate = true; // Assume allocation is possible

                // Check if all needed resources are available
                for (int j = 0; j < m; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate)
                { // If allocation is possible
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += alloc[p][k]; // Simulate resource allocation by updating work array
                    }

                    // Display recently allocated resources
                    printf("Allocating resources for Process P%d: ", p);
                    for (int k = 0; k < m; k++)
                    {
                        printf("%d ", alloc[p][k]);
                    }
                    printf("\n");

                    safe_seq[index++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (!found)
        { // If no process could proceed, not in safe state
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safe_seq[i]);
    printf("\n");
    return true;
}

int main()
{
    int n, m;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int processes[MAX_PROCESSES], avail[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES], alloc[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];

    // Input processes
    for (int i = 0; i < n; i++)
        processes[i] = i;

    // Input available resources
    printf("Enter available resources: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Input maximum demand matrix
    printf("Enter maximum demand matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Calculate need matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Check if the system is in a safe state
    is_safe(processes, avail, max, alloc, need, n, m);

    return 0;
}
