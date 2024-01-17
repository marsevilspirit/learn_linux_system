#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Single-producer , single-consumer Queue
struct SPSCQueue {
    int capacity;
    void **buffer;
    int size;
    int head;
    int tail;
} typedef SPSCQueue;

SPSCQueue *SPSCQueueInit(int capacity);
void SPSCQueuePush(SPSCQueue *queue, void *s);
void *SPSCQueuePop(SPSCQueue *queue);
void SPSCQueueDestory(SPSCQueue *);

// 定义多生产者多消费者队列结构
struct MPMCQueue {
    /* Define Your Data Here */
    void **buffer;
    int capacity;
    int size;
    int head;
    int tail;
} typedef MPMCQueue;

MPMCQueue *MPMCQueueInit(int capacity);
void MPMCQueuePush(MPMCQueue *queue, void *s);
void *MPMCQueuePop(MPMCQueue *queue);
void MPMCQueueDestory(MPMCQueue *);
