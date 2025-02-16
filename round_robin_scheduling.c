#include <limits.h>
#include <stdio.h>

#define MAX_PROCESSES 10
#define QUANTUM 2

typedef struct
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
} Process;

void round_robin_scheduling(Process processes[], int n, int quantum)
{
    int current_time = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    int completed = 0;

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0)
            {
                int exec_time = (processes[i].remaining_time > quantum) ? quantum : processes[i].remaining_time;
                processes[i].remaining_time -= exec_time;

                current_time += exec_time;

                // If the process is completed
                if (processes[i].remaining_time == 0)
                {
                    completed++;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

                    total_waiting_time += processes[i].waiting_time;
                    total_turnaround_time += processes[i].turnaround_time;
                }
            }
        }
    }

    // Print results
    printf("Round Robin Scheduling Results:\n");
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
    Process processes[] = {{1, 0, 10, 0, 0, 10}, // Process ID, Arrival Time, Burst Time
        {2, 1, 5, 0, 0, 5}, {3, 3, 8, 0, 0, 8}};
    int n = sizeof(processes) / sizeof(processes[0]);

    round_robin_scheduling(processes, n, QUANTUM);
    return 0;
}
