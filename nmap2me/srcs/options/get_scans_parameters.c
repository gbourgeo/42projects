
#include "options.h"
#include "libft.h"

static int		findname(char *name, void *table, int jmp, long size)
{
	char		*ptr;
	int			i;

	ptr = (char *)table;
	i = 0;
	while (size--)
	{
		if (!ft_strcmp(name, (char *)*(long *)(ptr + i)))
			return (1);
		i += jmp;
	}
	return (0);
}

char 			**get_scans_parameters(char **arg, t_params *e)
{
	char	*head;
	char	*tail;
	int		end;

	head = *++arg;
	if (head == NULL)
		nmap_error(e, "Option scan: Missing parameter.");
	end = 0;
	for (int i = 0; e->scans[i]; i++)
		ft_strdel(&e->scans[i]);
	while (end == 0)
	{
		if (!(tail = ft_strchr(head, '/')))
			end = 1;
		else
			*tail = '\0';
		if (!findname(head, nmap_scans(0), sizeof(t_scans), (long)nmap_scans(1)))
			nmap_error(e, "Unrecognized scan type: `%s'", head);
		if (!findname(head, e->scans, sizeof(char *), ft_tablen(e->scans)))
			e->scans[ft_tablen(e->scans)] = ft_strdup(head);
		head = tail + 1;
	}
	e->scans_nb = ft_tablen(e->scans);
	return (arg);
}
