
#include "options.h"
#include "libft.h"

void 			get_threads_parameters(char *arg, t_params *e)
{
	int			value;

	if (arg == NULL)
		nmap_error(e, "Option thread: Missing parameter.");
	free_threads(e->threads, e->threads_nb);
	value = ft_atoi(arg);
	if (value < 1 || value > MAX_THREADS_NUMBER)
		nmap_error(e, "Wrong parameter: %s (%d max).",
			arg, MAX_THREADS_NUMBER);
	if (!(e->threads = ft_memalloc(sizeof(*e->threads) * value)))
		nmap_error(e, "Threads allocation failed.");
	for (int i = 0; i < value; i++)
	{
		if (!(e->threads[i] = ft_memalloc(sizeof(**e->threads))))
			nmap_error(e, "Thread %d allocation failed.", i);
	}
	e->threads_nb = value;
}
