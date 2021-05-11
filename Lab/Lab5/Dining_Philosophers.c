#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t chopsticks[5];

sem_t diner;

struct para
{
    int number;
};

void *philosopher(void *arg);

int main()
{
    int i;
    pthread_mutex_init(&(chopsticks[0]), NULL);
    pthread_mutex_init(&(chopsticks[1]), NULL);
    pthread_mutex_init(&(chopsticks[2]), NULL);
    pthread_mutex_init(&(chopsticks[3]), NULL);
    pthread_mutex_init(&(chopsticks[4]), NULL);
    sem_init(&diner, 0, 4);

    pthread_t philosophers[5];

    struct para phi[5];

    for (i = 0; i < 5; i++)
    {
        phi[i].number = i;
    }

    for (i = 1; i < 5; i++)
    {
        pthread_create(&(philosophers[i]), NULL, philosopher, &phi[i]);
    }

    while (1)
        ;
}

void *philosopher(void *arg)
{
    struct para *phi;
    phi = (struct para *)arg;

    while (1)
    {
        sem_wait(&diner);
        pthread_mutex_lock(&(chopsticks[phi->number]));
        pthread_mutex_lock(&(chopsticks[(phi->number + 1) % 5]));

        printf("Philosopher %d is dining.\n", phi->number);
        srand(time(0));
        usleep(rand() % 200);

        pthread_mutex_unlock(&(chopsticks[phi->number]));
        pthread_mutex_unlock(&(chopsticks[(phi->number + 1) % 5]));
        sem_post(&diner);

        printf("Philosopher %d is thinking.\n", phi->number);
        usleep(rand() % 200);
    }
}
