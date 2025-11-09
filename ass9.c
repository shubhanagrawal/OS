#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int ref[20];
    int f;
    int n;
    int avail;
    int frames[20];        // fixed: cannot use variable-length array before initialization
    int k = 0;
    int count = 0;
    int currpage;
    int min;
    int lru;
    int framesfilled = 0;
    int lastused[20];      // fixed: must be declared with a known size

    printf("Enter no of frames: ");
    scanf("%d", &f);
    printf("Enter no of pages: ");
    scanf("%d", &n);
    printf("Enter the Reference String: ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref[i]);  // fixed: add '&' and remove trailing space
    }

    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
        lastused[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        avail = 0;
        currpage = ref[i];

        // Check if current page already exists in any frame
        for (int j = 0; j < f; j++)
        {
            if (frames[j] == currpage)
            {
                avail = 1;
                lastused[j] = i;  // update last used time
                break;
            }
        }

        if (avail == 0)
        {
            count++;
            if (framesfilled < f)
            {
                frames[framesfilled] = currpage;
                lastused[framesfilled] = i;
                framesfilled++;
            }
            else
            {
                // Find least recently used frame
                min = 9999;
                for (int j = 0; j < f; j++)
                {
                    if (lastused[j] < min)
                    {
                        min = lastused[j];
                        lru = j;
                    }
                }

                frames[lru] = currpage;
                lastused[lru] = i;
            }
        }

        printf("\nFrames after page %d: ", currpage);
        for (int j = 0; j < f; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }

        if (avail == 0)
            printf("  --> Page Fault");
        else
            printf("  --> No Fault");
    }

    printf("\n\nTotal Page Faults = %d\n", count);

    printf("Final Frame State: ");
    for (int i = 0; i < f; i++)
    {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
    }
    printf("\n");

    return 0;
}
