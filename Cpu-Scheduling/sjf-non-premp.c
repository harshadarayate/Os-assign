#include <stdio.h>

void findCompletionTime(int processes[], int n, int bt[], int at[], int ct[])
{
    ct[0] = at[0] + bt[0]; // Completion time for the first process

    // Calculate completion time for each process
    for (int i = 1; i < n; i++)
    {
        ct[i] = ct[i - 1] + bt[i]; // Start after the previous process finishes
        // Adjust if the next process arrives later than the current completion time
        if (at[i] > ct[i - 1])
        {
            ct[i] = at[i] + bt[i]; // If it arrives after the previous process finishes
        }
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int ct[], int tat[], int at[])
{
    // Calculate turnaround time as sum of burst time and waiting time
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i]; // TAT = CT - AT
    }
}

void findWaitingTime(int processes[], int n, int bt[], int ct[], int wt[], int tat[])
{
    // Calculate waiting time as turnaround time minus burst time
    for (int i = 0; i < n; i++)
    {
        wt[i] = tat[i] - bt[i]; // WT = TAT - BT
    }
}

void findavgTime(int processes[], int n, int bt[], int at[])
{
    int ct[n], tat[n], wt[n];

    // Calculate completion time
    findCompletionTime(processes, n, bt, at, ct);

    // Calculate turnaround time
    findTurnAroundTime(processes, n, bt, ct, tat, at);

    // Calculate waiting time
    findWaitingTime(processes, n, bt, ct, wt, tat);

    // Calculate total waiting time and turnaround time
    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], at[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

void printGanttChart(int processes[], int n, int ct[])
{
    printf("\nGantt Chart:\n");

    printf(" | ");

    for (int i = 0; i < n; i++)
    {
        printf("P%d | ", processes[i]);
    }

    printf("\n");

    // Print timeline under Gantt Chart
    printf("0");

    for (int i = 0; i < n; i++)
    {
        printf("\t%d", ct[i]);
    }

    printf("\n");
}

// Function to sort processes according to arrival time and burst time
void sortProcesses(int processes[], int n, int bt[], int at[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1] || (at[j] == at[j + 1] && bt[j] > bt[j + 1]))
            {
                // Swap burst times
                int temp_bt = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp_bt;

                // Swap arrival times accordingly
                int temp_at = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp_at;

                // Swap process IDs accordingly
                int temp_pid = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp_pid;
            }
        }
    }
}

int main()
{
    int n;

    // User input for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];

    // User input for burst times and arrival times
    printf("Enter burst times and arrival times for each process:\n");
    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1; // Process numbers start from 1
        printf("Process %d:\n", processes[i]);
        printf("Burst time: ");
        scanf("%d", &burst_time[i]);
        printf("Arrival time: ");
        scanf("%d", &arrival_time[i]);
    }

    // Sort processes based on arrival time and burst time
    sortProcesses(processes, n, burst_time, arrival_time);

    // Calculate and display average times
    findavgTime(processes, n, burst_time, arrival_time);

    // Print Gantt Chart
    printGanttChart(processes, n, arrival_time);

    return 0;
}
