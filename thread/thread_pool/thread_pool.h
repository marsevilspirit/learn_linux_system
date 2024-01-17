#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QUEUE_CAPACITY 30

typedef struct tpool_work{
    void* (*task_function)(void*);
    void* args;
}tpool_work_t;

typedef struct pthread_queue{
    tpool_work_t* task;
    int capacity;
    int size;
    int front;
    int rear;
    pthread_mutex_t mutex;
    pthread_cond_t empty;
    pthread_cond_t full;
}tqueue_t;

typedef struct {
    pthread_t* threads;
    int num_threads;
    tqueue_t* task_queue;
    int stop;
}tpool_t;

typedef struct {
    tqueue_t* task_queue;
    int thread_id;
} targs_t;

void init_tqueue(tqueue_t* queue, int capacity);

void destroy_tqueue(tqueue_t* queue);

void add_task_tqueue(tqueue_t* queue, tpool_work_t task);

tpool_work_t pop_task_tqueue(tqueue_t* queue);

void init_tpool(tpool_t* pool, int num_threads);

void add_task_tpool(tpool_t* pool, void* (*task_function)(void*), void* arg);

void destroy_tpool(tpool_t* pool);

void waitCompletion(tpool_t* pool);

void stopThreadPool(tpool_t* pool);
