#include "allocator.h"

struct dlist *free_list;
struct dlist *allocated_list;

int allocator_init(size_t size)
{
    free_list = dlist_create();
    allocated_list = dlist_create();

    if (free_list == NULL || allocated_list == NULL)
        return -1;

    struct dnode *ptr1 = dnode_create();
    void *ptr2 = calloc(1, size);

    if (ptr1 == NULL)
        return -1;

    if (ptr2 == NULL)
        return -1;

    dnode_setdata(ptr1, ptr2);
    dnode_setsize(ptr1, size);

    dlist_add_back(free_list, ptr1);

    return 0;
}

void *allocate(size_t size, int typee)
{
    switch (typee)
    {
    case 1:
        return allocateFirstFit(size);
    
    case 2:
        return allocateBestFit(size);
    
    case 3:
        return allocateWorstFit(size);
    
    default:
        return NULL;
    }
}

int deallocate(void *ptr)
{
    struct dnode *n = allocated_list->front;

    while ((n != NULL) && (n->data != ptr))
    {
        n = n->next;
    }

    if (n != NULL)
    {
        if (allocated_list->front == n)
        {
            if (1 == allocated_list->counter)
            {
                allocated_list->front = allocated_list->back = NULL;
            }
            else
            {
                allocated_list->front = allocated_list->front->next;
                allocated_list->front->prev = NULL;
            }

            (allocated_list->counter)--;

            dlist_add_back(free_list, n);

            return 0;
        }
        else if (allocated_list->back == n)
        {
            if (1 == allocated_list->counter)
            {
                allocated_list->front = allocated_list->back = NULL;
            }
            else
            {
                allocated_list->back = allocated_list->back->prev;
                allocated_list->back->next = NULL;
            }

            (allocated_list->counter)--;

            dlist_add_back(free_list, n);

            return 0;
        }
        else
        {
            if (1 == allocated_list->counter)
            {
                dlist_add_back(free_list, n);
                allocated_list->front = allocated_list->back = NULL;
            }
            else
            {
                n->prev->next = n->next;
                n->next->prev = n->prev;
                dlist_add_back(free_list, n);
            }
            (allocated_list->counter)--;

            return 0;
        }
    }

    return -1;
}

void *allocateFirstFit(size_t size)
{
    struct dnode *n = free_list->front;
    void *ret_ptr = NULL;

    while ((n != NULL) && (n->size < size))
    {
        n = n->next;
    }

    if(n==NULL)
        return ret_ptr;

    int original_size = n->size;

    struct dnode *ptr1 = dnode_create();
    void *p1 = calloc(1, size);

    if (ptr1 == NULL)
        return NULL;

    if (p1 == NULL)
        return NULL;

    dnode_setdata(ptr1, p1);
    dnode_setsize(ptr1, size);

    struct dnode *ptr2 = dnode_create();
    void *p2 = calloc(1, original_size - size);

    if (ptr2 == NULL)
        return NULL;

    if (p2 == NULL)
        return NULL;

    dnode_setdata(ptr2, p2);
    dnode_setsize(ptr2, size);

    if (n != NULL)
    {
        if (free_list->front == n)
        {
            dlist_remove_front(free_list);
            dlist_add_back(free_list, ptr2);
            dlist_add_back(allocated_list, ptr1);
            return ret_ptr = ptr1->data;
        }
        else if (free_list->back == n)
        {
            dlist_remove_back(free_list);
            dlist_add_back(free_list, ptr2);
            dlist_add_back(allocated_list, ptr1);
            return ret_ptr = ptr1->data;
        }
        else
        {
            if (1 == free_list->counter)
            {
                free_list->front = free_list->back = NULL;
            }
            else
            {
                n->prev->next = n->next;
                n->next->prev = n->prev;
            }
            (free_list->counter)--;
        }

        dlist_add_back(free_list, ptr2);
        dlist_add_back(allocated_list, ptr1);
        ret_ptr = ptr1->data;
        free(n);
    }

    return ret_ptr;
}

