#include "allocator.h"
#include <time.h>

#define TOTAL_SIZE 1048576

int chk_data(char *num);

int main(int argc, char *argv[])
{
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

    int algorithm,requests;
    int s;

    sscanf(argv[1], "%d", &algorithm);
    sscanf(argv[2], "%d", &requests);

    allocator_init(TOTAL_SIZE);
    
    srand(time(NULL));

    int r = 0;
    void *p = NULL;

    while(r<requests)
    {
        s=rand()%9900+100;
        p=allocate(s,algorithm);

        deallocate(p);
    }

    int a=average_frag();

    printf("The average fragmentation size is %f.\n",a);

    showFreeList();

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
