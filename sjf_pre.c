#include <stdio.h>

void main() {
    int n, i, j, temp;
    int process[10], arrival[10], burst[10], remaining[10], waiting[10], turnaround[10], completion[10];
    int gantt_chart[100][2]; // Store the process ID and the time intervals for Gantt chart
    float avg_wait = 0, avg_turnaround = 0;

    // Input number of processes and their details
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        process[i] = i + 1;  // Process ID
        printf("Process %d: ", i + 1);
        scanf("%d %d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];  // Initially, remaining burst time equals the original burst time
    }

    // Sort by Arrival Time, then Burst Time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j] || 
               (arrival[i] == arrival[j] && burst[i] > burst[j])) {
                temp = arrival[i], arrival[i] = arrival[j], arrival[j] = temp;
                temp = burst[i], burst[i] = burst[j], burst[j] = temp;
                temp = process[i], process[i] = process[j], process[j] = temp;
            }
        }
    }

    // Initialize time
    int time = 0, completed = 0, visited[10] = {0};
    int gantt_index = 0;

    // Loop until all processes are completed
    while (completed < n) {
        int min_burst = 9999, min_index = -1;

        // Find the process with the shortest remaining burst time among those that have arrived
        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && !visited[i] && remaining[i] > 0 && remaining[i] < min_burst) {
                min_burst = remaining[i];
                min_index = i;
            }
        }

        // If no process is ready, increment time
        if (min_index == -1) {
            time++;
            continue;
        }

        // Mark the process as visited and store in the Gantt chart
        visited[min_index] = 1;
        gantt_chart[gantt_index][0] = process[min_index];
        gantt_chart[gantt_index][1] = time;
        gantt_index++;

        // Execute the process (reduce its remaining burst time by 1)
        remaining[min_index]--;
        time++;

        // If the process finishes, calculate its completion, turnaround, and waiting times
        if (remaining[min_index] == 0) {
            completion[min_index] = time;
            turnaround[min_index] = completion[min_index] - arrival[min_index];
            waiting[min_index] = turnaround[min_index] - burst[min_index];
            avg_turnaround += turnaround[min_index];
            avg_wait += waiting[min_index];
            completed++;
        }
    }

    // Output the results
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", process[i], arrival[i], burst[i],
               completion[i], turnaround[i], waiting[i]);
    }

    // Print averages
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wait / n);

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    printf("---------------------------------------------------\n");
    printf("|");
    for (i = 0; i < gantt_index; i++) {
        printf(" P%d |", gantt_chart[i][0]);
    }
    printf("\n");

    // Print the time line at the top of the Gantt chart
    printf("0");
    for (i = 0; i < gantt_index; i++) {
        printf("    %d", gantt_chart[i][1]);
    }
    printf("\n");
}
