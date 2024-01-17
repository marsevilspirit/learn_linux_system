#include "threadqueue.h"
#include <pthread.h>

#define QUEUE_CAPACITY 10
#define NUM_ITEMS 200000

pthread_mutex_t mutex;
pthread_cond_t cond;


void *producer(void *arg);
void *consumer(void *arg);

SPSCQueue *queue;

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    // 初始化SPSC队列
    queue = SPSCQueueInit(QUEUE_CAPACITY);

    // 创建生产者和消费者线程
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // 销毁队列
    SPSCQueueDestory(queue);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

void *producer(void *arg) 
{
    for (int i = 0; i < NUM_ITEMS; ++i) 
    {
        int *data = malloc(sizeof(int));
        *data = i;
        //lock
        pthread_mutex_lock(&mutex);

        while(queue->size >= queue->capacity)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        SPSCQueuePush(queue, data);
        printf("生产: %d\n", *data);

        //unlock
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    return NULL;
}

void *consumer(void *arg) 
{
    for (int i = 0; i < NUM_ITEMS; ++i) 
    {
        //lock
        pthread_mutex_lock(&mutex);

        while(queue->size == 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        int *data = SPSCQueuePop(queue);
        if (data != NULL)
        {
            printf("消费: %d\n", *data);
            free(data);
        }
        //unlock
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    return NULL;
}

