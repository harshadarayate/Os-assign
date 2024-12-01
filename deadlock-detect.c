
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max_demand[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int num_processes, num_resources;
int i, j;

void input() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter allocation matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter maximum demand matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &max_demand[i][j]);
        }
    }

    printf("Enter available resources:\n");
    for (j = 0; j < num_resources; j++) {
        scanf("%d", &available[j]);
    }

    // Calculate the Need matrix
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            need[i][j] = max_demand[i][j] - allocation[i][j];
        }
    }
}

void print_matrices() {
    printf("\n--- Allocation, Maximum Demand, and Need Matrices ---\n");
    printf("Process\t\tAllocation\tMaximum Demand\tNeed\n");
    printf("-------------------------------------------------------------\n");
    for (i = 0; i < num_processes; i++) {
        printf("P%d\t\t", i);
        for (j = 0; j < num_resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < num_resources; j++) {
            printf("%d ", max_demand[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("\n--- Available Resources ---\n");
    printf("Resources: ");
    for (j = 0; j < num_resources; j++) {
        printf("%d ", available[j]);
    }
    printf("\n");
}

bool find_safe_sequence() {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    int safe_sequence[MAX_PROCESSES];
    int index = 0;

    // Initialize work as available resources
    for (j = 0; j < num_resources; j++) {
        work[j] = available[j];
    }

    int count = 0;

    while (count < num_processes) {
        bool found = false;

        for (i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_finish = true;

                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_finish = false;
                        break;
                    }
                }

                if (can_finish) {
                    for (j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safe_sequence[index++] = i; // Add process to safe sequence
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            printf("\nDeadlock detected!\n");
            return false; // No safe sequence found
        }
    }

    // Print the safe sequence
    printf("\nSafe Sequence: ");
    for (i = 0; i < num_processes; i++) {
        printf("P%d", safe_sequence[i]);
        if (i < num_processes - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    return true; // Safe sequence exists
}

int main() {
    input();
    print_matrices();

    if (!find_safe_sequence()) {
        printf("System is in an unsafe state.\n");
    } else {
        printf("System is in a safe state.\n");
    }

    return 0;
}