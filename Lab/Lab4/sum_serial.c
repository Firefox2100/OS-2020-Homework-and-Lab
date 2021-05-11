#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int chk_data(char *num);

int main(int argc, char *argv[])
{
    int n, i;

    long long sum = 0;

    struct timeval start, end;

    if (argc < 2)
    {
        printf("Error: not enough parameters.");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Error: too many parameters.");
        return 1;
    }

    if (chk_data(argv[1]) == 0)
    {
        printf("Error: input parameter is not a positive integer.");
        return 1;
    }

    sscanf(argv[1], "%d", &n);

    gettimeofday(&start, NULL);

    for (i = 1; i <= n; i++)
    {
        sum = sum + i * i;
    }

    gettimeofday(&end, NULL);

    long long timeuse = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("The sum is %lld, and the time used is %lld", sum, timeuse);

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