#include "allocator.h"

#define TOTAL_SIZE 1000
#define MAX_ALLOCATION 20

int main()
{
    //void * ptr[MAX_ALLOCATION];
    allocator_init(TOTAL_SIZE);

    printf("The total size of memory is %d\n", TOTAL_SIZE);

    showFreeList();
    showAllocatedList();

    void *ptr1=allocateBestFit(500);

    showFreeList();
    showAllocatedList();
    
    deallocate(ptr1);

    showFreeList();
    showAllocatedList();

    void *ptr2=allocateFirstFit(300);

    showFreeList();
    showAllocatedList();

    deallocate(ptr2);

    void *ptr3=allocateWorstFit(250);

    showFreeList();
    showAllocatedList();

    deallocate(ptr3);

    showFreeList();
    showAllocatedList();

    return 0;
}