/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:29:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/07/13 14:38:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int			main(int ac, char **av)
{
	int		fd;
	int		ret;
	char	buff[1024];

	if (ac < 2)
		return (write(STDOUT_FILENO, "File name missing.\n", 19));
	if (ac > 2)
		return (write(STDOUT_FILENO, "Too many arguments.\n", 20));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (write(STDOUT_FILENO, "File access missing.\n", 21));
	while ((ret = read(fd, buff, 1024)) > 0)
		write(STDIN_FILENO, buff, ret);
	close(fd);
	return (0);
}
