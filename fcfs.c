#include <stdio.h>

void calculateTimes(int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    int start_time = 0;
    for (int i = 0; i < n; i++) {
        if (start_time < at[i]) {
            start_time = at[i];  // Wait for the process to arrive
        }
        ct[i] = start_time + bt[i]; // Completion time
        start_time = ct[i];         // Update the start time for the next process
        tat[i] = ct[i] - at[i];     // Turnaround time
        wt[i] = tat[i] - bt[i];     // Waiting time
    }
}

void printGanttChart(int n, int bt[], int ct[], int at[]) {
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("P%d", i + 1);
        for (int j = 0; j < bt[i] - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("--");
        printf(" ");
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++) printf("  ");
        if (ct[i] >= 10) printf("\b"); // Adjust alignment for double digits
        printf("%d", ct[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];
    float total_tat = 0, total_wt = 0;

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // Swap arrival time
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;
                // Swap burst time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
            }
        }
    }

    calculateTimes(n, at, bt, ct, tat, wt);

    // Calculate total Turnaround Time and Waiting Time
    for (int i = 0; i < n; i++) {
        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    printGanttChart(n, bt, ct, at);

    return 0;
}
