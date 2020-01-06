/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_corfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:28:27 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/23 01:28:03 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

char			*basename(char *file)
{
	int			len;
	int			i;
	char		*b_name;

	len = ft_strlen(file) - 2;
	i = 0;
	if (!(b_name = (char *)ft_memalloc(sizeof(char) * len + 4 + 1)))
		return (NULL);
	while (file && i < len)
	{
		b_name[i] = file[i];
		i++;
	}
	return (ft_strjoinfree(b_name, COR_EXT, 1));
}

int				create_corfile(t_data *data, char *file)
{
	int			fd;

	if ((data->file_name = basename(file)) == NULL)
		return (ERR_MALLOC);
	if ((fd = open(data->file_name, O_CREAT | O_TRUNC | O_RDWR, 0700)) < 0)
		return (ERR_OPEN);
	return (fd);
}
