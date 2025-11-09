#include <stdio.h>

void sort(int p[], int at[], int bt[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                int temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;

                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
            }
        }
    }
}

void fcfs(int at[], int bt[], int ct[], int p[], int n, int tat[], int wt[])
{
    ct[0] = at[0] + bt[0]; // first process completes after its burst time

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

void findavg(int tat[], int wt[], int n)
{
    float stat = 0, swt = 0;

    for (int i = 0; i < n; i++)
    {
        stat += tat[i];
        swt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f", stat / n);
    printf("\nAverage Waiting Time = %.2f\n", swt / n);
}

void print(int p[], int at[], int bt[], int ct[], int tat[], int wt[], int n)
{
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

int main()
{
    int n, at[20], p[20], bt[20], ct[20], tat[20], wt[20];
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Process No, Arrival Time and Burst Time: ");
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
    }

    sort(p, at, bt, n);
    fcfs(at, bt, ct, p, n, tat, wt);
    print(p, at, bt, ct, tat, wt, n);
    findavg(tat, wt, n);

    return 0;
}
