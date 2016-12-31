/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_a_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 09:37:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/04/04 23:34:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_file		*ft_get_file(DIR *rep, char *dir_name, char *f_name)
{
	struct dirent	*file;
	t_file			*tmp;

	while ((file = readdir(rep)))
	{
		if (ft_strcmp(file->d_name, f_name) == 0)
		{
			if ((tmp = (t_file*)malloc(sizeof(t_file))) == NULL)
				return (NULL);
			ft_clear_file(tmp);
			tmp->name = ft_strdup(ft_strcat(dir_name, f_name));
			tmp->type = file->d_type;
			return (tmp);
		}
	}
	return (NULL);
}

t_file				*ft_is_a_file(char *dir_name)
{
	DIR			*rep;
	char		*name;
	t_file		*file;

	name = NULL;
	if (ft_strchr(dir_name, '/'))
	{
		name = ft_strdup(ft_strrchr(dir_name, '/') + 1);
		ft_strclr(ft_strrchr(dir_name, '/') + 1);
	}
	rep = opendir(dir_name);
	file = ft_get_file(rep, dir_name, name);
	closedir(rep);
	if (name)
	{
		ft_strcat(dir_name, name);
		free(name);
	}
	return (file);
}
