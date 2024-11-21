#include <stdio.h>

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int remainingTime;  // Remaining Burst Time
    int completionTime; // Completion Time
    int turnAroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
};

void roundRobin(struct Process p[], int n, int timeQuantum) {
    int currentTime = 0, completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remainingTime > 0 && p[i].arrivalTime <= currentTime) {
                if (p[i].remainingTime > timeQuantum) {
                    currentTime += timeQuantum;
                    p[i].remainingTime -= timeQuantum;
                } else {
                    currentTime += p[i].remainingTime;
                    p[i].remainingTime = 0;
                    p[i].completionTime = currentTime;
                    p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
                    p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
                    completed++;
                }
            }
        }
    }
}

void display(struct Process p[], int n) {
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnAround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1; // Process ID starts from 1
        printf("Enter Arrival Time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime; // Initialize remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(p, n, timeQuantum);
    display(p, n);

    return 0;
}
