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



// 初始化多生产者多消费者队列
MPMCQueue *MPMCQueueInit(int capacity) 
{
    MPMCQueue *queue = (MPMCQueue *)malloc(sizeof(MPMCQueue));

    queue->buffer = (void **)malloc(capacity * sizeof(void *));
    queue->capacity = capacity;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;

    return queue;
}

// 将元素推入队列
void MPMCQueuePush(MPMCQueue *queue, void *s) 
{
    // 在队列中添加元素
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

// 从队列中弹出元素
void *MPMCQueuePop(MPMCQueue *queue) 
{
    // 从队列中取出元素
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

// 销毁多生产者多消费者队列
void MPMCQueueDestory(MPMCQueue *queue) 
{
    free(queue->buffer);
    free(queue);
}
