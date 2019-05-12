/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:15:52 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 16:33:19 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "put.h"
#include "libft.h"
#include "shell_lib.h"
#include "quote_removal.h"
#include <dirent.h>

static char	*add_escape(char *str, int nb)
{
	char	*esc;
	int		i;
	int		j;

	if (!(esc = ft_memalloc(sizeof(char) * (ft_strlen(str) + nb + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (sh_is_escapable(str[i]))
		{
			if (str[i] == '\n')
			{
				ft_strcpy(&esc[j], "$'\\n'");
				j += 5;
			}
			else
				esc[j++] = '\\';
		}
		if (str[i] != '\n')
			esc[j++] = str[i];
	}
	return (esc);
}

t_tree		*create_bin_tree(char **env)
{
	t_tree	*ternary;

	if (!env)
		return (NULL);
	ternary = NULL;
	fill_tree_bin(env, &ternary);
	if (!ternary)
		return (NULL);
	set_psblty(ternary, 1);
	return (ternary);
}

t_tree		*create_env_tree(char **env)
{
	t_tree	*ternary;

	if (!env)
		return (NULL);
	ternary = NULL;
	fill_tree_env(env, &ternary);
	if (!ternary)
		return (NULL);
	set_psblty(ternary, 1);
	return (ternary);
}

static void	feed_file_tree(struct dirent *indir, char *beg, t_tree **tern)
{
	int		is_esc;
	char	*tmp;

	if ((is_esc = sh_str_isescape(indir->d_name)))
	{
		tmp = add_escape(indir->d_name, is_esc);
		if (beg)
			tmp = ft_strjoinfree(beg, tmp, 2);
		feed_tree(tmp, indir->d_type, tern, 0);
		free(tmp);
	}
	else
	{
		if (beg)
			tmp = ft_strjoin(beg, indir->d_name);
		else
			tmp = indir->d_name;
		feed_tree(tmp, indir->d_type, tern, 0);
		if (beg)
			free(tmp);
	}
}

t_tree		*create_file_tree(char *path, char *beg, t_tree *tern)
{
	struct dirent	*indir;
	DIR				*dir;
	char			*tmp;

	tmp = ft_strdup(path);
	check_str(path);
	if (!path || !(dir = opendir(path)))
	{
		free(tmp);
		return (NULL);
	}
	if (ft_strcmp(path, "."))
		ft_strcpy(path, tmp);
	free(tmp);
	if (!tern)
	{
		if (!(tern = ft_memalloc(sizeof(t_tree))))
			return (NULL);
		tern->value = -1;
	}
	while ((indir = readdir(dir)))
		feed_file_tree(indir, beg, &tern);
	set_psblty(tern, 0);
	closedir(dir);
	return (tern);
}
