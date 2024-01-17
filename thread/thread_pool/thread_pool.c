#include "thread_pool.h"

void init_tqueue(tqueue_t* queue, int capacity)
{
    queue->task = (tpool_work_t*)malloc(capacity * sizeof(tpool_work_t));
    queue->front = queue->rear = queue->size = 0;
    queue->capacity = capacity;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->full, NULL);
    pthread_cond_init(&queue->empty, NULL);
}

void destroy_tqueue(tqueue_t* queue)
{
    free(queue->task);
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->full);
    pthread_cond_destroy(&queue->empty);
}

void add_task_tqueue(tqueue_t* queue, tpool_work_t task)
{
    pthread_mutex_lock(&queue->mutex);

    while(queue->size >= queue->capacity)
    {
        pthread_cond_wait(&queue->full, &queue->mutex);
    }

    queue->task[queue->rear] = task;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;

    pthread_cond_broadcast(&queue->empty);
    pthread_mutex_unlock(&queue->mutex);
}

tpool_work_t pop_task_tqueue(tqueue_t* queue)
{
    pthread_mutex_lock(&queue->mutex);

    while(queue->size == 0)
    {
        pthread_cond_wait(&queue->empty, NULL);
    }

    tpool_work_t task = queue->task[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    pthread_cond_broadcast(&queue->full);
    pthread_mutex_unlock(&queue->mutex);

    return task;
}

void* worker(void* arg)
{
    targs_t* args = (targs_t*)arg;
    tqueue_t* task_queue = args->task_queue;

    while(1)
    {
        tpool_work_t task = pop_task_tqueue(task_queue);

        if(task.task_function ==NULL)
        {
            break;
        }

        task.task_function(task.args);
    }

    free(arg);
    return NULL;
}

void init_tpool(tpool_t* pool, int num_threads)
{
    pool->threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    pool->num_threads = num_threads;
    pool->task_queue = (tqueue_t*)malloc(sizeof(tqueue_t));
    pool->stop = 0;

    init_tqueue(pool->task_queue, QUEUE_CAPACITY);

    for(int i = 0; i < num_threads; i++)
    {
       targs_t* args = (targs_t*)malloc(sizeof(targs_t));
       args->task_queue = pool->task_queue;
       args->thread_id = i;
       pthread_create(&pool->threads[i], NULL, worker, args);
    }
}

void destroy_tpool(tpool_t* pool)
{
    destroy_tqueue(pool->task_queue);
    free(pool->task_queue);
    free(pool->threads);
}

void add_task_tpool(tpool_t* pool, void* (*task_function)(void*), void* arg)
{
    tpool_work_t task = {task_function, arg};
    add_task_tqueue(pool->task_queue, task);
}

void waitCompletion(tpool_t* pool)
{
    for (int i = 0; i < pool->num_threads; ++i)
    {
        add_task_tpool(pool, NULL, NULL); 
    }

    for (int i = 0; i < pool->num_threads; ++i)
    {
        pthread_join(pool->threads[i], NULL);
    }
}

void stopThreadPool(tpool_t* pool)
{
    pool->stop = 1;

    for (int i = 0; i < pool->num_threads; ++i)
    {
        add_task_tpool(pool, NULL, NULL);
    }
}

