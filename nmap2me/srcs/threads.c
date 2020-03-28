#include "all.h"
#include "libft.h"
#include "ft_printf.h"

#include <netinet/ip.h>
#include <linux/tcp.h>
#include <unistd.h>

static void 	*routine_threads(void *ptr)
{
	t_thread			*thr;
	t_data				*data;
	char				raw[sizeof(struct ip) + sizeof(struct tcphdr)];
	struct sockaddr_in	sin;
	int					fd;

	if (ptr == NULL)
		ft_printf("WARNING: Data from thread routine is NULL.\n");
	else
	{
		thr = (t_thread *)ptr;
		data = thr->data;
		if ((fd = init_socket(IPPROTO_TCP, g_global.recv_timeout)) < 0)
			pthread_exit(NULL);
		for (int i = 0; i < thr->opes; i++)
		{
			if (i == 0 || data[i - 1].addr != data[i].addr)
			{
				if (!init_ipv4_hdr(raw, g_global.device, data[i].addr->hostaddr, IPPROTO_TCP))
					break ;
				ft_memset(&sin, 0, sizeof(sin));
				sin.sin_family = AF_INET;
				sin.sin_addr.s_addr = ((struct ip *)raw)->ip_dst.s_addr;
			}
			init_tcp_hdr(raw, data[i].port, data[i].scan, g_global.device);
			sin.sin_port = htons(data[i].port);
			int ret = sendto(fd, raw, sizeof(raw), 0, (struct sockaddr *)&sin, sizeof(struct sockaddr));
			ft_printf("Thread %d sent %d bytes to %s on port %d from scan %s\n",
			thr->nb, ret, data[i].addr->hostaddr, data[i].port, data[i].scan);
		}
		close(fd);
	}
	pthread_exit(NULL);
}

void 			init_threads(t_params *e)
{
	t_thread	*ptr	= NULL;
	/* Total number of operations to be performed (scans per port per addresses). */
	int 		total	= e->addresses_nb * e->ports_nb * e->scans_nb;
	/* Number of operations per thread. */
	int 		opes	= total / e->threads_nb;
	int 		index 	= 0;
	int 		i 		= 0;

	// gettimeofday(&e->start, NULL);
	while (i < e->threads_nb && i < total)
	{
 		/* Number of total operations to perform and threads can be unpaired */
 		int ports_plus 	= (i < total % e->threads_nb) ? 1 : 0;

		ptr = e->threads[i];
		ptr->nb = i;
		ptr->opes = opes + ports_plus;
		ptr->data = g_global.data + index;
		if (pthread_create(&ptr->id, NULL, routine_threads, ptr))
			ft_printf("WARNING: Thread %d creation failed.\n", i);
		index += ptr->opes;
		i++;
	}
	i = 0;
	while (i < e->threads_nb && i < total) {
		ptr = e->threads[i];
		pthread_join(ptr->id, NULL);
		i++;
	}
	ft_printf("All threads terminated.\n");
	// if (init_pcap(100, 0, 0, ""))
	{
//		ping_scan();
	}
}
