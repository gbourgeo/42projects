/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:17:03 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/25 22:49:46 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

static int	eval_asm_file(char *file)
{
	size_t		len;

	if (file)
		len = ft_strlen(file);
	else
		return (ERR_FILE);
	if (len < 3)
		return (ERR_FILE);
	if (file[len - 1] != 's' || file[len - 2] != '.')
		return (ERR_EXTENSION);
	return (OK);
}

int			asm_file_open(t_env *e, char *file)
{
	int		fd;
	char	c;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_OPEN);
	if (read(fd, &c, 1))
		if (c == '\0')
			exit(1);
	close(fd);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_OPEN);
	e->fd_name = file;
	e->fd = fd;
	return (0);
}

int			asm_file(int ac, char **av, int i)
{
	int			ret;

	ret = 0;
	if (ac < 2)
		return (ERR_NOFILE);
	if ((ret = eval_asm_file(av[i])) > 0)
		return (ret);
	return (0);
}
