#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREAD_NUM 5

typedef struct tpool_work{
    void* (*work_routine)(void*);
    void* args;
    struct tpool_work* next;// list
}tpool_work_t;

typedef struct tpool{
    size_t max_thread_num;
    size_t shutdown;
    pthread_t *id;//id array
    tpool_work_t tpool_head;// head node
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_ready;// cond
}tpool_t;

int create_tpool(tpool_t* pool, size_t max_thread_num);

int add_task_tpool(tpool_t* pool, void* (*routine)(void*), void* args);

void destroy_tpool(tpool_t* pool);
