/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:45:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 16:26:31 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "put.h"
#include "shell_lib.h"

static int	check_path_access(char *path, char *name)
{
	char		*tmp;
	struct stat	sb;

	if (*path && *ft_strchr(path, 0) - 1 != '/')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	tmp = ft_strjoinfree(tmp, name, 1);
	if (!access(tmp, F_OK) && !access(tmp, X_OK) && stat(tmp, &sb) != -1
			&& !S_ISDIR(sb.st_mode))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static int	get_indir(char *toget, int *i, t_tree **ternary)
{
	char			*path;
	DIR				*dir;
	struct dirent	*indir;

	path = strdup_until(&toget[*i], ':');
	dir = opendir(path);
	while (dir && (indir = readdir(dir)))
		if (ft_strcmp(indir->d_name, ".") && ft_strcmp(indir->d_name, "..")
				&& !check_path_access(path, indir->d_name))
			feed_tree(indir->d_name, -1, ternary, 0);
	free(path);
	if (!ft_strchr(&toget[*i], ':'))
	{
		if (dir)
			closedir(dir);
		return (1);
	}
	*i += ft_strlen_ch(&toget[*i], ':') + 1;
	if (dir)
		closedir(dir);
	return (0);
}

void		fill_tree_bin(char **env, t_tree **ternary)
{
	char			*toget;
	int				i;
	static char		*builtins[] = {
		"alias", "cd", "echo", "env", "exit", "setenv", "source", "unalias",
		"unsetenv", NULL };

	toget = sh_getnenv("PATH", env);
	if (!(*ternary = ft_memalloc(sizeof(t_tree))))
	{
		*ternary = NULL;
		return ;
	}
	(*ternary)->value = -1;
	i = 0;
	if (toget)
		while (1)
			if (get_indir(toget, &i, ternary))
				break ;
	i = -1;
	while (builtins[++i])
		feed_tree(builtins[i], -1, ternary, 0);
}

void		fill_tree_env(char **env, t_tree **ternary)
{
	int		i;
	char	*var;

	if (!*ternary)
	{
		if (!(*ternary = ft_memalloc(sizeof(t_tree))))
			return ;
		(*ternary)->value = -1;
	}
	i = 0;
	if (env)
		while (env[i])
		{
			var = strdup_until(env[i], '=');
			feed_tree(var, -1, ternary, 0);
			free(var);
			i++;
		}
}
