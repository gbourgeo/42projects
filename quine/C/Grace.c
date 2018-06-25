/*
  This program will print its code source in a file only using macros.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define WRITE dprintf(fd, str, 10,10,10, 10,10,10, 10,34,34,10, 34,str,34, 10, 10);close(fd);return 0;
#define OPEN int fd = open("Grace_kid.c",O_CREAT|O_TRUNC|O_WRONLY,0644); if (fd < 0) return -1;
#define MAIN int main(void){ OPEN char*str="/*%c  This program will print its code source in a file only using macros.%c*/%c#include <stdio.h>%c#include <fcntl.h>%c#include <unistd.h>%c#define WRITE dprintf(fd, str, 10,10,10, 10,10,10, 10,34,34,10, 34,str,34, 10, 10);close(fd);return 0;%c#define OPEN int fd = open(%cGrace_kid.c%c,O_CREAT|O_TRUNC|O_WRONLY,0644); if (fd < 0) return -1;%c#define MAIN int main(void){ OPEN char*str=%c%s%c;WRITE}%cMAIN%c";WRITE}
MAIN
