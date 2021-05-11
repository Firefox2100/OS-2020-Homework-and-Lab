#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 250

int main()
{
    char write_msg[BUFFER_SIZE];
	char read_msg[BUFFER_SIZE];

    int fd;
    char *myfifo="/tmp/fifo";

    while(1)
    {
        fgets(write_msg,BUFFER_SIZE,stdin);

        fd=open(myfifo,O_WRONLY);

        write(fd, write_msg, strlen(write_msg)+1);

        if(!strcmp(write_msg,"end"))
        {
            close(fd);
            printf("End sent by user. Terminated.");
            break;
        }

        close(fd);

        fd=open(myfifo,O_RDONLY);

        read(fd,read_msg,BUFFER_SIZE);

        printf("Client received: %s\n",read_msg);

        close(fd);
    }

    return 0;
}