#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int number = 0;

pthread_rwlock_t rwlock;

void * writeNum(void* arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        int cur = number;
        cur++;
        number = cur;
        printf("++写操作完毕，number : %d, tid = %ld\n", number, pthread_self());
        pthread_rwlock_unlock(&rwlock);
        usleep(500000);
    }

    return NULL;
}

void* readNum(void* arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("--全局变量number = %d, tid = %ld\n", number, pthread_self());
        pthread_rwlock_unlock(&rwlock);
        usleep(500000);
    }

    return NULL;
}

int main(void)
{
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t wtid[3];
    pthread_t rtid[5];
    for(int i = 0; i < 3; i++)
    {
        pthread_create(&wtid[i], NULL, writeNum, NULL);
    }
    for(int i = 0; i < 5; i++)
    {
        pthread_create(&rtid[i], NULL, readNum, NULL);
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(wtid[i], NULL);
    }

    for(int i = 0; i < 5; i++)
    {
        pthread_join(rtid[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
