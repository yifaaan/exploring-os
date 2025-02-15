#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/// Process state enumeration
typedef enum
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;

/// PCB
typedef struct
{
    int pid;
    ProcessState state;
    int priority;
} PCB;

/// Fn to simulate state transition
void transition_state(PCB* process, ProcessState new_state)
{
    printf("Transitioning Process %d: %d -> %d\n", process->pid, process->state, new_state);
    process->state = new_state;
}

int main()
{
    PCB process;
    process.pid = getpid();
    process.state = NEW;
    process.priority = 0;

    // Simulating state transitions
    transition_state(&process, READY);
    sleep(1); // Simulate preparation time

    transition_state(&process, RUNNING);
    sleep(2); // Simulate execution

    transition_state(&process, WAITING);
    sleep(1); // Simulate waiting for resource

    transition_state(&process, READY);
    sleep(1);

    transition_state(&process, TERMINATED);
    return 0;
}