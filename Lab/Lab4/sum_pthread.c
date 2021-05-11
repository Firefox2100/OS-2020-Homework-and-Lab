#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h>

struct para
{
    int begin;
    int end;
    int pos;
};

u_int64_t sum[200][8] = {0};

int chk_data(char *num);
void *calc(void *arg);

int main(int argc, char *argv[])
{
    int n, i, threads;
    long long tsum = 0;

    struct timeval start, end;

    if (argc < 3)
    {
        printf("Error: not enough parameters.");
        return 1;
    }
    else if (argc > 3)
    {
        printf("Error: too many parameters.");
        return 1;
    }

    if (chk_data(argv[1]) == 0 | chk_data(argv[2]) == 0)
    {
        printf("Error: input parameter is not a positive integer.");
        return 1;
    }

    sscanf(argv[1], "%d", &threads);
    sscanf(argv[2], "%d", &n);

    pthread_t t[threads + 1];

    struct para interval[threads + 1];

    for (i = 1; i <= threads; i++)
    {
        interval[i].pos = i;
        interval[i].begin = n / threads * (i - 1) + 1;
        interval[i].end = n / threads * i;
    }

    gettimeofday(&start, NULL);

    for (i = 1; i <= threads; i++)
    {
        pthread_create(&(t[i]), NULL, calc, &interval[i]);
    }

    for (i = 1; i <= threads; i++)
    {
        pthread_join(t[i], NULL);
    }

    for (i = 1; i <= threads; i++)
    {
        tsum = tsum + sum[i][0];
    }

    gettimeofday(&end, NULL);

    long long timeuse = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("The sum is %lld, and the time used is %lld.\n", tsum, timeuse);

    return 0;
}

int chk_data(char *num)
{
    int i;
    for (i = 0; num[i]; i++)
    {
        if (num[i] > '9' || num[i] < '0')
        {
            return 0;
        }
    }

    return 1;
}

void *calc(void *arg)
{
    struct para *interval;
    interval = (struct para *)arg;
    
    u_int64_t temp = 0;

    int i;

    for (i = interval->begin; i <= interval->end; i++)
    {
        temp = i * i + temp;
    }

    sum[interval->pos][0] = temp;
}