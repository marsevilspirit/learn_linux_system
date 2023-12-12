#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void deal_child(int num)
{
    printf("deal_child into\n");
    wait(NULL);
}

int main(void)
{
    signal(SIGCHLD, deal_child);
    pid_t pid = fork();
    int i;

    if(pid == 0)
    {
        printf("child is running\n");
        sleep(2);
        printf("child will end\n");
    }
    else
    {
        sleep(1);
        printf("parent is running\n");
        sleep(10);
        printf("sleep 10s over\n");
        sleep(5);
        printf("sleep 5s over\n");
    }

    exit(0);
}