void *allocateBestFit(size_t size)
{
    struct dnode *m = free_list->front;
    struct dnode *n;
    void *ret_ptr = NULL;

    int temp = 65535;

    while (m != NULL)
    {
        if (m->size >= size && m->size < temp)
        {
            n = m;
            temp = m->size;
        }

        m = m->next;
    }

    if(n==NULL)
        return ret_ptr;

    int original_size = n->size;

    struct dnode *ptr1 = dnode_create();
    void *p1 = calloc(1, size);

    if (ptr1 == NULL)
        return NULL;

    if (p1 == NULL)
        return NULL;

    dnode_setdata(ptr1, p1);
    dnode_setsize(ptr1, size);

    struct dnode *ptr2 = dnode_create();
    void *p2 = calloc(1, original_size - size);

    if (ptr2 == NULL)
        return NULL;

    if (p2 == NULL)
        return NULL;

    dnode_setdata(ptr2, p2);
    dnode_setsize(ptr2, size);

    if (n != NULL)
    {
        if (free_list->front == n)
        {
            dlist_remove_front(free_list);
            dlist_add_back(free_list, ptr2);
            dlist_add_back(allocated_list, ptr1);
            return ret_ptr = ptr1->data;
        }
        else if (free_list->back == n)
        {
            dlist_remove_back(free_list);
            dlist_add_back(free_list, ptr2);
            dlist_add_back(allocated_list, ptr1);
            return ret_ptr = ptr1->data;
        }
        else
        {
            if (1 == free_list->counter)
            {
                free_list->front = free_list->back = NULL;
            }
            else
            {
                n->prev->next = n->next;
                n->next->prev = n->prev;
            }
            (free_list->counter)--;
        }

        dlist_add_back(free_list, ptr2);
        dlist_add_back(allocated_list, ptr1);
        ret_ptr = ptr1->data;
        free(n);
    }

    return ret_ptr;
}

void *allocateWorstFit(size_t size)
{
    struct dnode *m = free_list->front;
    struct dnode *n;
    void *ret_ptr = NULL;

    int temp = 0;

    while (m != NULL)
    {
        if (m->size >= size && m->size > temp)
        {
            n = m;
            temp = m->size;
        }

        m = m->next;
    }

    if(n==NULL)
        return ret_ptr;

    int original_size = n->size;

    struct dnode *ptr1 = dnode_create();
    void *p1 = calloc(1, size);

    if (ptr1 == NULL)
        return NULL;

    if (p1 == NULL)
        return NULL;

    dnode_setdata(ptr1, p1);
    dnode_setsize(ptr1, size);

    struct dnode *ptr2 = dnode_create();
    void *p2 = calloc(1, original_size - size);

    if (ptr2 == NULL)
        return NULL;

    if (p2 == NULL)
        return NULL;

    dnode_setdata(ptr2, p2);
    dnode_setsize(ptr2, size);

    if (n != NULL)
    {
        if (free_list->front == n)
        {
            dlist_remove_front(free_list);
            dlist_add_back(free_list, ptr2);
            dlist_add_back(allocated_list, ptr1);
            return ret_ptr = ptr1->data;
        }
        else if (free_list->back == n)
        {
            dlist_remove_back(free_list);
            dlist_add_back(free_list, ptr2);
            dlist_add_back(allocated_list, ptr1);
            return ret_ptr = ptr1->data;
        }
        else
        {
            if (1 == free_list->counter)
            {
                free_list->front = free_list->back = NULL;
            }
            else
            {
                n->prev->next = n->next;
                n->next->prev = n->prev;
            }
            (free_list->counter)--;
        }

        dlist_add_back(free_list, ptr2);
        dlist_add_back(allocated_list, ptr1);
        ret_ptr = ptr1->data;
        free(n);
    }

    return ret_ptr;
}

void showFreeList()
{
    int i = 1;
    struct dnode *n = free_list->front;

    if(n==NULL)
    {
        printf("There're no segment in free list.\n");
    }

    while (n != NULL)
    {
        printf("The size of No. %d segment of free list is %d.\n", i, n->size);
        i++;
        n = n->next;
    }
}

void showAllocatedList()
{
    int i = 1;
    struct dnode *n = allocated_list->front;

    if(n==NULL)
    {
        printf("There're no segments in allocated list.\n");
    }

    while (n != NULL)
    {
        printf("The size of No. %d segment of allocated list is %d.\n", i, n->size);
        i++;
        n = n->next;
    }
}

double average_frag()
{
    double i = 0;
    double size=0;
    struct dnode *n = free_list->front;

    if(n==NULL)
    {
        printf("There're no segment in free list.\n");
    }

    while (n != NULL)
    {
        size = size + n->size;
        i++;
        n = n->next;
    }

    return size/i;
}
