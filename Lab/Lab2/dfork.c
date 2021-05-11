#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void forkChildren(int nChildren);

int main(int argc, char **argv)
{
    int n;

    sscanf(argv[1],"%d",&n);

    forkChildren(n);
    
    return 0;
}

void forkChildren(int nChildren)
{
    pid_t pid = 0;
    int status;
    for (int i = 0; i < nChildren; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        { // child
            printf("I'm a child: %d PID: %d ,my parent pid: %d\n", i, getpid(), getppid());
            break;
        }
        else
        { // Parent
            wait(&status);
        }
    }

    exit(0);
}