
#include "all.h"
#include "libft.h"

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
	ft_bzero(*addr, sizeof(**addr));
	free(*addr);
	*addr = NULL;
}

void	free_threads(t_thread **thr, int thr_nb)
{
	if (thr == NULL)
		return ;
	for (int i = 0; i < thr_nb; i++) {
		ft_strdel((char **)&thr[i]);
	}
	free(thr);
}

void	free_params(t_params *e)
{
	ft_strdel((char **)&e->ports);
	ft_tabdel(&e->scans);
	free_addresses(&e->addresses);
	free_threads(e->threads, e->threads_nb);
	if (e->handle)
		pcap_close(e->handle);
	ft_strdel((char **)&g_global.device);
	ft_strdel((char **)&g_global.data);
}
