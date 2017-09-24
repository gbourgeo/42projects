/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:58:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 08:19:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_search_script(char **environ)
{
	int			i;

	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], "SCRIPT=", 7) == 0)
			return (0);
		i++;
	}
	return (1);
}

char			**ft_copy_env(char **environ, char *file_name, int i)
{
	int			notfound;
	char		**tab;

	i = ft_tablen(environ);
	notfound = ft_search_script(environ);
	tab = (char **)malloc(sizeof(*tab) * (i + 1 + notfound));
	if (tab == NULL)
	{
		ft_putendl_fd("Warning: the environnement have not been duplicated", 2);
		ft_putendl_fd("Warning: The default environnement will be used.", 2);
		return (environ);
	}
	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], "SCRIPT=", 7) == 0)
			tab[i] = ft_strjoin("SCRIPT=", file_name);
		else
			tab[i] = environ[i];
		i++;
	}
	tab[i] = (notfound) ? ft_strjoin("SCRIPT=", file_name) : NULL;
	if (notfound)
		tab[i + 1] = NULL;
	return (tab);
}

void			ft_free_env(t_env *e)
{
	int			i;

	i = 0;
	if (!e->environ)
		return ;
	while (e->environ[i])
	{
		if (ft_strncmp(e->environ[i], "SCRIPT=", 7) == 0)
			free(e->environ[i]);
		i++;
	}
	free(e->environ[i]);
	free(e->environ);
}
