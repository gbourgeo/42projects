/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 20:45:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/12 22:58:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_args	*new_elem(const char *av);
static void		create_list(t_info *list, const char *av);

void			ft_initialize_list(const char **av, t_info *info)
{
	int				len;
	int				i;

	len = 0;
	i = 1;
	info->lst_col = 0;
	info->elems = NULL;
	while (av[i])
	{
		create_list(info, av[i]);
		len = ft_strlen(av[i]);
		info->lst_col = (len > info->lst_col) ? len : info->lst_col;
		i++;
	}
	info->elems->current = 1;
	info->lst_len = i - 1;
}

static t_args	*new_elem(const char *av)
{
	t_args			*new;

	if ((new = (t_args*)malloc(1* sizeof(t_args))) == NULL)
	{
		ft_putstr_fd("Malloc (newelemlist) failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new->c = av;
	new->selected = 0;
	new->current = 0;
	new->next = new;
	new->prev = new;
	new->x = 0;
	new->y = 0;
	return (new);
}

static void		create_list(t_info *list, const char *av)
{
	t_args			*new;
	t_args			*tmp;

	new = NULL;
	if (list->elems == NULL)
		list->elems = new_elem(av);
	else
	{
		tmp = list->elems;
		if ((new = new_elem(av)) != NULL)
		{
			while (tmp->next != list->elems)
				tmp = tmp->next;
			tmp->next = new;
			new->next = list->elems;
			new->prev = tmp;
			list->elems->prev = new;
		}
	}
	tmp = NULL;
}
