#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>

off_t min, max, avg;
int nd, nr, nf;
char first[PATH_MAX], last[PATH_MAX];
time_t first_time, last_time;

int search_file(const char *src_dir);

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        printf(" usage: %s [path]\n", argv[0]);
        exit(-11);
    }

    min = 1024 * 1024 * 1024;
    max = 0;
    avg = 0;
    nd = 0;
    nr = 0;
    nf = 0;
    last_time = 0;
    time(&first_time);

    search_file(argv[1]);

    printf("The largest file size is: %d\n", max);
    printf("The smallest file size is: %d\n", min);
    printf("The number of directory is: %d\n", nd);
    printf("The number of regular file is: %d\n", nr);
    printf("The path of the last modfied file is: %s\n", last);
    printf("The path of the first modified file is: %s\n", first);
}

int search_file(const char *src_dir)
{
    struct dirent *entry;

    DIR *dirp = opendir(src_dir);

    char src_buf[1024] = {0};

    struct stat file_info;

    unsigned int fd;

    while (1)
    {
        entry = readdir(dirp);

        if (entry == NULL)
        {
            break;
        }

        if (!strncmp(entry->d_name, ".", 1) || !strncmp(entry->d_name, "..", 2))
        {
            continue;
        }

        sprintf(src_buf, "%s/%s", src_dir, entry->d_name);

        if (entry->d_type == DT_DIR)
        {
            nd++;
            search_file(src_buf);
        }
        else
        {
            fd = open(src_buf, O_RDONLY);
            fstat(fd, &file_info);

            nf++;

            if (file_info.st_size > max)
                max = file_info.st_size;
            if (file_info.st_size < min)
                min = file_info.st_size;

            avg += file_info.st_size;

            if (S_ISREG(file_info.st_mode))
                nr++;

            if (file_info.st_mtime > last_time)
            {
                strcpy(last, src_buf);
                last_time=file_info.st_mtime;
            }
            if (file_info.st_mtime < first_time)
            {
                strcpy(first, src_buf);
                first_time=file_info.st_mtime;
            }
        }
    }

    return 0;
}