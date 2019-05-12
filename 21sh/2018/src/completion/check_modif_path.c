/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_modif_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 01:00:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/23 15:59:28 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"
#include "shell_lib.h"
#include "main_tools.h"
#include "shell.h"
#include <sys/stat.h>

static int	cmp_t_stamp(t_stamp *tstmp, t_stamp *curr)
{
	if (tstmp->time == curr->time)
	{
		if (tstmp->next && curr->next)
			return (cmp_t_stamp(tstmp->next, curr->next));
		else if (!tstmp->next && !curr->next)
			return (0);
	}
	return (1);
}

static void	free_t_stamp(t_stamp *tstmp, int to_free)
{
	if (!tstmp || !to_free)
		return ;
	free_t_stamp(tstmp->next, 1);
	free(tstmp);
}

static int	get_timestamp(t_stamp *tstmp, char *path)
{
	char		*tmp;
	struct stat	sb;

	if (!tstmp || !path)
		return (1);
	while (path)
	{
		tmp = strdup_until(path, ':');
		if (!access(tmp, R_OK) && stat(tmp, &sb) != -1
				&& (tstmp->time = sb.st_mtime))
			if (ft_strchr(path, ':'))
			{
				if (!(tstmp->next = ft_memalloc(sizeof(t_stamp))))
				{
					free(tmp);
					return (1);
				}
				tstmp = tstmp->next;
			}
		free(tmp);
		if ((path = ft_strchr(path, ':')))
			path++;
	}
	return (0);
}

void		fill_alias_tree(t_alias *alias, t_line *line)
{
	while (alias)
	{
		feed_tree(alias->key, -1, &GET_TREE(line->tree, BIN), 0);
		alias = alias->next;
	}
}

void		check_mod_path(t_s_env *e, t_line *line, int to_free)
{
	static t_stamp	*tstmp = NULL;
	t_stamp			*curr;
	char			*path;

	path = sh_getnenv("PATH", e->public_env);
	if (!tstmp)
		if (get_timestamp((tstmp = ft_memalloc(sizeof(t_stamp))), path))
		{
			free_t_stamp(tstmp, 1);
			tstmp = NULL;
			return ;
		}
	if (get_timestamp((curr = ft_memalloc(sizeof(t_stamp))), path))
	{
		free_t_stamp(curr, 1);
		return ;
	}
	if (cmp_t_stamp(tstmp, curr))
	{
		free_tree(GET_TREE(line->tree, BIN));
		GET_TREE(line->tree, BIN) = create_bin_tree(e->public_env);
		fill_alias_tree(e->alias_list, line);
	}
	free_t_stamp(tstmp, 1);
	free_t_stamp((tstmp = curr), to_free);
}
