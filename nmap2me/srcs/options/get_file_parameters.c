
#include "options.h"
#include "libft.h"
#include "get_next_line.h"

#include <fcntl.h>

void			get_file_parameters(char *arg, t_params *e)
{
	t_addr		**tmp;
	char		*line;
	int			ret;
	int			fd;

	tmp = &e->addresses;
	line = NULL;
	if (arg == NULL)
		nmap_error(e, "Option file: Missing parameter.");
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		nmap_error(e, "Can't open file: \"%s\"", arg);
	free_addresses(&e->addresses);
	e->addresses_nb = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line && *line)
			tmp = get_new_addr(line, tmp, e);
		else
			ft_strdel(&line);
	}
	close(fd);
	if (ret < 0)
		nmap_error(e, "A problem occured while getting \"%s\" lines.", arg);
}
