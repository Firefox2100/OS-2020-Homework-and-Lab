#include <unistd.h> // need this for fork
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> // need this for printf and fflush
#include <stdlib.h>

int num = 50;

void ChildProcess(void);  /* child process prototype  */
void ParentProcess(void); /* parent process prototype */

int main(void)
{
    pid_t pid;
    pid = fork();
    printf("The returned pid is %d\n", pid);
    if (pid == -1)
    {
        printf("something went wrong in fork");
        return (-1);
    }
    else if (pid == 0)
        ChildProcess();
    else
        ParentProcess();
        return 0;
}
void ChildProcess(void)
{
    int i;
    int mypid;
    mypid = getpid();
    for (i = 1; i <= num; i++)
        printf("   This line is from child, value = %d\n", i);
    fflush(stdout);
    printf("   *** Child process %d is done ***\n", mypid);
    exit(0);
}
void ParentProcess(void)
{
    int i, status;
    int got_pid, mypid;
    mypid = getpid();
    for (i = 1; i <= num; i++)
        printf("This line is from parent, value = %d\n", i);
    fflush(stdout);
    printf("*** Parent %d is done ***\n", mypid);
    got_pid = wait(&status);
    printf("[%d] bye %d (%d)\n", mypid, got_pid, status);
}