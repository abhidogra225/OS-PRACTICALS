
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
// Structure to hold process information
struct Process
{
  int process_id;      // Process ID
  int arrival_time;    // Arrival time
  int burst_time;      // Burst time
  int completion_time; // Completion time
  int turnaround_time; // Turnaround time
  int waiting_time;    // Waiting time
  int remaining_time;  // Remaining burst time for preemption
  int is_completed;    // Flag to check if process is completed
};

// SJF schedulig (Preemptive)
void srtf_schedule(struct Process proc[], int n)
{
  int rt[n];
  int arr[1000];        // To store the order of execution
  int gantt_time[1000]; // To store the time at each switch
  int exec_idx = 0;     // Index to track gantt chart entries
  // Copy the burst time into rt[]
  for (int i = 0; i < n; i++)
    rt[i] = proc[i].burst_time;
  int complete = 0, t = 0, minm = INT_MAX;
  int shortest = 0, finish_time;
  int check = 0;
  // Process until all processes get completed
  while (complete != n)
  {
    // Find process with minimum remaining time among the processes
    // that arrive till the current time
    for (int j = 0; j < n; j++)
    {
      if ((proc[j].arrival_time <= t) &&
          (rt[j] < minm) && rt[j] > 0)
      {
        minm = rt[j];
        shortest = j;
        check = 1;
      }
    }
    if (check == 0)
    {
      t++;
      continue;
    }
    // Track the process execution in Gantt chart
    arr[exec_idx] = proc[shortest].process_id;
    gantt_time[exec_idx] = t;
    exec_idx++;
    // Reduce remaining time by one
    rt[shortest]--;
    // Update minimum
    minm = rt[shortest];
    if (minm == 0)
      minm = INT_MAX;
    // If a process gets completely executed
    if (rt[shortest] == 0)
    {
      complete++;
      check = 0;
      // Find finish time of current process
      finish_time = t + 1;
      // Calculate waiting time
      proc[shortest].waiting_time = finish_time -
                                    proc[shortest].burst_time - proc[shortest].arrival_time;
      if (proc[shortest].waiting_time < 0)
        proc[shortest].waiting_time = 0;
      // Calculate turnaround time
      proc[shortest].turnaround_time = proc[shortest].burst_time +
                                       proc[shortest].waiting_time;
      // Store the completion time
      proc[shortest].completion_time = finish_time;
    }
    // Increment time
    t++;
  }
  // Calculate total waiting time and turnaround time
  double total_waiting_time = 0, total_turnaround_time = 0;
  for (int i = 0; i < n; ++i)
  {
    total_waiting_time += proc[i].waiting_time;
    total_turnaround_time += proc[i].turnaround_time;
  }
  // Print average waiting time and average turnaround time
  printf("Average Waiting Time: %f\n", total_waiting_time / n);
  printf("Average Turnaround Time: %f\n", total_turnaround_time / n);
  // Print Gantt chart for SRTF
  printf("\nGantt chart: \n\n");
  for (int i = 0; i < exec_idx; i++)
  {
    if (i == 0 || arr[i] != arr[i - 1])
    {
      printf("| P%d ", arr[i]);
    }
  }
  printf("|\n");
  for (int i = 0; i < exec_idx; i++)
  {
    if (i == 0 || arr[i] != arr[i - 1])
    {
      printf("%d ", gantt_time[i]);
    }
  }
  printf("%d\n\n", t);
}
int main()
{
  int n;
  
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  struct Process processes[n];
  // Input process details
  for (int i = 0; i < n; ++i)
  {
    processes[i].process_id = i + 1;
    printf("Enter arrival time and burst time for process %d: ", i +
                                                                     1);
    scanf("%d %d", &processes[i].arrival_time,
          &processes[i].burst_time);
    processes[i].is_completed = 0;
    processes[i].remaining_time = processes[i].burst_time; //
    // Initialize remaining time for SRTF
  }
  printf("Choose the scheduling algorithm:\n");
  
  printf("1. Shortest Remaining Time First (Preemptive)\n");
  
  // Perform the chosen scheduling algorithm
  
 
  
    srtf_schedule(processes, n);
  
  
  // Display process details along with completion time
  printf("Process-ID\tArrival-Time\tBurst-Time\tTurnaround-Time\tWaiting-Time\n");
  for (int i = 0; i < n; ++i)
  {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
           processes[i].process_id,
           processes[i].arrival_time,
           processes[i].burst_time,
           processes[i].turnaround_time,
           processes[i].waiting_time);
  }
  return 0;
}