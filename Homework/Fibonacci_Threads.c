#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int n = 0;          //Global variable to store the user command input
int fib[500] = {0,1}; //Global variable to store the generated Fibonacci sequence

int chk_data(char *num);
void *fibgen(void *arg);

int main(int argc, char *argv[])
{
    int i;

    if(argc<2)
    {
        printf("Error: not enough parameters.");
        return 1;
    }
    else if(argc>2)
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

    pthread_t t;
    int rtn;
    void *joinrtn;

    rtn = pthread_create(&t, NULL, fibgen, NULL);

    if (rtn != 0)
    {
        printf("Error: could not create new thread.\n");
        return -1;
    }

    rtn = pthread_join(t, joinrtn);

    if (rtn != 0)
    {
        printf("Error: could not join created thread.\n");
        return -1;
    }

    for (i = 0; i < n; i++)
        printf("%d ", fib[i]);

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

void *fibgen(void *arg)
{
    int i;
    if (n > 2)
        for (i = 2; i < n; i++)
            fib[i] = fib[i - 1] + fib[i - 2];
    
    return ((void *)0);
}
