#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
char* my_itoa(char*file,int i){int nb=i;int len=1;while(i>9){len++;i/=10;}while(len-->0){file[len]=nb%10+'0';nb/=10;}return file;}
int create(char*file,int i){int fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);if(fd<0)return 1;
char*str="#include<stdio.h>%1$c#include<fcntl.h>%1$c#include<unistd.h>%1$c#include<stdlib.h>%1$c#include<string.h>%1$c#include<sys/stat.h>%1$cchar* my_itoa(char*file,int i){int nb=i;int len=1;while(i>9){len++;i/=10;}while(len-->0){file[len]=nb%%10+'0';nb/=10;}return file;}%1$cint create(char*file,int i){int fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);if(fd<0)return 1;%1$cchar*str=%2$c%s%2$c;%1$cdprintf(fd,str,10,34,str,i);%1$cclose(fd);return 0;}%1$cint main(void){%1$cchar *sully=%2$cSully_%2$c;%1$cint i=%4$d;%1$cif(i<=0||i>9999)return 0;%1$cchar itoa[11]={0};my_itoa(itoa,i);%1$cchar file[20];strncpy(file,sully,20);strcat(file,itoa);strcat(file,%2$c.c%2$c);if(create(file,i)) return 1;%1$cchar out[20];strncpy(out,sully,20);strcat(out,itoa);%1$cchar cmd[100];strncpy(cmd,%2$cgcc -Wall -Werror -Wextra -o %2$c,100);strcat(cmd,out);strcat(cmd, %2$c %2$c);strcat(cmd, file);%1$csystem(cmd);%1$cif(i){my_itoa(itoa,i-1);strncpy(file,sully,20);strcat(file,itoa);strcat(file,%2$c.c%2$c);if(create(file,i-1)) return 1;%1$cstrncpy(out,sully,20);strcat(out,itoa);%1$cstrncpy(cmd,%2$cgcc -Wall -Werror -Wextra -o %2$c,100);strcat(cmd,out);strcat(cmd, %2$c %2$c);strcat(cmd, file);strcat(cmd, %2$c && ./%2$c);strcat(cmd,out);%1$csystem(cmd);}%1$creturn 0;}%1$c";
dprintf(fd,str,10,34,str,i);
close(fd);return 0;}
int main(void){
char *sully="Sully_";
int i=5;
if(i<=0||i>9999)return 0;
char itoa[11]={0};my_itoa(itoa,i);
char file[20];strncpy(file,sully,20);strcat(file,itoa);strcat(file,".c");if(create(file,i)) return 1;
char out[20];strncpy(out,sully,20);strcat(out,itoa);
char cmd[100];strncpy(cmd,"gcc -Wall -Werror -Wextra -o ",100);strcat(cmd,out);strcat(cmd, " ");strcat(cmd, file);
system(cmd);
if(i){my_itoa(itoa,i-1);strncpy(file,sully,20);strcat(file,itoa);strcat(file,".c");if(create(file,i-1)) return 1;
strncpy(out,sully,20);strcat(out,itoa);
strncpy(cmd,"gcc -Wall -Werror -Wextra -o ",100);strcat(cmd,out);strcat(cmd, " ");strcat(cmd, file);strcat(cmd, " && ./");strcat(cmd,out);
system(cmd);}
return 0;}
