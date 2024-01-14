#include "threadqueue.h"

SPSCQueue*SPSCQueueInit(int capacity)
{
    SPSCQueue * queue = (SPSCQueue *)malloc(sizeof(SPSCQueue));
    if(queue == NULL)
    {
        fprintf(stderr, "线程队列分配失败\n");
        exit(EXIT_FAILURE);
    }

    queue->capacity = capacity;
    queue->buffer = (void **)malloc(capacity * sizeof(void *));
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;

    return queue;
}

void SPSCQueuePush(SPSCQueue *queue, void *s)
{
    if(queue->size < queue->capacity)
    {
        queue->buffer[queue->tail] = s;
        queue->tail = (queue->tail + 1) % queue->capacity;
        queue->size++;
    }
    else
    {
        fprintf(stderr, "队列满了\n");     
    }
}

void *SPSCQueuePop(SPSCQueue *queue) 
{
    if(queue->size > 0)
    {
        void *data = queue->buffer[queue->head];
        queue->head = (queue->head + 1) % queue->capacity;
        queue->size--;
        return data;
    }
    else
    {
        fprintf(stderr, "队列是空的\n"); 
        return NULL;
    }
}

void SPSCQueueDestory(SPSCQueue *queue)
{
    free(queue->buffer);
    free(queue);
}
