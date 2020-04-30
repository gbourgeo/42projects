
#include "options.h"
#include "libft.h"

char 			**get_threads_parameters(char **arg, t_params *e)
{
	char		*value;
	int			ivalue;

	value = *++arg;
	if (value == NULL)
		nmap_error(e, "Option thread: Missing parameter.");
	free_threads(e->threads, e->threads_nb);
	ivalue = ft_atoi(value);
	if (ivalue < 1 || ivalue > MAX_THREADS_NUMBER)
		nmap_error(e, "Wrong parameter: %s (%d max).",
			value, MAX_THREADS_NUMBER);
	if (!(e->threads = ft_memalloc(sizeof(*e->threads) * ivalue)))
		nmap_error(e, "Threads allocation failed.");
	for (int i = 0; i < ivalue; i++)
	{
		if (!(e->threads[i] = ft_memalloc(sizeof(**e->threads))))
			nmap_error(e, "Thread %d allocation failed.", i);
	}
	e->threads_nb = ivalue;
	return (arg);
}
