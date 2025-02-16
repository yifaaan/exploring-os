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
    int priority;
} Process;

void priority_scheduling(Process processes[], int n)
{
    int current_time = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    int completed = 0;

    while (completed != n)
    {
        // Find the process with the shortest burst time that has arrived
        int selected_process = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].priority < highest_priority && processes[i].burst_time > 0)
            {
                highest_priority = processes[i].priority;
                selected_process = i;
            }
        }

        if (selected_process == -1)
        {
            current_time++;
            continue;
        }

        // Execute the selected process
        processes[selected_process].burst_time--;

        // If the process is completed
        if (processes[selected_process].burst_time == 0)
        {
            completed++;
            int finish_time = current_time + 1;
            processes[selected_process].waiting_time = finish_time - processes[selected_process].burst_time - processes[selected_process].arrival_time;
            processes[selected_process].turnaround_time = finish_time - processes[selected_process].arrival_time;

            total_waiting_time += processes[selected_process].waiting_time;
            total_turnaround_time += processes[selected_process].turnaround_time;
        }
        current_time++;
    }

    // Print results
    printf("Priority Scheduling Results:\n");
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

    priority_scheduling(processes, n);
    return 0;
}
