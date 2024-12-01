#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

// Function to implement First Come First Served (FCFS) scheduling algorithm
void fcfs(Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            processes[i].waitingTime = 0;
            processes[i].turnaroundTime = processes[i].burstTime;
        } else {
            processes[i].waitingTime = processes[i - 1].turnaroundTime;
            processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        }

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nFCFS Scheduling Algorithm:\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].pid);
    }
    printf("|\n");

    // Print time intervals
    printf("0 ");
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf(" %d ", processes[i].turnaroundTime);
        } else {
            printf(" %d ", processes[i - 1].turnaroundTime + processes[i].burstTime);
        }
    }
    printf("\n");
}

// Function to implement Round Robin scheduling algorithm
void roundRobin(Process processes[], int n, int timeSlice) {
    int remainingBurst[n];
    for (int i = 0; i < n; i++) {
        remainingBurst[i] = processes[i].burstTime;
        processes[i].waitingTime = 0; // Initialize waiting time
        processes[i].turnaroundTime = 0; // Initialize turnaround time
    }

    int time = 0;
    while (1) {
        int done = 1; // Check if all processes are done
        for (int i = 0; i < n; i++) {
            if (remainingBurst[i] > 0) { // If process is not finished
                done = 0; // There is at least one process that is not done
                if (remainingBurst[i] > timeSlice) {
                    time += timeSlice;
                    remainingBurst[i] -= timeSlice;
                } else { // Process can finish in this time slice
                    time += remainingBurst[i];
                    processes[i].waitingTime = time - processes[i].burstTime - processes[i].arrivalTime;
                    remainingBurst[i] = 0;
                }
            }
        }
        if (done == 1) break; // Exit if all processes are done
    }

    // Calculate turnaround times and total waiting times
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    // Calculate averages
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nRound Robin Scheduling Algorithm:\n");
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].waitingTime, 
               processes[i].turnaroundTime);
    }
    
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");
    
    for (int i = 0; i < n; i++) {
        if (remainingBurst[i] > 0) { // Print only if the process was executed
            printf("| P%d ", processes[i].pid);
        }
        
        // Print time intervals
        if (i == n - 1) { // Last process in the round robin
            printf("%d ", time);
        } else {
            printf("%d ", time + timeSlice); // Increment by time slice for each process
            time += timeSlice;
        }
        
        remainingBurst[(i + 1) % n] -= timeSlice; // Decrement burst time of next process
        if(remainingBurst[(i + 1) % n] <= 0)
            remainingBurst[(i + 1) % n] = 0; // Ensure it doesn't go below zero
     } 
     printf("|\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = malloc(n * sizeof(Process));
    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].pid = i + 1;
    }

   fcfs(processes, n);
   //roundRobin(processes, n, 4);

   free(processes); // Free allocated memory

   return 0;
}
