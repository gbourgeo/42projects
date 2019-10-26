#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
char* my_itoa(char*file,int i){int nb=i;int len=1;while(i>9){len++;i/=10;}file[len]=0;while(len-->0){file[len]=nb%10+'0';nb/=10;}return file;}
int my_strlen(const char*s){int i=0;if(s)while(s[i])i++;return i;}
int create(char*file,const char*sully,int i){int fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);if(fd<0)return 1;
char*str="#include<stdio.h>%1$c#include<fcntl.h>%1$c#include<unistd.h>%1$c#include<stdlib.h>%1$c#include<string.h>%1$c#include<sys/stat.h>%1$cchar* my_itoa(char*file,int i){int nb=i;int len=1;while(i>9){len++;i/=10;}file[len]=0;while(len-->0){file[len]=nb%%10+'0';nb/=10;}return file;}%1$cint my_strlen(const char*s){int i=0;if(s)while(s[i])i++;return i;}%1$cint create(char*file,const char*sully,int i){int fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);if(fd<0)return 1;%1$cchar*str=%2$c%s%2$c;%1$cdprintf(fd,str,10,34,str,sully,i);close(fd);return 0;}%1$cint exec(char*cmd,const char*sully,char*itoa,int i,int exec){%1$cstrcpy(cmd,sully);strcat(cmd,itoa);strcat(cmd,%2$c.c%2$c);if(create(cmd,sully,i))return 1;%1$cstrcpy(cmd,%2$cgcc -Wall -Werror -Wextra -o %2$c);strcat(cmd,sully);strcat(cmd,itoa);%1$cstrcat(cmd,%2$c %2$c);strcat(cmd,sully);strcat(cmd,itoa);strcat(cmd,%2$c.c%2$c);%1$cif(exec){strcat(cmd,%2$c && ./%2$c);strcat(cmd,sully);strcat(cmd,itoa);}%1$creturn(system(cmd));}%1$cint err(char*cmd){if(cmd)free(cmd);return(1);}%1$cint main(void){%1$cconst char*sully=%2$c%4$s%2$c;%1$cint i=%5$d;%1$cif(i<0)return 1;%1$cchar itoa[11]={0};my_itoa(itoa,i);%1$cchar *cmd=malloc(29+(my_strlen(sully)+my_strlen(itoa))*3+11);if(!cmd)return 1;%1$cif(exec(cmd,sully,itoa,i,0))return err(cmd);%1$cif(i){my_itoa(itoa,i-1);if(exec(cmd,sully,itoa,i-1,1))return err(cmd);}%1$cfree(cmd);return 0;}%1$c";
dprintf(fd,str,10,34,str,sully,i);close(fd);return 0;}
int exec(char*cmd,const char*sully,char*itoa,int i,int exec){
strcpy(cmd,sully);strcat(cmd,itoa);strcat(cmd,".c");if(create(cmd,sully,i))return 1;
strcpy(cmd,"gcc -Wall -Werror -Wextra -o ");strcat(cmd,sully);strcat(cmd,itoa);
strcat(cmd," ");strcat(cmd,sully);strcat(cmd,itoa);strcat(cmd,".c");
if(exec){strcat(cmd," && ./");strcat(cmd,sully);strcat(cmd,itoa);}
return(system(cmd));}
int err(char*cmd){if(cmd)free(cmd);return(1);}
int main(void){
const char*sully="Sully_";
int i=5;
if(i<0)return 1;
char itoa[11]={0};my_itoa(itoa,i);
char *cmd=malloc(29+(my_strlen(sully)+my_strlen(itoa))*3+11);if(!cmd)return 1;
if(exec(cmd,sully,itoa,i,0))return err(cmd);
if(i){my_itoa(itoa,i-1);if(exec(cmd,sully,itoa,i-1,1))return err(cmd);}
free(cmd);return 0;}
