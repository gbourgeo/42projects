
#include "options.h"
#include "libft.h"

void			get_options(char **argv, t_params *e)
{
	t_options	*opt;
	long		size;

	opt = nmap_options(0);
	while (*argv && *++argv)
	{
		size = (long)nmap_options(1);
		while (size--)
		{
			if (!ft_strcmp(*argv, opt[size].sname)
				|| !ft_strcmp(*argv, opt[size].fname))
			{
				argv = opt[size].handler(argv, e);
				break ;
			}
		}
		if (size < 0)
			nmap_error(e, "Illegal option `%s' %d", *argv, size);
	}
}
