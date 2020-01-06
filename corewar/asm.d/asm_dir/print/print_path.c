/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:09:58 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/23 03:53:15 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

int				len_path(char *file)
{
	int		i;
	int		len;
	int		occ;

	occ = 0;
	len = 0;
	i = 0;
	while (file[i])
	{
		if (file[i] == '/')
			occ++;
		i++;
	}
	i = 0;
	while (file[i])
	{
		if (occ == 0)
			break ;
		if (file[i] == '/')
			occ--;
		len++;
		i++;
	}
	return (len);
}

static char		*get_path(char *file)
{
	int		i;
	int		len;
	char	*path;

	len = len_path(file);
	path = NULL;
	i = 0;
	if (len > 0)
	{
		if (!(path = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (i < len)
		{
			path[i] = file[i];
			i++;
		}
		path[i] = '\0';
	}
	return (path);
}

void			print_path(t_data *data)
{
	char *path;
	char *cwd;

	cwd = getcwd(NULL, 0);
	path = get_path(data->file_name);
	if (data->e->flag & FLAG_GP)
		ft_printf("%s/%s\n", cwd, data->file_name);
	else
		ft_printf("%s/%s\n", cwd, path);
	free(path);
	free(cwd);
}
