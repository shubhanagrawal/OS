#include<stdio.h>
#include<math.h>
#include<string.h>



void sort(int at[],int bt[],int p[],int n)
{
    int temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(at[j]>at[j+1])
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

void srtf(int at[],int bt[],int ct[],int p[],int n,int gantt[],int *gantt_len)
{
    int sum=0;
    int remaining_bt[20];
    int k=0;
    for(int i=0;i<n;i++)
    {
        sum+=bt[i];
    }

    for(int i=0;i<n;i++)
    {
        remaining_bt[i]=bt[i];
    }

    for(int i=0;i<sum;i++)
    {
        int shortest=-1;
        int min=9999;

        for(int j=0;j<n;j++)
        {
            if(at[j]<=i && remaining_bt[j]>0) // fixed: should include equal time
            {
                if(remaining_bt[j]<min)
                {
                    min=remaining_bt[j];
                    shortest=j;
                }
            }
        }

        if(shortest!=-1)
        {
            gantt[k++]=p[shortest];
            remaining_bt[shortest]--;
            if(remaining_bt[shortest]==0)
            {
                ct[shortest]=i+1;
            }
        }
        else
        {
            gantt[k++]=-1; // fixed: idle only when no process ready
        }
    }
    *gantt_len = k; // fixed: dereference pointer correctly
}

int main()
{
    int n;
    printf("Enter No of processes ");
    scanf("%d",&n);
    printf("\n");

    int at[n],bt[n],p[n];
    int ct[n],tat[n],wt[n];
    float avg_tat=0,avg_wt=0;

    printf("Enter Process No , Arrival Time and Burst Time of each process \n");
    for(int i=0;i<n;i++)
    {
        printf("The Process No , Arrival and Burst time for process %d is ",i+1);
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
        printf("\n");
    }

    sort(at,bt,p,n);

    
    int gantt[1000],gantt_len=0;

    srtf(at,bt,ct,p,n,gantt,&gantt_len);

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        
    }

    for(int i=0;i<n;i++)
    {
        wt[i]=tat[i]-bt[i];
    }

    for(int i=0;i<n;i++)
    {
        avg_tat+=tat[i];
    }

    for(int i=0;i<n;i++)
    {
        avg_wt+=wt[i];
    }

    avg_tat/=n;
    avg_wt/=n;

    for(int i=0;i<n;i++)
    {
        printf("----");
    }
    printf("\n");
    for(int i=0;i<gantt_len;i++)
    {
        if(gantt[i]==-1)
        {
            printf("IDLE|");
        }
        else
        {
            printf("P%d|",gantt[i]); // fixed: correct format specifier
        }
    
    }
    printf("\n");
    for(int i=0;i<n;i++)
    {
        printf("----");
    }

    for(int i=0;i<gantt_len;i++)
    {
        printf("%d",i);
    }

    return 0;
}
