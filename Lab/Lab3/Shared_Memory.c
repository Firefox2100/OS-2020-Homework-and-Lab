#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <wait.h>
#include <string.h>

#define FILE_SIZE 100

int main()
{
    int fd, rtn;
    void *ptr = NULL;

    fd = shm_open("Shared", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd < 0)
    {
        printf("Error: could not open shared memory.\n");
        return 1;
    }

    rtn = ftruncate(fd, FILE_SIZE);

    if (rtn == -1)
    {
        printf("Error: truncate failed.\n");
        return 1;
    }

    int pid;

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0)
    { // parent code
        int status;

        ptr = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, SEEK_SET);

        if (ptr == NULL)
        {
            printf("Error: parent mmap failed.\n");
            wait(&status);
            return 1;
        }

        wait(&status);

        if (status == 0)
        {
            printf("%s\n", ptr);
        }

        rtn = munmap(ptr, FILE_SIZE);

        if (rtn == -1)
        {
            printf("Error: parent munmap failed\n");
            return 1;
        }

        shm_unlink("Shared");
    }
    else
    { // child code
        ptr = mmap(NULL, FILE_SIZE, PROT_WRITE, MAP_SHARED, fd, SEEK_SET);

        if (ptr == NULL)
        {
            printf("Error: child mmap failed.\n");
            exit(1);
        }

        memcpy(ptr, "greeting to parent!", sizeof("greeting to parent!"));

        rtn = munmap(ptr, FILE_SIZE);

        if (rtn == -1)
        {
            printf("Error: child munmap failed\n");
            exit(1);
        }

        exit(0);
    }

    return 0;
}
