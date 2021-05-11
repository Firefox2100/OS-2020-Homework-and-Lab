#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void)
{
    char command[MAX_LINE];
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1;           /* flag to determine when to exit program */
    int flag = 0;
    char *token;
    int i, status;
    pid_t pid;

    while (should_run)
    {
        printf("\n os>");
        fflush(stdout);

        i = 0;
        flag = 0;

        gets(command);

        token = strtok(command, " ");

        while (token != NULL)
        {
            if (!strcmp(token,"&"))
                flag = 1;
            else
                args[i] = token;

            token = strtok(NULL, " ");

            i++;
        }

        args[i]=NULL;

        if(!strcmp(args[0],"exit"))
            break;

        pid = fork();

        if (pid == -1)
        {
            printf("Error: could not creat a child process");
        }
        else if (pid == 0)
        { // Child
            execvp(args[0], args);
            exit(0);
        }
        else
        { // Parent
            if(!flag)
                wait(&status);
        }
    }
    return 0;
}