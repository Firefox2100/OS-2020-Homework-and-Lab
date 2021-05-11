#include <unistd.h> // need this for fork
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> // need this for printf and fflush
#include <stdlib.h>

int i = 10;
double x = 3.14159;
int pid;

int main(int argc, char *argv[])
{

    int j = 2;
    double y = 0.12345;

    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    if (pid > 0)
    {
        int status;

        // parent code
        printf("parent process -- pid= %d\n", getpid());
        fflush(stdout);

        i = 20;
        y = 0.78912;
        x = 1.428571;

        printf("parent sees: i= %d, x= %lf\n", i, x);
        fflush(stdout);
        printf("parent sees: j= %d, y= %lf\n", j, y);
        fflush(stdout);

        wait(&status);
    }
    else
    {
        // child code
        printf("child process -- pid= %d, ppid= %d\n", getpid(), getppid());
        fflush(stdout);
        printf("child sees: i= %d, x= %lf\n", i, x);
        fflush(stdout);
        printf("child sees: j= %d, y= %lf\n", j, y);
        fflush(stdout);
    }

    return (0);
}
