#include <stdlib.h>
#include <stdio.h>

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
