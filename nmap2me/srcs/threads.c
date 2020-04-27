#include "all.h"
#include "libft.h"
#include "ft_printf.h"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <linux/tcp.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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
	for (int i = 0, ret; i < thr->opes; i++)
	{
		dest.sin_family = AF_INET;
		dest.sin_port = htons(data[i].port);
		dest.sin_addr.s_addr = inet_addr(data[i].addr->hostaddr);
		init_ipv4_hdr(raw, &dest, IPPROTO_TCP, thr->addr);
		init_tcp_hdr(raw, data + i);
		pthread_mutex_lock(thr->lock);
	ft_printf("Sent:\n");
	for (unsigned int i = 0; i < sizeof(raw); i++)
	{
		ft_printf("%02x ", raw[i]);
		if ((i + 1) % 16 == 0)
			ft_printf("\n");
	}
	ft_printf("\n");
		ret = sendto(thr->socket, raw, sizeof(raw), 0,
			(struct sockaddr *)&dest, sizeof(dest));
		pthread_mutex_unlock(thr->lock);
		if (ret < 0)
		{
			ft_printf("ERROR: Thread %d sending packet. %s\n", thr->thread_id);
			break ;
		}
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
		if (pthread_create(&ptr->thread_id, NULL, routine_threads, ptr))
			ft_printf("WARNING: Thread %d creation failed.\n", i);
		index += ptr->opes;
		i++;
	}
	i = 0;
	while (i < e->threads_nb && i < e->total_operations)
	{
		pthread_join(e->threads[i]->thread_id, NULL);
		i++;
	}
}
