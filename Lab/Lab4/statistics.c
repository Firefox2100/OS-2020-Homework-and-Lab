#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int n, avg, min, max;

int num[200];

int chk_data(char *num);
void *avggen(void *arg);
void *mingen(void *arg);
void *maxgen(void *arg);

int main(int argc, char *argv[])
{

    int i;

    n = argc - 1;

    if (argc < 2)
    {
        printf("Error: not enough parameters. At least one integer is expected");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        if (chk_data(argv[i]) == 0)
        {
            printf("Error: the %d th input parameter is not a positive integer.", i);
            return 1;
        }

        sscanf(argv[i], "%d", &(num[i - 1]));
    }

    pthread_t t1, t2, t3;
    int rtn1, rtn2, rtn3;

    rtn1 = pthread_create(&(t1), NULL, avggen, NULL);
    rtn2 = pthread_create(&(t2), NULL, mingen, NULL);
    rtn3 = pthread_create(&(t3), NULL, maxgen, NULL);

    if ((rtn1 != 0) | (rtn2 != 0) | (rtn2 != 0))
    {
        printf("Error: could not create new thread.\n");
        return -1;
    }

    rtn1 = pthread_join(t1, NULL);
    rtn2 = pthread_join(t2, NULL);
    rtn3 = pthread_join(t3, NULL);

    if ((rtn1 != 0) | (rtn2 != 0) | (rtn2 != 0))
    {
        printf("Error: could not join created thread.\n");
        return -1;
    }

    printf("The average value is %d\n", avg);
    printf("The minimum value is %d\n", min);
    printf("The maximum value is %d\n", max);

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

void *avggen(void *arg)
{
    int i, sum = 0;

    for (i = 0; i < n; i++)
    {
        sum += num[i];
    }

    avg = sum / n;
}

void *mingen(void *arg)
{
    int i;

    min = num[0];

    for (i = 0; i < n; i++)
    {
        if (num[i] < min)
            min = num[i];
    }
}

void *maxgen(void *arg)
{
    int i;

    max = num[0];

    for (i = 0; i < n; i++)
    {
        if (num[i] > max)
            max = num[i];
    }
}
