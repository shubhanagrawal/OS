#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int ref[20];
    int f;
    int n;
    int avail;
    int frames[f];
    int k=0;
    int count=0;
    int currpage;
    int min;
    int lru;
    int framesfilled=0;
    int lastused[f];

    printf("Enter no of frames");
    scanf("%d",&f);
    printf("Enter no of pages");
    scanf("%d",&n);
    printf("Enter The Reference String ");

    for(int i=0;i<n;i++)
    {
        scanf("%d ",ref[i]);
    }

    for(int i=0;i<f;i++)
    {
        frames[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        avail=0;
        for(int j=0;j<f;j++)
        {
            if(ref[i]==frames[j])
            {
                avail=1;
                break;
            }
        }
        
        if(avail==0)
        {
            count++;
            if(framesfilled<n)
            {
                frames[framesfilled]=ref[i];
                lastused[framesfilled]=i;
                framesfilled++;
            }
        else
        {
            min=ref[i];
            for(int j=0;j<f;j++)
            {
            if(lastused[j]<min)
            {
                min=lastused[j];
                lru=j;
            }
            frames[lru]=currpage;
            lastused[lru]=i;
            }
        }


    }
}

printf("No of Faults is = %d ", count);

for(int i=0;i<f;i++)
{
    printf("%d ",frames[i]);
}

return 0;

}