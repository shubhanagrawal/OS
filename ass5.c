#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#define Max 20

void pipe1()
{
    int filedes[2];
    pid_t pid;
    char str1[20];
    char buffer[20];

    if(pipe(filedes)<0)
    {
        printf("Pipe call Failed ");
        return;
    }
    
    pid = fork();

    if(pid < 0)
    {
        printf("Fork Call Failed....");
        return;
    }

    if(pid>0)
    {
        printf("Enter string to write into pipe: ");
        fgets(str1, Max, stdin);                        // fixed: MAX → Max
        close(filedes[0]);
        write(filedes[1], str1, strlen(str1) + 1);      // fixed: str → str1
        printf("Parent has written into pipe: %s\n", str1);
        close(filedes[1]);
        wait(NULL);
    }

    if(pid==0)
    {
        close(filedes[1]);
        read(filedes[0], buffer, sizeof(buffer));        // fixed: wrong strlen(buffer)
        printf("Child has read from pipe: %s\n", buffer);
        close(filedes[0]);
    }
}

void pipe2()
{
    int filedes1[2];
    int filedes2[2];
    char str1[20], str2[20], buffer[20];
    pid_t pid;

    printf("Enter string to be written by parent: ");
    fgets(str1, Max, stdin);
    printf("Enter string to be written by child: ");
    fgets(str2, Max, stdin);

    if(pipe(filedes1)<0 || pipe(filedes2)<0)
    {
        printf("Pipe System Call Failed ");
        return;
    }

    pid = fork();

    if(pid<0)
    {
        printf("Fork System Call Failed ");
        return;
    }

    if(pid==0)
    {
        close(filedes1[0]);
        write(filedes1[1], str2, strlen(str2) + 1);
        printf("Child is writing into Pipe 1: %s\n", str2);   // fixed: str1 → str2

        close(filedes2[1]);
        read(filedes2[0], buffer, sizeof(buffer));            // fixed: wrong strlen(buffer)
        printf("Child is reading from Pipe 2: %s\n", buffer);
        close(filedes2[0]);
    }

    if(pid > 0)
    {
        close(filedes1[1]);
        read(filedes1[0], buffer, sizeof(buffer));            // fixed: wrong strlen(buffer)
        printf("Parent is reading from Pipe 1: %s\n", buffer);

        close(filedes2[0]);
        write(filedes2[1], str1, strlen(str1) + 1);
        printf("Parent is writing into Pipe 2: %s\n", str1);  // fixed: str2 → str1
        close(filedes2[1]);

        wait(NULL);
    }
}
