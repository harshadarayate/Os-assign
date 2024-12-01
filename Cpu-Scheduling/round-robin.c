#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int at[], int wt[], int quantum, int gantt[], int *ganttIndex)
{
    int remaining_bt[n]; // Remaining burst time for each process
    for (int i = 0; i < n; i++)
    {
        remaining_bt[i] = bt[i];
        wt[i] = 0; // Initialize waiting time
    }

    int t = 0; // Current time
    while (1)
    {
        int done = 1; // Flag to check if all processes are done
        for (int i = 0; i < n; i++)
        {
            if (remaining_bt[i] > 0) // If process is not finished
            {
                done = 0; // There is a pending process
                if (remaining_bt[i] > quantum)
                {
                    gantt[(*ganttIndex)++] = processes[i]; // Record process in Gantt chart
                    t += quantum;               // Increase current time by quantum
                    remaining_bt[i] -= quantum; // Decrease remaining burst time
                }
                else
                {
                    gantt[(*ganttIndex)++] = processes[i]; // Record process in Gantt chart
                    t += remaining_bt[i];       // Increase current time by remaining burst time
                    wt[i] += t - bt[i] - at[i]; // Calculate waiting time
                    remaining_bt[i] = 0;        // Process finished
                }
            }
        }
        if (done)
            break; // Break if all processes are done
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i]; // TAT = BT + WT
    }
}

void printResults(int processes[], int n, int bt[], int at[], int wt[], int tat[], int gantt[], int ganttIndex)
{
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i],
               bt[i],
               at[i],
               wt[i],
               tat[i]);
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    
    printf(" | ");
    
    for (int i = 0; i < ganttIndex; i++) {
        printf("P%d |", gantt[i]);
    }

    printf("\n");

    // Print time line under Gantt Chart
    printf("0");
    
    for (int i = 1; i <= ganttIndex; i++) {
        printf("\t%d", (i * 2)); // Assuming each quantum unit is represented as '2' for simplicity.
    }

    printf("\n");
}

int main()
{
    int n;

    // User input for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n], waiting_time[n], turnaround_time[n];
    
    // Array to store the Gantt chart order
    int gantt[100]; 
    int ganttIndex = 0;

    // User input for burst times and arrival times
    printf("Enter Burst Time and Arrival Time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1; // Process ID starting from 1
        printf("Process %d:\n", processes[i]);
        printf("Burst time: ");
        scanf("%d", &burst_time[i]);
        printf("Arrival time: ");
        scanf("%d", &arrival_time[i]);
    }

    int quantum;
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    // Calculate waiting time and turnaround time
    findWaitingTime(processes, n, burst_time, arrival_time, waiting_time, quantum, gantt, &ganttIndex);
    findTurnAroundTime(processes, n, burst_time, waiting_time, turnaround_time);

    // Print results including Gantt Chart
    printResults(processes, n, burst_time, arrival_time, waiting_time, turnaround_time, gantt, ganttIndex);

    return 0;
}
