#include "all.h"
#include "libft.h"
#include "ft_printf.h"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <linux/tcp.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <linux/if_ether.h>
#include <netinet/ether.h>
#include <signal.h>

t_data		*my_data(int protocol, int id, int opes, t_data *data)
{
	int		i;

	i = 0;
	(void)protocol;
	while (i < opes)
	{
		if (data[i].id == id)
		{
			return (data + i);
		}
		i++;
	}
	return (NULL);
}
void				p_dump(unsigned char *user, const struct pcap_pkthdr *h,
const unsigned char *bytes)
{
	t_thread			*thr;
	t_data				*data;
	struct ethhdr	*eth;
	struct iphdr	*ip;
	
	(void)h;
	thr = (t_thread *)user;
	data = thr->data;
	eth = (struct ethhdr *)bytes; // link layer header
	ip = (struct iphdr *)(bytes + sizeof(*eth));
	if (ip->protocol == IPPROTO_TCP)
	{
		struct tcphdr	*tcp_header;
		int				id_dst;

		tcp_header = (struct tcphdr*)(bytes + sizeof(*eth) + sizeof(*ip));
		id_dst = ntohs(tcp_header->dest);
		data = my_data(IPPROTO_TCP, id_dst, thr->opes, data);
		if (data)
		{
			data->response.received = 1;
			if (!ft_strcmp(data->scan, "SYN"))
			{
				if (tcp_header->syn)
				{
					data->response.open = 1;
				}
				else if (tcp_header->rst)
					data->response.filtered = 0;
			}
		}
	}
	else if (ip->protocol == IPPROTO_ICMP)
	{
		struct icmp		*icmp;

		icmp = (struct icmp *)(bytes + sizeof(*eth) + sizeof(*ip));
		ft_printf("ICMP %p\n", icmp);
	}
}

static void 	*routine_threads(void *ptr)
{
	t_thread			*thr;
	t_data				*data;
	char				raw[sizeof(struct iphdr) + sizeof(struct tcphdr)];
	struct sockaddr_in	dest;

	thr = (t_thread *)ptr;
	data = thr->data;
	ft_memset(raw, 0, sizeof(raw));
	ft_memset(&dest, 0, sizeof(dest));
	for (int loop = 0; loop < thr->retry_nb; loop++)
	{
		for (int i = 0, ret; i < thr->opes; i++)
		{
			if (data[i].response.received)
				continue ;
			dest.sin_family = AF_INET;
			dest.sin_port = htons(data[i].port);
			dest.sin_addr.s_addr = inet_addr(data[i].addr->hostaddr);
			init_ipv4_hdr(raw, &dest, IPPROTO_TCP, thr->addr);
			init_tcp_hdr(raw, data + i);
			pthread_mutex_lock(thr->lock);
		// ft_printf("Sending:\n");
		// print_ip_hdr((struct iphdr *)raw);
		// print_tcp_hdr((struct tcphdr *)(raw + sizeof(struct iphdr)));
			ret = sendto(thr->socket, raw, sizeof(raw), 0,
				(struct sockaddr *)&dest, sizeof(dest));
			pthread_mutex_unlock(thr->lock);
			if (ret < 0)
			{
				ft_printf("ERROR: Thread %d sending packet. %s\n", thr->thread_id);
				break ;
			}
		}
		usleep(thr->retry_timeout * 1000);
	}
	pthread_exit(NULL);
}

void 			init_threads(t_params *e)
{
	t_thread		*ptr	= NULL;
	/* Number of operations per thread. */
	int				opes	= e->total_operations / e->threads_nb;
	int				index	= 0;
	unsigned int	i		= 0;
	int				fd		= 0;

	// gettimeofday(&e->start, NULL);
	if ((fd = init_socket(IPPROTO_RAW)) < 0)
		nmap_error(e, "Can't open socket to send packets");
	while (i < e->threads_nb && i < e->total_operations)
	{
		/* Number of total operations to perform and threads can be unpaired */
		int ports_plus	= (i < e->total_operations % e->threads_nb) ? 1 : 0;

		ptr = e->threads[i];
		ptr->data = e->data + index;
		ptr->socket = fd;
		ptr->opes = opes + ports_plus;
		ptr->addr = e->pcap.addr;
		ptr->lock = &e->socket_lock;
		ptr->retry_nb = e->retry;
		ptr->retry_timeout = e->tcp_timeout;
		if (pthread_create(&ptr->thread_id, NULL, routine_threads, ptr))
			ft_printf("WARNING: Thread %d creation failed.\n", i);
		index += ptr->opes;
		i++;
	}
}
