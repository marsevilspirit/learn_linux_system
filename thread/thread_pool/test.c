#include "thread_pool.h"
#define NUM_THREADS 5


void* calculateFactorial(void* arg) 
{
    int n = *((int*)arg);
    long long result = 1;
    for (int i = 1; i <= n; ++i) 
    {
        result *= i;
    }
    printf("%-3d的阶乘为 %-lld\n", n, result);

    return NULL;
}

int main(void)
{
    tpool_t pool;
    int num_threads = NUM_THREADS;

    init_tpool(&pool, num_threads);

    int tasks[] = {1,2,3,4,5,6,7,8,9,10};
    for (int i = 0; i < sizeof(tasks) / sizeof(tasks[0]); ++i)
    {
        add_task_tpool(&pool, calculateFactorial, &tasks[i]);
    }

    waitCompletion(&pool);

    destroy_tpool(&pool);

    return 0;
}
