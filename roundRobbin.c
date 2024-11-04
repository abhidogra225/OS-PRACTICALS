#include <stdio.h>

struct Process {
    int pid;             // Process ID
    int burst_time;      // Burst time
    int arrival_time;    // Arrival time
    int remaining_time;  // Remaining burst time
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
    int completion_time; // Completion time
};

void findAvgTime(struct Process proc[], int n, int quantum) {
    int current_time = 0;  // Current time in the scheduler
    int completed = 0;     // Count of completed processes
    int wait_time = 0;     // Total waiting time
    int turn_time = 0;     // Total turnaround time

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    // Process scheduling loop
    while (completed < n) {
        int process_done = 1;

        for (int i = 0; i < n; i++) {
            // Only process those that have arrived and still have remaining time
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {
                process_done = 0; // There is at least one process that needs to be processed

                if (proc[i].remaining_time > quantum) {
                    // Process runs for time quantum
                    current_time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    // Process completes
                    current_time += proc[i].remaining_time;
                    proc[i].completion_time = current_time;
                    proc[i].waiting_time = current_time - proc[i].arrival_time - proc[i].burst_time;
                    proc[i].turnaround_time = current_time - proc[i].arrival_time;
                    proc[i].remaining_time = 0;
                    completed++;
                }
            }
        }

        // If no process is available to execute, increment time
        if (process_done) {
            current_time++;
        }
    }

    // Calculate total waiting and turnaround times, and display process info
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        wait_time += proc[i].waiting_time;
        turn_time += proc[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time, proc[i].completion_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turn_time / n);
}

int main() {
    int n, quantum;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input details for each process
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    // Find and display the average times and scheduling information
    findAvgTime(proc, n, quantum);

    return 0;
}
