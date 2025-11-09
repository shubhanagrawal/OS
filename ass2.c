#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

void Zombie()
{
    pid_t pid;
    pid = fork();

    if(pid < 0)
    {
        printf("Fork Call Failed");
    }
    if(pid==0)
    {
        printf("ID of child is %d ",getpid());
    }

    if(pid>0)
    {
        sleep(10);
        printf("...........Parent");
        system("ps -axj | tail");
    }
}


void orphan()
{
    pid_t pid;
    pid=fork();

    if(pid < 0)
    {
        printf("Fork Call Failed..");
    }

    if(pid==0)
    {
        sleep(10);
        printf("ID OF Child is %d ", getpid());
        printf("ID of Parent is %d ", getppid());
    }

    if(pid > 0)
    {
        printf(" ID of Parent is %d ", getpid());
    }
}