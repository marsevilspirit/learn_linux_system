#include "threadqueue.h"
#include <pthread.h>
#include <unistd.h>

#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define CAPACITY 10

pthread_mutex_t mutex;
pthread_cond_t cond_full;
pthread_cond_t cond_empty;

MPMCQueue* queue;

void* producer(void* arg) 
{
    int i = 0;
    while(1) 
    {
        i++;
        int* data = malloc(sizeof(int));
        *data = i;
        printf("%ld生产者: %d\n", pthread_self(), *data);       

        pthread_mutex_lock(&mutex);
        while(queue->size >= queue->capacity)
        {
            pthread_cond_wait(&cond_full, &mutex);
        }

        MPMCQueuePush(queue, (void*)data);

        pthread_cond_broadcast(&cond_empty);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg) 
{
    while (1) 
    {
        pthread_mutex_lock(&mutex);

        while (queue->size == 0) 
        {
            pthread_cond_wait(&cond_empty, &mutex);
        }

        int* data = (int*)MPMCQueuePop(queue);

        pthread_cond_broadcast(&cond_full);
        pthread_mutex_unlock(&mutex);

        printf("%ld消费者: %d\n", pthread_self(), *data);
        free(data);
    }

    pthread_exit(NULL);
}

int main(void) 
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_full, NULL);
    pthread_cond_init(&cond_empty, NULL);

    queue = MPMCQueueInit(CAPACITY);

    pthread_t producerThreads[NUM_PRODUCERS];
    pthread_t consumerThreads[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; ++i) 
    {
        pthread_create(&producerThreads[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) 
    {
        pthread_create(&consumerThreads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i) 
    {
        pthread_join(producerThreads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) 
    {
        pthread_join(consumerThreads[i], NULL);
    }

    MPMCQueueDestory(queue);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_full);
    pthread_cond_destroy(&cond_empty);

    return 0;
}

