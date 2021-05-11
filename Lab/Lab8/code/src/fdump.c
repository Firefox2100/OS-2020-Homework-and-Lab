#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hexdump.h"

int chk_data(char *num);

int main(int argc, char *argv[])
{
    int offset;
    int size;

    if (argc < 4)
    {
        printf("Error: not enough parameters.\n");
        printf("fdump [fileName:char[]] [offset:int] [size:int]\n");
        return 1;
    }
    else if (argc > 4)
    {
        printf("Error: too many parameters.\n");
        printf("fdump [fileName:char[]] [offset:int] [size:int]\n");
        return 1;
    }

    if (chk_data(argv[2]) == 0 | chk_data(argv[3]) == 0)
    {
        printf("Error: input parameter is not a positive integer.\n");
        printf("fdump [fileName:char[]] [offset:int] [size:int]\n");
        return 1;
    }

    sscanf(argv[2], "%d", &offset);
    sscanf(argv[3], "%d", &size);

    FILE *fp;
    if ((fp = fopen(argv[1], "rb")) == NULL)
    {
        printf("Fail to open file!\n");
        exit(0);
    }

    fseek(fp, offset, SEEK_SET);

    unsigned char buffer[size+1];

    int check;

    check=fread(buffer,sizeof(char),size,fp);

    if(check<size)
    {
        if(fp)
        {
            printf("Error: the file is not large enough. EOF encountered.\n");
        }
        else
        {
            printf("Read failed!\n");
            exit(0);
        }
    }

    hexdump(buffer, size);

    fclose(fp);

    return 0;
}

int chk_data(char *num)
{
    int i;
    for (i = 0; num[i]; i++)
    {
        if (num[i] > '9' || num[i] < '0')
        {
            return 0;
        }
    }

    return 1;
}