#include <limits.h>
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

void sjf_scheduling(Process processes[], int n)
{
    int current_time = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    int completed = 0;
    int remaining_time[MAX_PROCESSES];

    // Initialize remaining time array
    for (int i = 0; i < n; i++)
    {
        remaining_time[i] = processes[i].burst_time;
    }

    while (completed != n)
    {
        // Find the process with the shortest burst time that has arrived
        int shortest_job = -1;
        int min_burst_time = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && remaining_time[i] < min_burst_time && remaining_time[i] > 0)
            {
                min_burst_time = remaining_time[i];
                shortest_job = i;
            }
        }

        if (shortest_job == -1)
        {
            current_time++;
            continue;
        }

        // Execute the shortest job
        remaining_time[shortest_job]--;

        // If the process is completed
        if (remaining_time[shortest_job] == 0)
        {
            completed++;
            int finish_time = current_time + 1;
            processes[shortest_job].waiting_time = finish_time - processes[shortest_job].burst_time - processes[shortest_job].arrival_time;
            processes[shortest_job].turnaround_time = finish_time - processes[shortest_job].arrival_time;

            total_waiting_time += processes[shortest_job].waiting_time;
            total_turnaround_time += processes[shortest_job].turnaround_time;
        }
        current_time++;
    }

    // Print results
    printf("SJF Scheduling Results:\n");
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

    sjf_scheduling(processes, n);
    return 0;
}
