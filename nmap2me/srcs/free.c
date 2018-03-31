#include "all.h"
#include "libft.h"

static void 	free_addresses(t_addr *addr)
{
	if (addr == NULL)
		return ;
	free_addresses(addr->next);
	free(addr);
}

static void		free_threads(t_thread **thr)
{
	if (thr == NULL)
		return ;
	for (int i = 0; thr[i]; i++) {
		free(thr[i]);
	}
	free(thr);
}

void			free_resources()
{
	ft_freetab(&globals.scans);
	free_addresses(globals.addresses);
	free_threads(globals.threads);
}
