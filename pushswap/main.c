/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 17:52:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/30 01:12:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ps_dellist(t_lib **anumb);
static char		*check_solution(char *ret);
static t_lib	*create_lib(const char **av);
static int		ultimate_check(t_lib *a);

int				main(int ac, const char **av)
{
	t_lib		*l_a;
	char		*ret;

	if (ac > 2 && (ps_check_params(ac, av)))
	{
		l_a = create_lib(av);
		if (ultimate_check(l_a))
			return (0);
		ret = ft_push_swap(&l_a);
		ret = check_solution(ret);
		ret[ft_strlen(ret) - 1] = '\0';
		ft_putstr(ret);
		ps_dellist(&l_a);
	}
	ft_putstr("\n");
	return (0);
}

static t_lib	*create_lib(const char **av)
{
	t_lib		*l_a;
	t_lib		*tmp;
	int			i;

	i = 1;
	if ((tmp = ps_newlist(0)) == NULL)
		return (NULL);
	l_a = tmp;
	while (av[i])
	{
		tmp->nb = ft_atoi(av[i]);
		if (av[i + 1])
		{
			if ((tmp->next = ps_newlist(0)) == NULL)
				return (NULL);
			tmp = tmp->next;
		}
		i++;
	}
	return (l_a);
}

static int		ultimate_check(t_lib *a)
{
	t_lib	*b;

	while (a->next)
	{
		b = a->next;
		while (b)
		{
			if (b->nb == a->nb)
			{
				ft_putstr("Error\n");
				return (1);
			}
			b = b->next;
		}
		a = a->next;
	}
	return (0);
}

static char		*check_solution(char *ret)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (i < ft_strlen(ret))
	{
		if (ret[i] == 's')
		{
			if (ft_strcmp(ret, "sa sb") == 32)
			{
				tmp = ft_strjoin("ss", &ret[i + 5]);
				ret = ft_strcpy(&ret[i], tmp);
			}
		}
		if (ret[i] == 'r')
		{
			if (ft_strcmp(ret, "ra rb") == 32)
			{
				tmp = ft_strjoin("rr", &ret[i + 5]);
				ret = ft_strcpy(&ret[i], tmp);
			}
		}
		i += 6;
	}
	return (ret);
}

static void		ps_dellist(t_lib **anumb)
{
	if (*anumb != NULL)
	{
		(*anumb)->nb = 0;
		while ((*anumb)->next != NULL)
			ps_dellist(&(*anumb)->next);
		free(*anumb);
		*anumb = NULL;
	}
}
