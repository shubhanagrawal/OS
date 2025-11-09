#include <stdio.h>
#include <stdlib.h>
#define m 20

int need[m][m], alloc[m][m], max[m][m], avail[m], n, r;

int issafe()
{
    int work[m];
    int finish[m];
    int ans[m];
    int ind = 0;

    for (int i = 0; i < r; i++)
    {
        work[i] = avail[i];
    }
    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int count = 0;
    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < r; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == r)
                {
                    /* this process can be satisfied */
                    for (int k = 0; k < r; k++)
                        work[k] += alloc[i][k];
                    ans[ind++] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (found == 0)
            break;
    }

    if (count == n)
    {
        printf("SAFE STATE Sequence: ");
        for (int i = 0; i < n; i++)
        {
            printf("P%d", ans[i]);
            if (i < n - 1)
                printf(" -> ");
        }
        printf("\n");
        return 1;
    }
    return 0;
}

void calculateNeed()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

void displayMatrices()
{
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++)
            printf("%d ", alloc[i][j]);
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\nAvailable Resources:\n");
    for (int j = 0; j < r; j++)
        printf("R%d: %d  ", j, avail[j]);
    printf("\n");
}

void requestResources()
{
    int process;
    int request[m];

    printf("Enter Process no of request: ");
    if (scanf("%d", &process) != 1)
        return;
    if (process < 0 || process >= n)
    {
        printf("Invalid process number.\n");
        return;
    }

    printf("Enter No of Resources requested (space separated, %d values):\n", r);
    for (int i = 0; i < r; i++)
    {
        if (scanf("%d", &request[i]) != 1)
            request[i] = 0;
    }

    for (int i = 0; i < r; i++)
    {
        if (request[i] > need[process][i])
        {
            printf("Error: process has exceeded its maximum claim.\n");
            return;
        }
        if (request[i] > avail[i])
        {
            printf("Resources not available currently.\n");
            return;
        }
    }

    /* try to allocate temporarily */
    for (int i = 0; i < r; i++)
    {
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
        avail[i] -= request[i];
    }

    if (issafe())
    {
        printf("Safe state found — resources allocated to process %d.\n", process);
    }
    else
    {
        printf("Safe state could not be found — rolling back.\n");
        for (int i = 0; i < r; i++)
        {
            alloc[process][i] -= request[i];
            need[process][i] += request[i];
            avail[i] += request[i];
        }
    }
}

int main()
{
    printf("=== BANKER'S ALGORITHM IMPLEMENTATION ===\n\n");

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1)
        return 1;

    if (n <= 0 || n > m)
    {
        printf("Error: Number of processes must be between 1 and %d\n", m);
        return 1;
    }

    printf("Enter the number of resources: ");
    if (scanf("%d", &r) != 1)
        return 1;

    if (r <= 0 || r > m)
    {
        printf("Error: Number of resources must be between 1 and %d\n", m);
        return 1;
    }

    printf("\nEnter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process P%d: ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter the MAX Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process P%d: ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the Available Resources:\n");
    for (int i = 0; i < r; i++)
    {
        printf("Resource R%d: ", i);
        scanf("%d", &avail[i]);
    }

    calculateNeed();

    int choice;
    do
    {
        printf("\n=== MENU ===\n");
        printf("1. Check if system is in a safe state\n");
        printf("2. Request resources for a process\n");
        printf("3. Display current system state\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
            break;

        switch (choice)
        {
        case 1:
            if (issafe())
                printf("The system is in a SAFE state.\n");
            else
                printf("The system is in an UNSAFE state.\n");
            break;
        case 2:
            requestResources();
            break;
        case 3:
            displayMatrices();
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
