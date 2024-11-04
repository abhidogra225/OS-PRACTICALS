#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int n = argc - 1; // Number of elements
    int arr[n];

    // Convert command line arguments to integers
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Sort the array
    bubble_sort(arr, n);

    // Prepare arguments for the child process
    char *args[n + 2]; // +1 for program name, +1 for NULL terminator
    args[0] = "./reverse_display"; // Name of the child program
    for (int i = 0; i < n; i++) {
        args[i + 1] = (char *)malloc(12 * sizeof(char)); // Allocate memory for each integer
        sprintf(args[i + 1], "%d", arr[i]); // Convert integer to string
    }
    args[n + 1] = NULL; // Null terminate the args

    pid_t pid = fork(); // Create a child process
    if (pid == 0) { // Child process
        execve(args[0], args, NULL); // Execute the reverse_display program
        perror("execve failed"); // If execve fails
        exit(1); // Exit on failure
    } else if (pid > 0) { // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Parent process finished.\n");
    } else {
        perror("fork failed"); // If fork fails
        return 1; // Exit on fork failure
    }

    // Free allocated memory for args
    for (int i = 1; i <= n; i++) {
        free(args[i]);
    }

    return 0;
}
