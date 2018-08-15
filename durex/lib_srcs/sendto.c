#define _GNU_SOURCE
#include<stdio.h>
#include<dlfcn.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
static ssize_t (*original_sendto)(int,const void*,size_t,int,const struct sockaddr*,socklen_t)=NULL;
ssize_t sendto(int sockfd,const void*buf, size_t len, int flags,const struct sockaddr*dest_addr, socklen_t addrlen){
if(original_sendto==NULL){original_sendto=dlsym(RTLD_NEXT,"sendto");if(original_sendto==NULL){return -1;}}
if(!strcmp(inet_ntoa(((struct sockaddr_in*)dest_addr)->sin_addr),"127.0.0.1")){if(ntohs(((struct sockaddr_in*)dest_addr)->sin_port)==4242){for(int i=0;i<len;i++){printf("%02x.",*((u_char*)buf+i));}printf("\n");}}
return original_sendto(sockfd,buf,len,flags,dest_addr,addrlen);}
