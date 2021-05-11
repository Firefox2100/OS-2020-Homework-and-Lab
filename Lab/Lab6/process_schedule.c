#include "process_schedule.h"

int main(int argc, char *argv[])
{
    char select;
    init_pcb_table();
    bool end = false;

    while (!end)
    {
        printf("|----------MAIN    MENU-------------|\n");
        printf("|  1:first come first served        |\n");
        printf("|  2:round robin                    |\n");
        printf("|  3:shrotest job first             |\n");
        printf("|  4:priority scheduling            |\n");
        printf("|  5:create a process               |\n");
        printf("|  6:exit                           |\n");
        printf("|-----------------------------------|\n");
        printf("select a function(1~6):");
        do
        {
            select = getchar();
        } while (!(('1' <= select && select <= '6')));
        switch (select)
        {
        case '1':
            FCFS();
            break;
        case '2':
            RR();
            break;
        case '3':
            SJF();
            break;
        case '4':
            PS();
            break;
        case '5':
            create_process();
            break;
        case '6':
            printf("\n");
            end = true;
        }
        printf("press any key to continue.\n");
        getchar();
    }
    return 0;
}

void init_pcb_table()
{
    int i = 0;
    pcb_free = &pcb_table[0];
    pcb_table[MAX_PROCESS - 1].next = NULL;
    pcb_table[MAX_PROCESS - 1].process_number = 0;
    pcb_table[MAX_PROCESS - 1].process_start_moment = 0;
    pcb_table[MAX_PROCESS - 1].process_burst_time = 0;
    pcb_table[MAX_PROCESS - 1].process_time_slice = 0;
    pcb_table[MAX_PROCESS - 1].process_priority = 0;
    strcpy(pcb_table[MAX_PROCESS - 1].process_name, "");
    for (i = 0; i < MAX_PROCESS - 1; i++)
    {
        pcb_table[i].next = &pcb_table[i + 1];
        pcb_table[i].process_number = 0;
        pcb_table[i].process_start_moment = 0;
        pcb_table[i].process_burst_time = 0;
        pcb_table[i].process_time_slice = 0;
        pcb_table[i].process_priority = 0;
        strcpy(pcb_table[i].process_name, "");
    }
}

void FCFS()
{
    printf("|--------------|--------------|--------------|-----------------|\n");
    printf("|  process     | burst time   | waiting time | turnaround time |\n");
    printf("|--------------|--------------|--------------|-----------------|\n");

    PCB *p;

    int i;

    int time = 0;
    float wtime = 0;
    float ttime = 0;

    if (pcb_free == &pcb_table[0])
    {
        printf("PCB table is empty,no process to run.\n");
    }

    for (i = 0; i < process_number; i++)
    {
        p = &pcb_table[i];

        printf("|   %s       |    %d     |    %d     |    %d     |\n", p->process_name, p->process_burst_time, time - p->process_start_moment, time - p->process_start_moment + p->process_burst_time);

        wtime += time - p->process_start_moment;
        ttime += time - p->process_start_moment + p->process_burst_time;
        time += p->process_burst_time;
    }

    printf("Average waiting time = %f\n", wtime / (float)i);
    printf("Average turnaround time = %f\n", ttime / (float)i);
}

void RR()
{
    printf("|--------------|--------------|--------------|----------------|-----------------|\n");
    printf("|  process     | burst time   | waiting time | remaining time | turnaround time |\n");
    printf("|--------------|--------------|--------------|----------------|-----------------|\n");

    PCB *p;

    int i = 0;

    int time = 0;
    float wtime = 0;
    float ttime = 0;

    if (pcb_free == &pcb_table[0])
    {
        printf("PCB table is empty,no process to run.\n");
    }

    pcb_ready = malloc(sizeof(PCB) * MAX_PROCESS);
    memcpy(pcb_ready, pcb_table, sizeof(PCB) * MAX_PROCESS);
    p = pcb_ready;

    pcb_ready[i].next = &pcb_ready[i + 1];

    for (i = 1; i < process_number - 1; i++)
    {
        pcb_ready[i].next = &pcb_ready[i + 1];
        pcb_ready[i + 1].prev = &pcb_ready[i];
    }

    pcb_ready[process_number - 1].next = &pcb_ready[0];
    pcb_ready[0].prev = &pcb_ready[process_number - 1];

    while (p->next != p)
    {
        if (p->process_burst_time - p->process_time_slice < 2)
        {
            p->process_time_slice += p->process_burst_time;
            printf("|   %s       |    %d     |    %d     |    %d     |    %d     |\n", p->process_name, p->process_burst_time, time - p->process_time_slice - p->process_start_moment, p->process_burst_time - p->process_time_slice, time - p->process_start_moment);
            time += 1;
        }
        else
        {
            p->process_time_slice += 2;

            printf("|   %s       |    %d     |    %d     |    %d     |    %d     |\n", p->process_name, p->process_burst_time, time - p->process_time_slice - p->process_start_moment, p->process_burst_time - p->process_time_slice, time - p->process_start_moment);

            time += 2;
        }

        if (p->process_burst_time - p->process_time_slice == 0)
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }

        p = p->next;
    }
}

