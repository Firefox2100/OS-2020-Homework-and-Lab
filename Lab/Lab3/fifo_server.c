#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 250

char* strrev(char* s);

int main()
{
    char *write_msg;
	char read_msg[BUFFER_SIZE];

    int fd;
    char *myfifo="/tmp/fifo";

    mkfifo(myfifo,0644);

    while(1)
    {
        fd=open(myfifo,O_RDONLY);

        read(fd,read_msg,BUFFER_SIZE);

        if(!strcmp(read_msg,"end"))
        {
            close(fd);
            printf("End sent by client. Terminated.");
            break;
        }
        
        printf("%d",strcmp(read_msg,"end"));
        printf("Server received: %s\n",read_msg);

        close(fd);

        fd=open(myfifo,O_WRONLY);

        write_msg=strrev(read_msg);

        write(fd, write_msg, strlen(write_msg)+1);

        close(fd);
    }

    return 0;
}

char* strrev(char* s)
{
    char* h = s;    
    char* t = s;
    char ch;
    while(*t++){};
    t--;
    t--;

    while(h < t)
    {
        ch = *h;
        *h++ = *t;
        *t-- = ch;
    }
 
    return(s);
}
