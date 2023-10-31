#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"

int read_int(const char *prompt)
{
    int done;
    int ret;
    do
    {
        printf(prompt);
        done = scanf("%d", &ret);
        if (done != 1)
        {
            fprintf(stderr, "ERROR: invalid input!\n");
            scanf("%*s");
        }
    } while (done != 1);
    return ret;
}

void *thread_main(void *arg)
{
    int *n1 = (int *)malloc(sizeof(int));
    if (arg != NULL)
        n1 = ((int *)arg);

    int n2 = 0;
    while (n2 < 10 || n2 > 20)
    {
        n2 = read_int("[thread] Enter a value between 10 and 20: ");
    }

    while (*n1 != n2)
    {
        usleep(500000);
        *n1 = *n1 + 1;
        printf("[thread] %d\n", *n1);
    }
    return NULL;
}

int main()
{
    pthread_t a_thread;
    int n1 = 0;
    while (n1 < 1 || n1 > 9)
    {
        n1 = read_int("[main]   Enter a value between 1 and 9: ");
    }

    thread_create(&a_thread, NULL, thread_main, (void *)&n1);
    thread_join(a_thread, NULL);

    while (n1 != 1)
    {
        usleep(500000);
        n1--;
        printf("[main]   %d\n", n1);
    }

    printf("[main]   done\n");
}