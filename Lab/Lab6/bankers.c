#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

pthread_mutex_t mutex;

int f_num = 0;
int s_num = 0;
int t_num = 0;
int mcount = 0;
int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

pthread_t tids[NUMBER_OF_CUSTOMERS];

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

int create_rand(int start, int end)
{
	return start + (int)(rand() / (RAND_MAX + 1.0) * (end - start));
}

void print()
{
	int i, j;
	printf("available:\n");
	for (i = 0; i < NUMBER_OF_RESOURCES; i++)
	{
		printf("%d ", available[i]);
	}
	printf("\nmaximum:\n");
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)
		{
			printf("%d ", maximum[i][j]);
		}
		printf("\n");
	}
	printf("allocation:\n");
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)
		{
			printf("%d ", allocation[i][j]);
		}
		printf("\n");
	}
	printf("need:\n");
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)
		{
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
}

void init()
{
	available[0] = f_num;
	available[1] = s_num;
	available[2] = t_num;

	int i, j;

	pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)
		{
			maximum[i][j] = create_rand(0, available[j] + 1);
			allocation[i][j] = 0;
			need[i][j] = maximum[i][j] - allocation[i][j];
		}
	}

	for (i = 0; i < NUMBER_OF_RESOURCES; i++)
	{
		int sum = 0;
		for (j = 0; j < NUMBER_OF_CUSTOMERS; j++)
		{
			sum += allocation[j][i];
		}

		available[i] -= sum;
	}

	print();
}

int safe()
{
	int work[NUMBER_OF_RESOURCES];
	int i;

	for (i = 0; i < NUMBER_OF_RESOURCES; i++)
	{
		work[i] = available[i];
	}
	
	int finish[NUMBER_OF_CUSTOMERS];

	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		finish[i] = 0;
	}

	while (1)
	{
		int flag = 1;
		for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		{
			if (finish[i] == 0 && need[i][0] <= work[0] && need[i][1] <= work[1] && need[i][2] <= work[2])
			{
				work[0] += need[i][0];
				work[1] += need[i][1];
				work[2] += need[i][2];
				finish[i] = 1;
				flag = 0;
			}
		}

		if (flag == 1)
		{
			break;
		}
	}

	int flag = 1;

	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		if (finish[i] == 0)
		{
			flag = 0;
		}
	}

	if (flag == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void *req(void *arg)
{
	while (1)
	{
		int request[NUMBER_OF_RESOURCES];
		int i;

		int num = *(int *) arg;

		pthread_mutex_lock(&mutex);

		for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		{
			request[i] = create_rand(0, need[num][i] + 1);
		}

		if (request[0] == 0 && request[1] == 0 && request[2] == 0)
		{
			pthread_mutex_unlock(&mutex);
			continue;
		}

		printf("%d request:%d %d %d", num + 1, request[0], request[1], request[2]);

		if (request[0] <= available[0] && request[1] <= available[1] && request[2] <= available[2])
		{
			available[0] -= request[0];
			available[1] -= request[1];
			available[2] -= request[2];
			allocation[num][0] += request[0];
			allocation[num][1] += request[1];
			allocation[num][2] += request[2];
			need[num][0] -= request[0];
			need[num][1] -= request[1];
			need[num][2] -= request[2];

			if (need[num][0] == 0 && need[num][1] == 0 && need[num][2] == 0)
			{
				available[0] += allocation[num][0];
				available[1] += allocation[num][1];
				available[2] += allocation[num][2];
				mcount++;

				if (mcount == NUMBER_OF_CUSTOMERS)
				{
					printf(" complete\n");
					print();
					exit(0);
				}
			}
			if (safe() == 0)
			{
				available[0] += request[0];
				available[1] += request[1];
				available[2] += request[2];
				allocation[num][0] -= request[0];
				allocation[num][1] -= request[1];
				allocation[num][2] -= request[2];
				need[num][0] += request[0];
				need[num][1] += request[1];
				need[num][2] += request[2];

				printf(" unsafe ");
			}
			else
			{
				printf(" safe ");
			}

			printf("available: %d %d %d ", available[0], available[1], available[2]);
			printf(" need: %d %d %d\n", need[num][0], need[num][1], need[num][2]);
		}
		else
		{
			printf("\n");
		}

		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		fprintf(stderr, "Error: not enough parameters.");

		return -1;
	}
	else if (argc>4)
	{
		fprintf(stderr, "Error: too many parameters.");

		return -1;
	}

	if (chk_data(argv[1]) == 0 | chk_data(argv[2]) == 0 | chk_data(argv[3]) == 0)
    {
		fprintf(stderr, "Error: input parameter is not a positive integer.");

        return 1;
    }

	f_num = atoi(argv[1]);
	s_num = atoi(argv[2]);
	t_num = atoi(argv[3]);

	srand((unsigned)time(NULL));

	init();

	if (safe() == 0)
	{
		printf("unsafe at first\n");
		return 0;
	}

	int i;

	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		pthread_t tid;
		tids[i] = tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, req, &i);
	}

	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		pthread_join(tids[i], NULL);
	}

	return 0;
}