#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

  // pointer to file name string
  char *name;

  // allocate tm structure to store retrieved time
  struct tm time;

  // allocate space to hold a string with retrieved time (ASCII text)
  char asctime_str[35];

  // container for complete set of file permission bits (binary)
  unsigned int mode;

  // container for the three bits of user permissions
  unsigned int umode;

  // container for the three bits of group permissions
  unsigned int gmode;

  // container for the three bits of owner permission
  unsigned int omode;

  // human readable file permissions (ASCII text)
  char perm_bits_str[] = "---------";

  // file descriptor
  unsigned int fd;

  // structure to contain the result of the fstat call (info on this file)
  struct stat file_info; //= malloc(sizeof(struct stat));

  // structure to contain the result of the vfstat call (info on file system)
  struct statvfs fs_info; //= malloc(sizeof(struct statvfs));

  // used to save the return value of realpath
  char resolved_path[PATH_MAX];
  char *ret_path;

  // check number of arguments for appropriate usage
  if (2 != argc)
  {
    printf(" usage: %s [file_name]\n", argv[0]);
    exit(-11);
  }

  // post-condition: argv[1] contains name of file to use

  // try to open file
  // todo open file to get filedescriptor
  //

  fd = open(argv[1], O_RDONLY);

  if (-1 == fd)
  {
    perror("Failed to open read only file - ");
    exit(-1);
  }

  // use fstatvfs to learn details about the file system
  if (fstatvfs(fd, &fs_info) == 0)
  {
    printf("== FILE SYSTEM INFO ============================\n");
    printf(" file system fstatvfs() call successful\n");
    printf(" file system block size: %lu\n", fs_info.f_bsize);
    printf(" max. file name length: %lu\n", fs_info.f_namemax);
  }
  else
  {
    printf("%s: File system fstatvfs call failed\n", argv[0]);
    exit(-1);
  }

  // post-condition: maximum length of file name string is known

  // use calloc to allocate space for file name string
  name = calloc(fs_info.f_namemax, 1);

  if (NULL == name)
  {
    perror("Problem in calloc - ");
    exit(-1);
  }

  // copy file name into name variable using secure version of string copy
  strncpy(name, argv[1], fs_info.f_namemax);

  // use fstat to get information on specific file
  if (fstat(fd, &file_info) == 0)
  {
    printf("\n== FILE INFO ============================\n");
    printf(" file fstat() call successful\n");

    // mode comes from the lower 9 bits in file_info.st_mode
    mode = file_info.st_mode & 0x1FF;

    printf(" file protection bits = 0%o\n", mode);

    // umode comes from the high 3 bits in mode
    umode = mode >> 6;

    // gmode comes from the middle 3 bits in mode
    // TO-DO
    gmode = (mode >> 3) % 16;

    // omode comes from the low 3 bits in mode
    //TO-DO
    omode = mode % 16;

    // once you have set umode, gmode, and omode, the code below
    // will construct the right string for you and display it

    // construct string with file protection information
    if (umode & 0x4)
      perm_bits_str[0] = 'r';
    if (umode & 0x2)
      perm_bits_str[1] = 'w';
    if (umode & 0x1)
      perm_bits_str[2] = 'x';

    if (gmode & 0x4)
      perm_bits_str[3] = 'r';
    if (gmode & 0x2)
      perm_bits_str[4] = 'w';
    if (gmode & 0x1)
      perm_bits_str[5] = 'x';

    if (omode & 0x4)
      perm_bits_str[6] = 'r';
    if (omode & 0x2)
      perm_bits_str[7] = 'w';
    if (omode & 0x1)
      perm_bits_str[8] = 'x';

    printf(" file protection string = %s\n", perm_bits_str);

    printf(" file protection mode (u:g:o) = %o:%o:%o\n",
           umode, gmode, omode);

    //struct passwd stuff = malloc(sizeof(struct passwd));
    //struct passwd *pwd = malloc(sizeof(struct passwd));
    struct passwd *pwd;
    //struct group *gp = malloc(sizeof(struct group));
    struct group *gp;

    // TO-DO: man getpwuid
    pwd = getpwuid(file_info.st_uid);
    printf(" owner user name = %s\n", pwd->pw_name);
    // TO-DO: man getgrgid
    gp = getgrgid(file_info.st_gid);
    printf(" owner group name = %s\n", gp->gr_name);

    // Testing the Type of a File
    // All of the symbols listed in this section are defined in the header file sys/stat.h. for example : int S_ISDIR (mode_t m)
    // TO-DO: print "mode = x", where x may be:
    // "regular file"
    // "directory"
    // "character device"
    // "block device"
    // "symbolic link"
    // "socket"
    // "fifo"
    // "unknown"

    //printf(" mode = regular file\n");
    if(S_ISREG(file_info.st_mode))
      printf(" mode = regular file\n");
    else if(S_ISDIR(file_info.st_mode))
      printf(" mode = directory\n");
    else if(S_ISCHR(file_info.st_mode))
      printf(" mode = character device\n");
    else if(S_ISBLK(file_info.st_mode))
      printf(" mode = block device\n");
    else if(S_ISLNK(file_info.st_mode))
      printf(" mode = symbolic link\n");
    else if(S_ISSOCK(file_info.st_mode))
      printf(" mode = socket\n");
    else if(S_ISFIFO(file_info.st_mode))
      printf(" mode = fifo\n");
    else
      printf(" mode = unknown\n");

    ret_path = realpath(name, resolved_path);
    if (NULL != ret_path)
      printf(" absolute path = %s\n", ret_path);
    else
    {
      perror(" couldn't resolve path");
      exit(-1);
    }

    // fill in the time the last write was made to file
    // TO-DO

    struct tm *mtime=localtime(&(file_info.st_mtime));
    printf(" time of last modification: %s",asctime(mtime));

    struct tm *atime=localtime(&(file_info.st_atime));
    printf(" time of last access: %s",asctime(atime));

    struct tm *ctime=localtime(&(file_info.st_ctime));
    printf(" time of status change: %s",asctime(ctime));

    fflush(stdout);

    close(fd);
    exit(0);
  }
  else
    printf(" fstat call failed\n");

  return 0;
}
