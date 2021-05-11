#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "abcdefg";
	char read_msg[BUFFER_SIZE]={0};
	pid_t pid;
	int ptoc[2],ctop[2];

	/* create the pipe */
	if (pipe(ptoc) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}

    if (pipe(ctop) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* close the unused end of the pipe */
		close(ptoc[READ_END]);
        close(ctop[WRITE_END]);

        /* write to the pipe */
        write(ptoc[WRITE_END], write_msg, strlen(write_msg)+1);

        close(ptoc[WRITE_END]);

        while(read(ctop[READ_END], read_msg, BUFFER_SIZE))
        {
            printf("parent read %s\n",read_msg);
        }

        close(ctop[READ_END]);
	}
	else { /* child process */
		/* close the unused end of the pipe */
		close(ptoc[WRITE_END]);
        close(ctop[READ_END]);

        int i;

        while(read(ptoc[READ_END], read_msg, BUFFER_SIZE))
        {
            printf("child read %s\n",read_msg);

            for(i=0;read_msg[i];i++)
            {
                if(read_msg[i]>='a'&&read_msg[i]<='z')
                    read_msg[i]-=32;
            }

            write(ctop[WRITE_END], read_msg, strlen(read_msg)+1);
        }

        close(ctop[WRITE_END]);
        close(ptoc[READ_END]);
	}

	return 0;
}
