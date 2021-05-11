#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>

#define BUFFER_SIZE 2500
#define READ_END 0
#define WRITE_END 1

int main(void)
{
    char read_msg[BUFFER_SIZE];
    pid_t pid;
    int fd[2];

    /* create the pipe */
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    /* now fork a child process */
    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0)
    { /* parent process */
        /* close the unused end of the pipe */
        close(fd[WRITE_END]);

        /* read from the pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("parent read %s\n", read_msg);

        /* close the read end of the pipe */
        close(fd[READ_END]);
    }
    else
    { /* child process */
        /* close the unused end of the pipe */
        close(fd[READ_END]);

        /* relocate the standard output*/
        dup2(fd[WRITE_END], 1);

        /* execute the command */
        system("ls -a");

        /* close the write end of the pipe */
        close(fd[WRITE_END]);

        exit(0);
    }

    return 0;
}
