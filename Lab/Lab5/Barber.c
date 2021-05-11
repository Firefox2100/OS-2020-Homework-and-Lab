#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t seats[5];
pthread_mutex_t serving;

struct para
{
    int number;
};

void *barber(void *arg);
void *customer(void *arg);

int main()
{
    pthread_mutex_init(&seats[0], NULL);
    pthread_mutex_init(&seats[1], NULL);
    pthread_mutex_init(&seats[2], NULL);
    pthread_mutex_init(&seats[3], NULL);
    pthread_mutex_init(&seats[4], NULL);

    int i;

    pthread_t bar;
    pthread_t cus[1000];

    struct para num[1000];

    for (i = 0; i < 1000; i++)
    {
        num[i].number = i;
    }

    pthread_create(&bar, NULL, barber, NULL);

    for (i = 0; i < 1000; i++)
    {
        sleep(rand() % 5);
        pthread_create(&cus[i], NULL, customer, &num[i]);
    }

    sleep(30);
    return 0;
}

void *barber(void *arg)
{
    while (1)
    {
        sleep(3);
        pthread_mutex_unlock(&(serving));
    }
}

void *customer(void *arg)
{
    struct para *num;
    num = (struct para *)arg;

    if (pthread_mutex_trylock(&(seats[4])) != 0)
    {
        printf("Line full, customer %d leaving.\n", num->number);
    }
    else
    {
        printf("Customer %d entering.\n", num->number);
        pthread_mutex_lock(&(seats[3]));
        pthread_mutex_unlock(&(seats[4]));
        pthread_mutex_lock(&(seats[2]));
        pthread_mutex_unlock(&(seats[3]));
        pthread_mutex_lock(&(seats[1]));
        pthread_mutex_unlock(&(seats[2]));
        pthread_mutex_lock(&(seats[0]));
        pthread_mutex_unlock(&(seats[1]));

        printf("Customer %d will be served.\n", num->number);

        pthread_mutex_lock(&(serving));
        pthread_mutex_unlock(&(seats[0]));

        printf("Customer %d served.\n", num->number);
    }
}
