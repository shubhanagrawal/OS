#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
// #include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt, mutex;
int reader_count = 0;
int sharedvar = 99;

void *reader(void *params)
{
    sem_wait(&mutex);
    reader_count++;
    if (reader_count == 1)
    {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("Reader has entered. Shared value = %d\n", sharedvar);
    sleep(1);

    sem_wait(&mutex);
    reader_count--;
    if (reader_count == 0)
    {
        sem_post(&wrt);
    }
    printf("Reader is leaving. Remaining readers = %d\n", reader_count);
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *writer(void *params)
{
    printf("Writer is trying to enter...\n");
    sem_wait(&wrt);
    sharedvar += 10;
    printf("Writer has entered and modified value to %d\n", sharedvar);
    sem_post(&wrt);
    printf("Writer is leaving...\n");

    pthread_exit(NULL);
}

int main()
{
    int n;
    printf("Enter No of Reader - Writer Pairs: ");
    scanf("%d", &n);

    pthread_t readers[n], writers[n];

    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < n; i++)
    {
        pthread_create(&readers[i], NULL, reader, NULL);
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);

    return 0;
}
