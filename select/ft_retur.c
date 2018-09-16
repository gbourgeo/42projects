/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 21:12:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/13 18:08:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_print_to_shell(t_args *elems);

void		ft_retur(t_info *info)
{
	struct termios	termios;

	tputs(ft_tgetstr("te"), 1, ft_pchar);
	tputs(ft_tgetstr("ve"), 1, ft_pchar);
	if (tcgetattr(0, &termios) != 0)
		ft_error("Fatal restore error: tcgetattr().\n");
	termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &termios) == -1)
		ft_error("Fatal restore error: tcsetattr().\n");
	close(info->fd);
	ft_print_to_shell(info->elems);
	exit(EXIT_SUCCESS);
}

static void	ft_print_to_shell(t_args *elems)
{
	t_args			*tmp;
	int				count;

	count = 0;
	tmp = elems;
	if (tmp->selected == 1)
	{
		ft_putstr_fd(tmp->c, 1);
		count++;
	}
	while ((tmp = tmp->next) != elems)
	{
		if (tmp->selected == 1)
		{
			if (count)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(tmp->c, 1);
			count++;
		}
	}
}
