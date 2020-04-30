
#include "options.h"
#include "libft.h"
#include "get_next_line.h"

#include <fcntl.h>

char			**get_file_parameters(char **arg, t_params *e)
{
	char		*line;
	char		*value;
	int			ret;
	int			fd;

	line = NULL;
	value = *++arg;
	if (value == NULL)
		nmap_error(e, "Option file: Missing parameter.");
	fd = open(value, O_RDONLY);
	if (fd < 0)
		nmap_error(e, "Can't open file: \"%s\"", value);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line && *line)
		{
			if (add_new_addr(line, &e->addresses))
				e->addresses_nb++;
		}
		else
			ft_strdel(&line);
	}
	close(fd);
	if (ret < 0)
		nmap_error(e, "A problem occured while getting \"%s\" lines.", value);
	return (arg);
}
