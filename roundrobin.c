#include <stdio.h>
#include <stdbool.h>

void calculateRoundRobin(int n, int at[], int bt[], int tq) {
    int wt[n], tat[n], ct[n], remaining_bt[n];
    int time = 0, completed = 0;
    bool isProcessInQueue = true;
    
    // Copy burst times to remaining burst time array
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
        wt[i] = 0;
        ct[i] = 0;
    }

    printf("\nGantt Chart:\n");
    while (completed < n) {
        isProcessInQueue = false;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining_bt[i] > 0) {
                isProcessInQueue = true;

                printf("P%d | ", i + 1);

                if (remaining_bt[i] > tq) {
                    time += tq;
                    remaining_bt[i] -= tq;
                } else {
                    time += remaining_bt[i];
                    remaining_bt[i] = 0;
                    ct[i] = time;
                    completed++;
                }
            }
        }
        if (!isProcessInQueue) time++;
    }
    printf("\n");

    // Calculate TAT and WT
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    // Print Results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
}

int main() {
    int n, tq;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];

    printf("Enter the arrival times of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &at[i]);
    }

    printf("Enter the burst times of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    calculateRoundRobin(n, at, bt, tq);

    return 0;
}
