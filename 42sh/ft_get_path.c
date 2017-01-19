/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 06:17:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 18:48:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*ft_gen_path_from_list(t_hist *list)
{
	char	*path;
	char	*node;
	t_hist	*tmp;

	path = ft_strdup("/");
	if ((tmp = list) == NULL)
		return (path);
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		node = ft_strjoin(path, tmp->command);
		free(path);
		path = ft_strjoin(node, "/");
		free(node);
		tmp = tmp->prev;
	}
	if (tmp)
		node = ft_strjoin(path, tmp->command);
	free(path);
	tmp = NULL;
	ft_free_history(list);
	return (node);
}

static t_hist	*ft_add_to_list(char *dir, t_hist **list)
{
	t_hist	*new;

	if ((new = (t_hist*)malloc(sizeof(t_hist))) == NULL)
		return (NULL);
	new->prev = NULL;
	new->command = ft_strdup(dir);
	new->save = NULL;
	new->next = *list;
	if (*list)
		(*list)->prev = new;
	return (new);
}

static t_hist	*ft_remove_from_list(t_hist *list)
{
	t_hist	*new;

	new = NULL;
	if (list)
	{
		new = list->next;
		new->prev = NULL;
		if (list->command)
			free(list->command);
		list->next = NULL;
		free(list);
	}
	return (new);
}

char			*ft_get_path(char *pwd)
{
	char		**table;
	t_hist		*list;
	int			i;

	if ((table = ft_strsplit(pwd, '/')) == NULL)
		return (NULL);
	list = NULL;
	i = 0;
	while (table[i] != '\0')
	{
		if (!ft_strcmp(table[i], ".."))
			list = ft_remove_from_list(list);
		else if (table[i] && ft_strcmp(table[i], ".") != 0)
			list = ft_add_to_list(table[i], &list);
		i++;
	}
	ft_free(&table);
	free(pwd);
	pwd = NULL;
	return (ft_gen_path_from_list(list));
}
