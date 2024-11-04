#include <stdio.h>

int main()
{
  int n, m, i, j, k;

  // Take user input for number of processes and resources
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  printf("Enter the number of resources: ");
  scanf("%d", &m);

  int alloc[n][m]; // Allocation Matrix
  int max[n][m];   // Maximum Resource Matrix
  int avail[m];    // Available Resources Array

  // Input allocation matrix
  printf("Enter the allocation matrix:\n");
  for (i = 0; i < n; i++)
  {
    printf("Process %d: ", i);
    for (j = 0; j < m; j++)
    {
      scanf("%d", &alloc[i][j]);
    }
  }

  // Input max matrix
  printf("Enter the maximum matrix:\n");
  for (i = 0; i < n; i++)
  {
    printf("Process %d: ", i);
    for (j = 0; j < m; j++)
    {
      scanf("%d", &max[i][j]);
    }
  }

  // Input available resources
  printf("Enter the available resources: ");
  for (i = 0; i < m; i++)
  {
    scanf("%d", &avail[i]);
  }

  int f[n], ans[n], ind = 0;
  for (k = 0; k < n; k++)
  {
    f[k] = 0; // Initialize all processes as 'not finished'
  }

  // Calculate the Need Matrix as max - alloc
  int need[n][m];
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < m; j++)
    {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }

  // Main algorithm to find a safe sequence
  int y = 0;
  for (k = 0; k < n; k++)
  { // Loop n times for all processes
    for (i = 0; i < n; i++)
    {
      if (f[i] == 0)
      { // If the process is not finished
        int flag = 0;
        for (j = 0; j < m; j++)
        {
          if (need[i][j] > avail[j])
          { // Check if need > available
            flag = 1;
            break;
          }
        }

        if (flag == 0)
        {                 // Process can safely proceed
          ans[ind++] = i; // Store process in safe sequence
          for (y = 0; y < m; y++)
          {
            avail[y] += alloc[i][y]; // Free the resources
          }
          f[i] = 1; // Mark process as finished
        }
      }
    }
  }

  // Check if all processes are finished
  int flag = 1;
  for (i = 0; i < n; i++)
  {
    if (f[i] == 0)
    {
      flag = 0;
      printf("The following system is not safe.\n");
      break;
    }
  }

  // Print the safe sequence if the system is safe
  if (flag == 1)
  {
    printf("Following is the SAFE Sequence:\n");
    for (i = 0; i < n - 1; i++)
    {
      printf(" P%d ->", ans[i]);
    }
    printf(" P%d\n", ans[n - 1]);
  }

  return 0;
}
