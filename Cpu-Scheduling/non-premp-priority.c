#include <stdio.h>

struct Process {
    int id;         // Process ID
    int bt;        // Burst Time
    int at;        // Arrival Time
    int priority;  // Priority
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
};

// Function to sort processes based on arrival time and priority
void sortProcesses(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].at > proc[j + 1].at || 
                (proc[j].at == proc[j + 1].at && proc[j].priority > proc[j + 1].priority)) {
                // Swap processes
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

// Function to calculate completion time, turnaround time, and waiting time
void calculateTimes(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            proc[i].ct = proc[i].at + proc[i].bt;
        } else {
            // Check if the CPU is idle until the next process arrives
            if (proc[i].at > proc[i - 1].ct) {
                proc[i].ct = proc[i].at + proc[i].bt;
            } else {
                proc[i].ct = proc[i - 1].ct + proc[i].bt;
            }
        }
        proc[i].tat = proc[i].ct - proc[i].at; // TAT = CT - AT
        proc[i].wt = proc[i].tat - proc[i].bt; // WT = TAT - BT
    }
}

// Function to print the results and Gantt Chart
void printResults(struct Process proc[], int n) {
    printf("\nProcess\tBurst Time\tArrival Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].id, 
               proc[i].bt, 
               proc[i].at, 
               proc[i].priority, 
               proc[i].ct, 
               proc[i].tat, 
               proc[i].wt);
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    
    int current_time = 0;
    
    printf(" | ");
    
    for (int i = 0; i < n; i++) {
        if (proc[i].at <= current_time) { // Only consider processes that have arrived
            printf("P%d ", proc[i].id);
            current_time += proc[i].bt;
            printf("| ");
        } else {
            // If the next process has not arrived yet, idle time is represented by a gap.
            printf("Idle ");
            printf("| ");
            current_time = proc[i].at; // Move current time to the next arriving process
            printf("P%d ", proc[i].id);
            current_time += proc[i].bt;
            printf("| ");
        }
    }

    printf("\n");
    
    // Print time line under Gantt Chart
    current_time = 0;
    printf("0");

    for (int i = 0; i < n; i++) {
        if (proc[i].at <= current_time) { // Only consider processes that have arrived
            current_time += proc[i].bt;
            printf("\t%d", current_time);
        } else {
            current_time = proc[i].at + proc[i].bt; // Move current time to the next arriving process
            printf("\t%d", current_time);
        }
    }
    
    printf("\n");
}

int main() {
    int n;

    // User input for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // User input for burst times, arrival times, and priorities
    printf("Enter Burst Time, Arrival Time and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &proc[i].at);
        printf("Burst time: ");
        scanf("%d", &proc[i].bt);
        
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
        proc[i].id = i + 1; // Assigning process ID starting from 1
    }

    // Sort processes based on arrival time and priority
    sortProcesses(proc, n);

    // Calculate completion time, turnaround time, and waiting time
    calculateTimes(proc, n);

    // Print results including Gantt Chart
    printResults(proc, n);

    return 0;
}
