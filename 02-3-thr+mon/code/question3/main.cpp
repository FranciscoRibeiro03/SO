#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"

pthread_mutex_t counter_mutex;
int counter = 0;

pthread_cond_t cond_par;
pthread_cond_t cond_impar;

static pthread_cond_t cond[2] = { PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER };

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

void *thread_main(void* arg)
{
    int idx = *(int *)arg;

    mutex_lock(&counter_mutex);

    while (counter > 1)
    {
        while (counter % 2 != idx)
            cond_wait(&cond[idx], &counter_mutex);

        printf("[TID:%d; thread] %d\n", gettid(), counter);
        counter--;

        cond_broadcast(&cond[counter % 2]);
    }
    mutex_unlock(&counter_mutex);
    return NULL;
}

int main()
{
    pthread_t thread_par;
    pthread_t thread_impar;

    mutex_init(&counter_mutex, NULL);

    while (counter < 10 || counter > 20)
    {
        counter = read_int("Enter a value between 10 and 20: ");
    }

    int ZERO = 0;
    int ONE = 1;

    thread_create(&thread_par, NULL, thread_main, (void *)&ZERO);
    thread_create(&thread_impar, NULL, thread_main, (void *)&ONE);

    thread_join(thread_par, NULL);
    thread_join(thread_impar, NULL);

    printf("[TID:%d; main]   valor final: %d\n", gettid(), counter);
    printf("[TID:%d; main]   done\n", gettid());
}
