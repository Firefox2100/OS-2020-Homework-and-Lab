#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    int i = 0;
    pid_t pid = fork();
    if (pid == -1)
        return 0;
    else if (pid == 0)
    { // Child
        printf("child pid is %d\n", getpid());
        printf("child terminated\n");
    }
    else if (pid > 0)
    { // Parent
        printf("parent pid is %d\n", getpid());
        while (1)
            sleep(100);
    }
    return 0;
}