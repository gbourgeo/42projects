
#include "options.h"
#include "ft_printf.h"

char			**get_help(char **arg, t_params *e)
{
	t_options	*opt;
	long		i;

	opt = nmap_options(0);
	i = (long)nmap_options(1);
	ft_printf("Usage: %s [OPTIONS]...\n", e->progname);
	while (i--)
	{
		ft_printf("\n\t%s, %s", opt[i].sname, opt[i].fname);
		if (opt[i].argument)
			ft_printf(" [%s]", opt[i].argument);
		ft_printf("\n\t\t%s\n", opt[i].description);
	}
	free_params(e);
	exit(0);
	return (arg);
}
