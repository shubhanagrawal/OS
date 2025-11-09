#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void sort(int p[20], int at[20], int bt[20], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfs(int at[20], int bt[20], int ct[20], int p[20], int n, int tat[20], int wt[20])
{
    ct[0] = at[0] + bt[0];
    for (int i = 1; i < n; i++)
    {
        if (ct[i - 1] < at[i])
        {
            ct[i] = at[i] + bt[i]; // CPU idle till process arrives
        }
        else
        {
            ct[i] = ct[i - 1] + bt[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

void gantt(int at[20], int bt[20], int ct[20], int n, int p[20])
{
    printf("\nGantt Chart:\n ");

    for (int i = 0; i < n; i++)
        printf("--------");
    printf("\n|");

    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < at[i])
        {
            printf(" IDLE |");
            time = at[i];
        }
        printf(" P%d |", p[i]);
        time += bt[i];
    }

    printf("\n ");
    for (int i = 0; i < n; i++)
        printf("--------");

    time = 0;
    printf("\n0");
    for (int i = 0; i < n; i++)
    {
        if (time < at[i])
        {
            printf("     %d", at[i]);
            time = at[i];
        }
        time += bt[i];
        printf("      %d", time);
    }
    printf("\n");
}

void findavg(int tat[20], int wt[20], int n)
{
    int tatsum = 0;
    int wtsum = 0;

    for (int i = 0; i < n; i++)
        tatsum += tat[i];

    for (int i = 0; i < n; i++)
        wtsum += wt[i];

    float atat = (float)tatsum / n;
    float awt = (float)wtsum / n;

    printf("\nAverage Turnaround Time = %.2f", atat);
    printf("\nAverage Waiting Time = %.2f\n", awt);
}

void print(int at[20], int bt[20], int ct[20], int tat[20], int wt[20], int n)
{
    printf("\nAT\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; i++)
    {
        printf("\n%d\t%d\t%d\t%d\t%d", at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\n");
}

int main()
{
    int n, at[20], p[20], bt[20], ct[20], tat[20], wt[20];
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process No, Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
    }

    sort(p, at, bt, n);
    fcfs(at, bt, ct, p, n, tat, wt);
    print(at, bt, ct, tat, wt, n);
    findavg(tat, wt, n);
    gantt(at, bt, ct, n, p);

    return 0;
}