void SJF()
{
    printf("|--------------|--------------|--------------|-----------------|\n");
    printf("|  process     | burst time   | waiting time | turnaround time |\n");
    printf("|--------------|--------------|--------------|-----------------|\n");

    PCB *p;
    PCB *t;

    int i = 0;
    int temp;

    int time = 0;
    float wtime = 0;
    float ttime = 0;

    if (pcb_free == &pcb_table[0])
    {
        printf("PCB table is empty,no process to run.\n");
    }

    pcb_ready = malloc(sizeof(PCB) * MAX_PROCESS + 1);
    memcpy(pcb_ready + sizeof(PCB), pcb_table, sizeof(PCB) * MAX_PROCESS);
    p = pcb_ready;

    pcb_ready[i].next = &pcb_ready[i + 1];

    for (i = 2; i < process_number; i++)
    {
        pcb_ready[i].next = &pcb_ready[i + 1];
        pcb_ready[i + 1].prev = &pcb_ready[i];
    }

    for (i = 1; i < process_number + 1; i++)
    {
        p = pcb_ready;
        temp = 999;

        while (p->next != NULL)
        {
            if (p->process_burst_time < temp && p->process_start_moment <= time)
            {
                t = p;
                temp = p->process_burst_time;
            }
        }
        p = t;
        printf("|   %s       |    %d     |    %d     |    %d     |\n", p->process_name, p->process_burst_time, time - p->process_start_moment, time - p->process_start_moment + p->process_burst_time);

        wtime += time - p->process_start_moment;
        ttime += time - p->process_start_moment + p->process_burst_time;
        time += p->process_burst_time;

        p->prev->next = p->next;
        if (p->next != NULL)
            p->next->prev = p->prev;
    }
}

void PS()
{
    printf("|--------------|--------------|--------------|-----------------|\n");
    printf("|  process     | burst time   | waiting time | turnaround time |\n");
    printf("|--------------|--------------|--------------|-----------------|\n");

    PCB *p;
    PCB *t;

    int i = 0;
    int temp;

    int time = 0;
    float wtime = 0;
    float ttime = 0;

    if (pcb_free == &pcb_table[0])
    {
        printf("PCB table is empty,no process to run.\n");
    }

    pcb_ready = malloc(sizeof(PCB) * MAX_PROCESS + 1);
    memcpy(pcb_ready + sizeof(PCB), pcb_table, sizeof(PCB) * MAX_PROCESS);
    p = pcb_ready;

    pcb_ready[i].next = &pcb_ready[i + 1];

    for (i = 2; i < process_number; i++)
    {
        pcb_ready[i].next = &pcb_ready[i + 1];
        pcb_ready[i + 1].prev = &pcb_ready[i];
    }

    for (i = 1; i < process_number + 1; i++)
    {
        p = pcb_ready;
        temp = 999;

        while (p->next != NULL)
        {
            if (p->process_priority < temp && p->process_start_moment <= time)
            {
                t = p;
                temp = p->process_priority;
            }
        }
        p = t;
        printf("|   %s       |    %d     |    %d     |    %d     |\n", p->process_name, p->process_burst_time, time - p->process_start_moment, time - p->process_start_moment + p->process_burst_time);

        wtime += time - p->process_start_moment;
        ttime += time - p->process_start_moment + p->process_burst_time;
        time += p->process_burst_time;

        p->prev->next = p->next;
        if (p->next != NULL)
            p->next->prev = p->prev;
    }
}

PCB *create_process()
{
    PCB *p = pcb_free;
    if (p == NULL)
        return NULL;
    else
    {
        pcb_free = pcb_free->next;

        printf("Please enter the process parameters:\n");
        printf("Process name:");
        scanf("%s", p->process_name);
        printf("Arrive time:");
        scanf("%d", &(p->process_start_moment));
        printf("CPU Burst:");
        scanf("%d", &(p->process_burst_time));
        printf("Time Slice:");
        scanf("%d", &(p->process_time_slice));
        printf("Priority:");
        scanf("%d", &(p->process_priority));

        p->process_number = (process_number + 1) % 100;

        process_number++;

        p->next = NULL;
        p->prev = NULL;

        return p;
    }
}
