#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct mallocBlock 
{
    struct mallocBlock *before;
    int size;
    int use;
} mb;

static mb *mb_last = NULL;

void *my_malloc(int size) 
{
    mb *mbp;

    for (mbp = mb_last; mbp != NULL; mbp = mbp->before) 
    {
        if (mbp->use == 0 && mbp->size >= size) 
        {
            break;
        }
    }
    if (mbp == NULL) 
    {
        mbp = sbrk(sizeof(mb) + size);
        if (mbp == (void *)-1)
            return (void *)0;
        mbp->size = size;
        mbp->before = mb_last;
        mb_last = mbp;
    }

    mbp->use = 1;
    return mbp + 1;
}

int my_free(void *p) 
{
    if (p == NULL)
        return 0;
    mb *mbp = (mb *)p - 1;
    mbp->use = 0;
    return 0;
}

int main(void) 
{
    char *a = my_malloc(1);
    char *b = my_malloc(2);
    char *c = my_malloc(3);
    my_free(a);
    my_free(b);
    my_free(c);
    printf("%p,%p,%p\n", a, b, c);
    b = my_malloc(1);
    printf("%p,%p,%p\n", a, b, c);
    return 0;
}
