#include <sys/types.h>
#include <stdio.h>
#include<string.h>
#include <unistd.h>

int chk_data(char *num);

int main(int argc,char** argv)
{
    int n;
    char * temp;
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

    pid_t pid;
    pid = fork();

    if(pid==0)
    {
        while(n!=1)
        {
            printf("%d ",n);
            
            if(n%2==0)
            {
                n=n/2;
            }
            else if (n%2==1)
            {
                n=n*3+1;
            }
        }

        printf("%d",n);
    }
    else if(pid>0)
    {
        wait(NULL);
    }
    
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