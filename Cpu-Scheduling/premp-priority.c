#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int priority; // Added for Priority Scheduling
} Process;

// Function to implement Preemptive Priority Scheduling
void preemptivePriority(Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Array to keep track of remaining burst times
    int remainingBurst[n];
    for (int i = 0; i < n; i++) {
        remainingBurst[i] = processes[i].burstTime;
        processes[i].waitingTime = 0; // Initialize waiting time
        processes[i].turnaroundTime = 0; // Initialize turnaround time
    }

    int time = 0;
    int completed = 0;

    // To store the order of execution for Gantt Chart
    int ganttChart[100]; // Assuming max 100 time units for simplicity
    int ganttIndex = 0;

    while (completed < n) {
        // Find the process with the highest priority that has arrived
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && remainingBurst[i] > 0) {
                if (idx == -1 || processes[i].priority < processes[idx].priority) {
                    idx = i; // Select process with highest priority
                }
            }
        }

        if (idx != -1) { // If a process is found to execute
            ganttChart[ganttIndex++] = processes[idx].pid; // Record the process in Gantt chart
            remainingBurst[idx]--; // Execute for one time unit

            // If a process is completed
            if (remainingBurst[idx] == 0) {
                completed++;
                processes[idx].turnaroundTime = time + 1 - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                totalWaitingTime += processes[idx].waitingTime;
                totalTurnaroundTime += processes[idx].turnaroundTime;
            }
        }

        time++; // Increment time
    }

    printf("\nPreemptive Priority Scheduling Algorithm:\n");
    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].priority, 
               processes[i].waitingTime, 
               processes[i].turnaroundTime);
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    
    for (int i = 0; i < ganttIndex; i++) {
        printf("| P%d ", ganttChart[i]);
    }
    
    printf("|\n");

    // Print time intervals
    printf("0 ");
    for (int i = 1; i <= ganttIndex; i++) {
        printf("%d ", i); // Print end times for each process in Gantt chart
    }
    
    printf("\n");
}

// Main function to run the scheduling algorithms
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = malloc(n * sizeof(Process));
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].pid = i + 1;
    }

   preemptivePriority(processes, n);

   free(processes); // Free allocated memory

   return 0;
}
