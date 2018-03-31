#include <linux/if_ether.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#include "libft.h"
#include "all.h"

/*
struct ip {
#if BYTE_ORDER == LITTLE_ENDIAN 
	u_char	ip_hl:4,		// header length //
		ip_v:4;			// version //
#endif
#if BYTE_ORDER == BIG_ENDIAN 
	u_char	ip_v:4,			// version //
		ip_hl:4;		// header length //
#endif
	u_char	ip_tos;			// type of service //
	short	ip_len;			// total length //
	u_short	ip_id;			// identification //
	short	ip_off;			// fragment offset field //
#define	IP_DF 0x4000			// dont fragment flag //
#define	IP_MF 0x2000			// more fragments flag //
	u_char	ip_ttl;			// time to live //
	u_char	ip_p;			// protocol //
	u_short	ip_sum;			// checksum //
	struct	in_addr ip_src,ip_dst;	// source and dest address //
};
*/
static uint16_t 		checksum (uint16_t *addr, int len)
{
  int count = len;
  register uint32_t sum = 0;
  uint16_t answer = 0;

  // Sum up 2-byte values until none or only one byte left.
  while (count > 1) {
    sum += *(addr++);
    count -= 2;
  }

  // Add left-over byte, if any.
  if (count > 0) {
    sum += *(uint8_t *) addr;
  }

  // Fold 32-bit sum into 16 bits; we lose information by doing this,
  // increasing the chances of a collision.
  // sum = (lower 16 bits) + (upper 16 bits shifted right 16 bits)
  while (sum >> 16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }

  // Checksum is one's compliment of sum.
  answer = ~sum;

  return (answer);
}

int 					construct_packet(t_addr *address, char *packet, int port)
{
	int 				packet_len;
	struct ethhdr 		*eth;
	struct iphdr 		*iph;
	struct udphdr 		*uh;
	char 				*data;
	struct sockaddr_ll 	*mac;
	int 				total_len;
	int 				data_len;

	packet_len = sizeof(*eth) + sizeof(*iph) + sizeof(*uh) + 22;
	ft_memset(packet, 0, packet_len);
	total_len = 0;
	mac = (struct sockaddr_ll *)(&globals.pcap.mac);

	/* Construct ETHERNET header */
	eth = (struct ethhdr *)(packet);
	ft_memset(eth->h_dest, 0xff, ETH_ALEN);
	ft_memcpy(eth->h_source, mac->sll_addr, mac->sll_halen);
	eth->h_proto = htons(ETH_P_IP);
	total_len = sizeof(*eth);

	/* Construct IP header */
	iph = (struct iphdr*)(packet + sizeof(*eth));
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->id = htons(42);
	iph->ttl = 255;
	iph->protocol = IPPROTO_UDP;
	inet_pton(AF_INET, globals.pcap.netstr, &iph->saddr);
	inet_pton(AF_INET, address->hostaddr, &iph->daddr);
	iph->check = 0;
	total_len += sizeof(*iph);

	/* Construct UDP header */
	uh = (struct udphdr *)(packet + sizeof(*eth) + sizeof(*iph));
	uh->source = htons(4242);
	uh->dest = htons(port);
	uh->check = 0;
	total_len += sizeof(struct udphdr);

	/* We can now had some data */
	data = &packet[total_len];
	data_len = 0;
	data[data_len++] = 'A';
	data[data_len++] = 'B';
	data[data_len++] = 'C';
	data[data_len++] = 'D';
	data[data_len++] = '\0';
	total_len += data_len;

	/* Filling the IP and UDP headers len field */
	iph->tot_len = htons(total_len - sizeof(*eth));
	uh->len = htons((total_len - sizeof(*iph) - sizeof(*eth)));

	/* NOw the IP header checksum */
	iph->check = checksum((uint16_t *) iph, 20);
	return total_len;
}
