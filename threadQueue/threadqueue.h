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

//Multi-producer , Multi-consumer Queue
struct MPMCQueue {
    /* Define Your Data Here */
} typedef MPMCQueue;

MPMCQueue *MPMCQueueInit(int capacity);
void MPMCQueuePush(MPMCQueue *queue, void *s);
void *MPMCQueuePop(MPMCQueue *queue);
void MPMCQueueDestory(MPMCQueue *);
