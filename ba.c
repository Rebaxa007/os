#include <stdio.h>

int main()
{
    int n, m, i, j;

    // Take user input for number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    // Take input for Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("Allocated Resources for Process P%d, Resource R%d: ", i, j);
            scanf("%d", &alloc[i][j]);
        }
    }

    // Take input for Max Matrix
    printf("Enter the Max Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("Maximum Resources for Process P%d, Resource R%d: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    // Take input for Available Resources
    printf("Enter the Available Resources:\n");
    for (i = 0; i < m; i++)
    {
        printf("Available Resources for Resource R%d: ", i);
        scanf("%d", &avail[i]);
    }

  

    // Calculate the Need Matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[n], safeSeq[n], count = 0;
    for (i = 0; i < n; i++)
        finish[i] = 0; // Initialize finish array to 0

    // Banker's Algorithm - Safety check
    while (count < n)
    {
        int found = 0;

        // Try to find a process that can finish
        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            { // If process i is not finished
                int canFinish = 1;

                // Check if this process's needs can be met with available resources
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        canFinish = 0;
                        break;
                    }
                }

                // If process can finish, update available resources
                if (canFinish)
                {
                    for (j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i][j]; // Release the allocated resources
                    }
                    safeSeq[count++] = i; // Add process i to the safe sequence
                    finish[i] = 1;        // Mark process i as finished
                    found = 1;
                }
            }
        }

        // If no process can finish, the system is not in a safe state
        if (!found)
        {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }

    // If safe sequence exists
    printf("The system is in a safe state.\nSafe Sequence: ");
    for (i = 0; i < n; i++)
    {
        printf("P%d ", safeSeq[i]); // Print the safe sequence of processes
    }
    printf("\n");

    return 0;
}
