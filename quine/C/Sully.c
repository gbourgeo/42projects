#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
char* my_itoa(char*file,int i){int nb=i;int len=1;while(i>9){len++;i/=10;}while(len-->0){file[len]=nb%10+'0';nb/=10;}return file;}
int create(char*file,int i){int fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);if(fd<0)return 1;
char*str="#include<stdio.h>%c#include<fcntl.h>%c#include<unistd.h>%c#include<stdlib.h>%c#include<string.h>%c#include<sys/stat.h>%cchar* my_itoa(char*file,int i){int nb=i;int len=1;while(i>9){len++;i/=10;}while(len-->0){file[len]=nb%%10+'0';nb/=10;}return file;}%cint create(char*file,int i){int fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,0644);if(fd<0)return 1;%cchar*str=%c%s%c;%cdprintf(fd, str, 10,10,10,10,10,10, 10, 10, 34,str,34,10,10,10, 10,34,34,10, i,10, 10, 34,34,10, 10, 34,34,34,34,10, 10, 34,34,10, 10, 34,34,34,34,34,34,10, 10);%cclose(fd);return 0;}%cint main(void){%cchar *sully=%cSully_%c;%cint i=%d; if (i<=0||i>9999) return 0;%cchar itoa[11]={0};my_itoa(itoa,i);%cchar file[20];strncpy(file,sully,20);strcat(file,itoa);strcat(file,%c.c%c);if(create(file,i)) return 1;%cchar out[20];strncpy(out,sully,20);strcat(out,itoa);%cchar cmd[100];strncpy(cmd,%cgcc -Wall -Werror -Wextra -o %c,100);strcat(cmd,out);strcat(cmd, %c %c);strcat(cmd, file);%csystem(cmd);%cif(i){my_itoa(itoa,i-1);strncpy(file,sully,20);strcat(file,itoa);strcat(file,%c.c%c);if(create(file,i-1)) return 1;%cstrncpy(out,sully,20);strcat(out,itoa);%cstrncpy(cmd,%cgcc -Wall -Werror -Wextra -o %c,100);strcat(cmd,out);strcat(cmd, %c %c);strcat(cmd, file);strcat(cmd, %c && ./%c);strcat(cmd,out);%csystem(cmd);}return 0;}%c";
dprintf(fd, str, 10,10,10,10,10,10, 10, 10, 34,str,34,10,10,10, 10,34,34,10, i,10, 10, 34,34,10, 10, 34,34,34,34,10, 10, 34,34,10, 10, 34,34,34,34,34,34,10, 10);
close(fd);return 0;}
int main(void){
char *sully="Sully_";
int i=5; if (i<=0||i>9999) return 0;
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
