/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 16:20:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/19 16:34:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				ft_add_link(char *buf, t_env *e)
{
	t_map		*r_tmp;
	t_link		*l_tmp;
	char		**str;

	r_tmp = e->rooms;
	str = ft_strsplit(buf, '-');
	if (!str[0] || !str[1] || str[2] || ft_strcmp(str[0], str[1]) == 0)
		return (1);
	while (r_tmp && ft_strcmp(r_tmp->name, str[0]))
		r_tmp = r_tmp->next;
	if (r_tmp == NULL)
		return (1);
	if ((l_tmp = (t_link*)malloc(sizeof(t_link))) == NULL)
		return (1);
	l_tmp->name = ft_strdup(str[1]);
	l_tmp->next = r_tmp->links;
	r_tmp->links = l_tmp;
	r_tmp->linknb++;
	return (0);
}

int				ft_add_second_link(char *buf, t_env *e)
{
	t_map		*r_tmp;
	t_link		*l_tmp;
	char		**str;

	r_tmp = e->rooms;
	str = ft_strsplit(buf, '-');
	if (!str[0] || !str[1] || str[2] || ft_strcmp(str[0], str[1]) == 0)
		return (1);
	while (r_tmp && ft_strcmp(r_tmp->name, str[1]))
		r_tmp = r_tmp->next;
	if (r_tmp == NULL)
		return (1);
	if ((l_tmp = (t_link*)malloc(sizeof(t_link))) == NULL)
		return (1);
	l_tmp->name = ft_strdup(str[0]);
	l_tmp->next = r_tmp->links;
	r_tmp->links = l_tmp;
	r_tmp->linknb++;
	return (0);
}
