/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 17:20:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 20:58:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_path	*ft_new_path(void);

int				main(int ac, char **av)
{
	t_env		e;
	t_map		*m_tmp;

	if (ac && av)
	{
		if (ft_init_env(&e) && ft_check_paths(&e))
		{
			m_tmp = find_start_room(e.rooms);
			e.paths = ft_get_paths(m_tmp, e.rooms, ft_new_path());
			if (e.paths)
			{
				ft_sort_paths(e.paths);
				if (ft_strstr(e.paths->name, find_end_room(e.rooms)->name))
					ft_print_lem(e.ants, ft_strsplit(e.paths->name, ' '));
				else if (e.paths->next)
					ft_print_lem(e.ants, ft_strsplit(e.paths->next->name, ' '));
				return (0);
			}
		}
	}
	ft_putendl_fd("\n!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!", 2);
	return (0);
}

static t_path	*ft_new_path(void)
{
	t_path		*new;

	if ((new = (t_path*)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	new->name = ft_strnew(1);
	new->len = 0;
	new->next = NULL;
	return (new);
}
