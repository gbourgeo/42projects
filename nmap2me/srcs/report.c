
#include "all.h"
#include "ft_printf.h"

static char		*get_status(t_response *r)
{
	if (r->received == 0)
		return ("closed");
	if (r->filtered == 0)
		return ("open");
	return ("filtered");
}

void			scan_report(t_addr *addr, t_params *e)
{
	unsigned int	opes;
	unsigned int	i;

	opes = e->ports_nb * e->scans_nb;
	i = 0;
	ft_printf("%s scan report for %s (%s)\n", e->progname, addr->name, addr->hostaddr);
	ft_printf("%s %s %s\n", "PORT", "STATE", "SERVICE");
	while (i < opes)
	{
		ft_printf("%d/%s %s\n",
			e->data[i].port,
			e->data[i].scan,
			get_status(&e->data[i].response)
		);
		i++;
	}
}
