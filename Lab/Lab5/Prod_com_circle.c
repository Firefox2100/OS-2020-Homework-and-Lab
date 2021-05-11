#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5

int chk_data(char *num);
void *producer(void *arg);
void *consumer(void *arg);

struct node
{
    int num;
    struct node *next;
} * start, *end;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int main(int argc, char *argv[])
{
    int num_prod, num_cons, sleep_time;
    int i;

    if (argc < 4)
    {
        printf("Error: not enough parameters.");
        return 1;
    }
    else if (argc > 4)
    {
        printf("Error: too many parameters.");
        return 1;
    }

    if (chk_data(argv[1]) == 0 | chk_data(argv[2]) == 0 | chk_data(argv[3]) == 0)
    {
        printf("Error: input parameter is not a positive integer.");
        return 1;
    }

    sscanf(argv[1], "%d", &num_prod);
    sscanf(argv[2], "%d", &num_cons);
    sscanf(argv[2], "%d", &sleep_time);

    struct node *current;
    current = malloc(sizeof(struct node));

    start = current;

    for (i = 0; i < BUFFER_SIZE - 1; i++)
    {
        current->next = malloc(sizeof(struct node));
        current = current->next;
    }

    current->next = start;
    end = start;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    srand(time(0));

    pthread_t pro[num_prod];
    pthread_t con[num_cons];

    for (i = 0; i < num_prod; i++)
    {
        pthread_create(&pro[i], NULL, producer, NULL);
    }

    for (i = 0; i < num_cons; i++)
    {
        pthread_create(&con[i], NULL, consumer, NULL);
    }

    usleep(sleep_time);

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

int insert_item(int item)
{
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    end->num=item;
    end=end->next;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

int remove_item(int *item)
{
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    *item = start->num;
    start=start->next;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

void *producer(void *param)
{
    int r;

    while (1)
    {
        usleep(rand() % 200);

        r = rand();

        printf("Producer produced %d.\n", r);

        if (insert_item(r))
            printf("Error: producer failed to insert item.\n");
    }
}

void *consumer(void *param)
{
    int r;

    while (1)
    {
        usleep(rand() % 200);

        if (remove_item(&r))
            printf("Error: consumer failed to consume item.\n");
        else
            printf("Consumer consumed %d.\n", r);
    }
}
