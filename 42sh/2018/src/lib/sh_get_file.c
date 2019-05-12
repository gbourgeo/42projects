/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:57:01 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/06 20:52:11 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "libft.h"
#include "struct.h"

char	*sh_get_file(int fd)
{
	char	*line;
	char	buff[1024];
	int		nb_read;
	int		max;

	line = NULL;
	ft_bzero(buff, 1024);
	max = 0;
	while ((nb_read = read(fd, buff, 1023)) > 0
			&& max < MAX_SHELL_LEN * 100)
	{
		buff[nb_read] = '\0';
		if (line)
			line = ft_strjoinfree(line, buff, 1);
		else
			line = ft_strdup(buff);
		max += nb_read;
	}
	return (line);
}
