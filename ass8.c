#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int ref[20];
    int f;
    int n;
    int avail;
    int frames[20];  // fixed: must have defined size
    int k = 0;
    int count = 0;

    printf("Enter no of frames: ");
    scanf("%d", &f);

    printf("Enter no of pages: ");
    scanf("%d", &n);

    printf("Enter the Reference String: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref[i]);   // fixed: added &
    }

    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;         // initialize frames as empty
    }

    printf("\nFIFO Page Replacement Process:\n");

    for (int i = 0; i < n; i++)
    {
        avail = 0;
        for (int j = 0; j < f; j++)
        {
            if (frames[j] == ref[i])
            {
                avail = 1;
                break;
            }
        }

        if (avail == 0)
        {
            frames[k] = ref[i];
            k = (k + 1) % f;        // fixed: was (k+1)/n
            count++;

            for (int d = 0; d < f; d++)
            {
                if (frames[d] != -1)
                    printf(" %d ", frames[d]);
                else
                    printf(" - ");
            }
            printf("  --> Page Fault\n");
        }
        else
        {
            for (int d = 0; d < f; d++)
            {
                if (frames[d] != -1)
                    printf(" %d ", frames[d]);
                else
                    printf(" - ");
            }
            printf("  --> No Page Fault\n");
        }
    }

    printf("\nTotal number of Page Faults = %d\n", count);

    printf("Final State of Frames: ");
    for (int i = 0; i < f; i++)
    {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
    }
    printf("\n");

    return 0;
}
