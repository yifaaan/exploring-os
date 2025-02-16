#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void fcfs_scheduling(Process processes[], int n)
{
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;

    for (int i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }

    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++)
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void fcfs_scheduling_sorted(Process processes[], int n)
{
    int current_time = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate waiting and turnaround times
    for (int i = 0; i < n; i++)
    {
        if (current_time < processes[i].arrival_time)
        {
            current_time = processes[i].arrival_time;
        }

        // Calculate waiting time
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        // Update current time
        current_time += processes[i].burst_time;
        // Calculate turnaround time
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        // Update total times
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Print results
    printf("FCFS Scheduling Results:\n");
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main()
{
    Process processes[] = {{1, 0, 10}, // Process ID, Arrival Time, Burst Time
        {2, 1, 5}, {3, 3, 8}};
    int n = sizeof(processes) / sizeof(processes[0]);

    fcfs_scheduling(processes, n);
    fcfs_scheduling_sorted(processes, n);
    return 0;
}
