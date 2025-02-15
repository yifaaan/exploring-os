#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child process: PID = %d\n", getpid());
        printf("Child process: Parent PID = %d\n", getppid());
        char* args[] = {"ls", "-al", NULL};
        execvp("ls", args);
        perror("execvp");
        exit(1);
    }
    else
    {
        printf("Parent process: PID = %d\n", getpid());
        printf("Parent process: Child PID = %d\n", pid);
        wait(NULL);
        printf("Parent process: Child process completed\n");
    }
    return 0;
}