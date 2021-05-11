#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int allocation[5][3];
int max[5][3];
int need[5][3];
int avaliable[3];

bool finished[5] = {false, false, false, false, false};

bool check_avaliable(int n);

int get_avaliable();
int get_allocation();
int get_max();
int calc_need();
int work(int n);

int main()
{
    get_avaliable();
    get_allocation();
    get_max();

    calc_need();

    int i, j;
    int index[5] = {-1, -1, -1, -1, -1};

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (check_avaliable(j) && !finished[j])
            {
                work(j);
                index[i] = j;
                break;
            }
        }
    }

    if (index[4] == -1)
    {
        printf("The system is not safe.\n");
    }
    else
    {
        printf("The system is safe.\n");
        printf("One Safe Sequence is P%d, P%d, P%d, P%d, P%d.\n", index[0], index[1], index[2], index[3], index[4]);
    }

    return 0;
}

int get_avaliable()
{
    printf("Please enter the avaliable amount of three resources, divided by space:\n");
    scanf("%d %d %d", &avaliable[0], &avaliable[1], &avaliable[2]);

    return 0;
}

int get_allocation()
{
    int i = 0;

    for (i = 0; i < 5; i++)
    {
        printf("Please enter the allocated resources of process P%d, divided by space:", i);
        scanf("%d %d %d", &allocation[i][0], &allocation[i][1], &allocation[i][2]);
    }

    return 0;
}

int get_max()
{
    int i = 0;

    for (i = 0; i < 5; i++)
    {
        printf("Please enter the maximum requirement of process P%d, divided by space:", i);
        scanf("%d %d %d", &max[i][0], &max[i][1], &max[i][2]);
    }

    return 0;
}

int calc_need()
{
    int i, j;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 3; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    return 0;
}

bool check_avaliable(int n)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (need[n][i] > avaliable[i])
            return false;
    }

    return true;
}

int work(int n)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        avaliable[i] += allocation[n][i];
    }

    finished[n] = true;

    return 0;
}
