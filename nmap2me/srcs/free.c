
#include "all.h"
#include "libft.h"

#include <unistd.h>

t_addr	*delete_address(t_addr *addr, t_addr **head)
{
	t_addr	*ret;

	if (!addr)
		return (NULL);
	ret = addr->next;
	if (addr->prev)
		addr->prev->next = ret;
	else
		*head = ret;
	addr->next = NULL;
	free_addresses(&addr);
	return (ret);
}

void	free_addresses(t_addr **addr)
{
	if (*addr == NULL)
		return ;
	free_addresses(&(*addr)->next);
	ft_strdel(&(*addr)->name);
	if ((*addr)->res)
		freeaddrinfo((*addr)->res);
	ft_bzero(*addr, sizeof(**addr));
	free(*addr);
	*addr = NULL;
}

void	free_threads(t_thread **thr, int thr_nb)
{
	if (thr == NULL)
		return ;
	if ((*thr)->socket > 0 && (*thr)->socket != STDIN_FILENO
	&& (*thr)->socket != STDOUT_FILENO && (*thr)->socket != STDERR_FILENO)
		close((*thr)->socket);
	(*thr)->socket = -1;
	for (int i = 0; i < thr_nb; i++) {
		ft_strdel((char **)&thr[i]);
	}
	free(thr);
}

void	free_ifaddrs(t_ifaddr *addr)
{
	if (!addr)
		return ;
	free_ifaddrs(addr->next);
	ft_strdel(&addr->name);
	free(addr);
}

void	free_params(t_params *e)
{
	for (unsigned int i = 0; i < e->threads_nb && i < e->total_operations; i++)
	{
		if (e->threads[i]->thread_id > 0)
			pthread_join(e->threads[i]->thread_id, NULL);
	}
	ft_strdel((char **)&e->ports);
	ft_tabdel(&e->scans);
	free_addresses(&e->addresses);
	free_threads(e->threads, e->threads_nb);
	ft_strdel(&e->device);
	free_ifaddrs(e->ifaddrs);
	if (e->interfaces)
		pcap_freealldevs(e->interfaces);
	e->interfaces = NULL;
	pthread_mutex_destroy(&e->socket_lock);
	ft_strdel((char **)&e->data);
	if (g_global.handle)
		pcap_close(g_global.handle);
	g_global.handle = NULL;
}
