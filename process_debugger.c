#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH 1024
#define MAX_LINE 256

typedef struct
{
    pid_t pid;
    char state;
    unsigned long vm_size;
    unsigned long vm_rss;
    unsigned long threads;
    char name[MAX_LINE];
} ProcessInfo;

/// Fn to read process info from /proc
void read_process_info(pid_t pid, ProcessInfo* info)
{
    char path[MAX_PATH];
    char line[MAX_LINE];
    FILE* fp;

    // Read status file
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    fp = fopen(path, "r");
    if (!fp)
        return;

    info->pid = pid;
    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "State:", 6) == 0)
        {
            info->state = line[7];
        }
        else if (strncmp(line, "VmSize:", 7) == 0)
        {
            sscanf(line, "VmSize: %lu", &info->vm_size);
        }
        else if (strncmp(line, "VmRss:", 6) == 0)
        {
            sscanf(line, "VmRss: %lu", &info->vm_rss);
        }
        else if (strncmp(line, "Threads:", 8) == 0)
        {
            sscanf(line, "Threads: %lu", &info->threads);
        }
        else if (strncmp(line, "Name:", 5) == 0)
        {
            sscanf(line, "Name: %s", info->name);
        }
    }
    fclose(fp);
}

// Fn to print process state info
void print_process_info(ProcessInfo* info)
{
    printf("PID: %d\n", info->pid);
    printf("Name: %s\n", info->name);
    printf("State: %c (", info->state);

    switch (info->state)
    {
    case 'R':
        printf("Running");
        break;
    case 'S':
        printf("Sleeping");
        break;
    case 'D':
        printf("Disk Sleep");
        break;
    case 'Z':
        printf("Zombie");
        break;
    case 'T':
        printf("Stopped");
        break;
    default:
        printf("Unknown");
    }
    printf(")\n");

    printf("Virtual Memory: %lu KB\n", info->vm_size);
    printf("RSS: %lu KB\n", info->vm_rss);
    printf("Threads: %lu\n", info->threads);
    printf("------------------------\n");
}

/// Fn to scan all processes
void scan_processes()
{
    DIR* proc_dir;
    struct dirent* entry;
    ProcessInfo info;

    proc_dir = opendir("/proc");
    if (!proc_dir)
    {
        perror("Cannot open /proc");
        return;
    }

    printf("Scanning all processes...\n");

    while ((entry = readdir(proc_dir)))
    {
        if (entry->d_type == DT_DIR)
        {
            char* endptr;
            pid_t pid = strtol(entry->d_name, &endptr, 10);
            if (*endptr == '\0')
            {
                memset(&info, 0, sizeof(ProcessInfo));
                read_process_info(pid, &info);
                print_process_info(&info);
            }
        }
    }

    closedir(proc_dir);
}

int main()
{
    scan_processes();
    return 0;
}