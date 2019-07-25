/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 12:48:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 20:05:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_get_directives(t_env *e);
static int		ft_check(int *special, char **tab, t_env *e);
static void		ft_freetab(char **tab);

int				ft_init_env(t_env *e)
{
	int			ret;
	char		*buf;
	int			i;

	buf = NULL;
	e->rooms = NULL;
	e->paths = NULL;
	i = 0;
	while ((ret = get_next_line(0, &buf)) > 0 && buf[0] == '#')
	{
		ft_putendl(buf);
		if (!ft_strcmp(buf, "##start") && !ft_strcmp(buf, "##end"))
			return (0);
		free(buf);
	}
	ft_putendl(buf);
	while (buf[i])
	{
		if (ft_isdigit(buf[i++]) == 0)
			return (0);
	}
	if (ret > 0 && (e->ants = ft_atoi(buf)) > 0)
		return (ft_get_directives(e));
	return (0);
}

static int		ft_get_directives(t_env *e)
{
	int			ret;
	int			special;
	char		*buf;
	char		**tab;

	special = 0;
	while ((ret = get_next_line(0, &buf)) > 0 && buf[0])
	{
		ft_putendl(buf);
		if (ft_strcmp(buf, "##start") == 0)
			special = START;
		else if (ft_strcmp(buf, "##end") == 0)
			special = END;
		else if (buf[0] == 'L')
			return (0);
		if ((tab = ft_strsplit(buf, ' ')) == NULL)
			return (0);
		if (ft_check(&special, tab, e))
			return (0);
		ft_freetab(tab);
		free(buf);
	}
	return (ret);
}

static int		ft_check(int *special, char **tab, t_env *e)
{
	if (tab[0][0] != '#' && ft_strchr(tab[0], '-') && tab[1])
		return (1);
	if (tab[0][0] != '#' && ft_strchr(tab[0], '-') && !tab[1])
	{
		if (ft_add_link(tab[0], e) || ft_add_second_link(tab[0], e))
			return (1);
	}
	else if (tab[0][0] != '#' && !(e->rooms = ft_add_room(tab, special, e)))
		return (1);
	return (0);
}

static void		ft_freetab(char **tab)
{
	int			i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}
