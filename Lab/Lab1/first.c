#include <stdio.h>
#include <stdlib.h>

/* A statically allocated variable */
int var1;

int my_func(int i);

/* A statically allocated, pre-initialized variable */
volatile int stuff = 7;

int main(int argc, char *argv[]) {
    /* A stack allocated variable */
    volatile int i = 0;

    /* Dynamically allocate some stuff */
    volatile char *buf1 = malloc(10);
    /* ... and some more stuff */
    volatile char *buf2 = malloc(10);

    my_func (3);

    printf("static data var1,address: %d\n", &var1);
    
    printf("Heap: data buf1, address: %d\n", buf1);

    return 0;
}

int my_func(int i)
{
    printf("Stack: data i, address: %d\n", &i);
}
