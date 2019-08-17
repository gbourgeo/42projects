/*
  This program will print its code source in a file only using macros.
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define WRITE dprintf(fd, str, 10, 34, str);close(fd);return 0;
#define OPEN int fd = open("Grace_kid.c",O_CREAT|O_TRUNC|O_WRONLY,0644); if (fd < 0) return -1;
#define MAIN int main(void){ OPEN char*str="/*%1$c  This program will print its code source in a file only using macros.%1$c*/%1$c#include <stdio.h>%1$c#include <fcntl.h>%1$c#include <unistd.h>%1$c#define WRITE dprintf(fd, str, 10, 34, str);close(fd);return 0;%1$c#define OPEN int fd = open(%2$cGrace_kid.c%2$c,O_CREAT|O_TRUNC|O_WRONLY,0644); if (fd < 0) return -1;%1$c#define MAIN int main(void){ OPEN char*str=%2$c%s%2$c;WRITE}%1$cMAIN%1$c";WRITE}
MAIN
