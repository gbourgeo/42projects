
#include "all.h"
#include "options.h"
#include "libft.h"

void 			get_threads_parameters(char *arg, t_params *e)
{
	if (arg == NULL)
		nmap_error(e, "Missing parameter `--speed'.");
	free_threads(e->threads, e->threads_nb);
	e->threads_nb = ft_atoi(arg);
	if (e->threads_nb < 1 || e->threads_nb > MAX_THREADS_NUMBER)
		nmap_error(e, "Wrong parameter: %s (%d max).",
			arg, MAX_THREADS_NUMBER);
	if (!(e->threads = ft_memalloc(sizeof(*e->threads) * e->threads_nb)))
		nmap_error(e, "Threads allocation failed.");
	for (int i = 0; i < e->threads_nb; i++)
	{
		if (!(e->threads[i] = ft_memalloc(sizeof(**e->threads))))
			nmap_error(e, "Thread %d allocation failed.", i);
	}
}
