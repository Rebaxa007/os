#include <stdio.h>

#define MAX 10

// Function declarations
void input_data(int n_processes, int n_resources, int max[MAX][MAX], int allocation[MAX][MAX], int available[MAX]);
void calculate_need(int n_processes, int n_resources, int max[MAX][MAX], int allocation[MAX][MAX], int need[MAX][MAX]);
int is_safe(int n_processes, int n_resources, int allocation[MAX][MAX], int need[MAX][MAX], int available[MAX], int safe_sequence[MAX]);

int main() {
    int n_processes, n_resources;
    int available[MAX], max[MAX][MAX], allocation[MAX][MAX], need[MAX][MAX];
    int safe_sequence[MAX];

    // Input data
    printf("Enter the number of processes: ");
    scanf("%d", &n_processes);

    printf("Enter the number of resource types: ");
    scanf("%d", &n_resources);

    input_data(n_processes, n_resources, max, allocation, available);
    calculate_need(n_processes, n_resources, max, allocation, need);

    // Check system safety
    if (is_safe(n_processes, n_resources, allocation, need, available, safe_sequence)) {
        printf("\nSystem is in a safe state.\nSafe Sequence: ");
        for (int i = 0; i < n_processes; i++) {
            printf("P%d ", safe_sequence[i] + 1);
        }
        printf("\n");
    } else {
        printf("\nSystem is not in a safe state.\n");
    }

    return 0;
}

// Function to input data
void input_data(int n_processes, int n_resources, int max[MAX][MAX], int allocation[MAX][MAX], int available[MAX]) {
    printf("\nEnter available resources:\n");
    for (int i = 0; i < n_resources; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < n_processes; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Enter maximum resource requirements:\n");
        for (int j = 0; j < n_resources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &max[i][j]);
        }

        printf("Enter allocated resources:\n");
        for (int j = 0; j < n_resources; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);
        }
    }
}

// Function to calculate the need matrix
void calculate_need(int n_processes, int n_resources, int max[MAX][MAX], int allocation[MAX][MAX], int need[MAX][MAX]) {
    for (int i = 0; i < n_processes; i++) {
        for (int j = 0; j < n_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check system safety and return safe sequence
int is_safe(int n_processes, int n_resources, int allocation[MAX][MAX], int need[MAX][MAX], int available[MAX], int safe_sequence[MAX]) {
    int work[MAX], finish[MAX] = {0};
    int index = 0;

    // Initialize work vector with available resources
    for (int i = 0; i < n_resources; i++) {
        work[i] = available[i];
    }

    for (int count = 0; count < n_processes; count++) {
        int found = 0;

        for (int i = 0; i < n_processes; i++) {
            if (!finish[i]) { // Check if process is not finished
                int can_allocate = 1;

                for (int j = 0; j < n_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < n_resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    safe_sequence[index++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            return 0; // System is not in a safe state
        }
    }

    return 1; // System is in a safe state
}
