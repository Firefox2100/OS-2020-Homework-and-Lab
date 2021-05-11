#include <pthread.h>
#include <stdio.h>
#include  <sys/types.h>

int value = 0;
void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
    pid_t pid;
    pthread_t tid;
    pthread_attr_t attr;
    int myvalue = 5;
    pid = fork();
    if (pid == 0) { /* child process */
        int myval = 5;
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,runner,&myvalue);
        pthread_join(tid,NULL);
        printf("CHILD: value = %d\n",value); /* LINE A */
    }
    else if (pid > 0) { /* parent process */
        myvalue = 10;
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,runner,&myvalue );
        pthread_join(tid,NULL);
        wait(NULL);
        printf("PARENT: value = %d\n",value); /* LINE B */
    }
}


void *runner(void *param) {
        value = *((int*)param) - 1;
        pthread_exit(0);
}