/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 12:00:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:09:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		*ft_tgetstr(char *t)
{
	char			*tmp;

	if ((tmp = tgetstr(t, NULL)) == NULL)
	{
		ft_putstr_fd(t, 2);
		ft_putendl_fd(" not available", 2);
	}
	return (tmp);
}

void		ft_define_new_term_cap(t_env *e)
{
	struct termios	termios;

	if (tcgetattr(e->fd, &e->save) != 0)
	{
		ft_putendl("Fatal error: tcgetattr().\n");
		ft_exit(NULL, e);
	}
	if (tcgetattr(e->fd, &termios) != 0)
	{
		ft_putendl("Fatal error: tcgetattr().\n");
		ft_exit(NULL, e);
	}
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	tputs(ft_tgetstr("im"), 1, ft_pchar);
	if ((tcsetattr(e->fd, TCSANOW, &termios)) == -1)
	{
		ft_putendl("Fatal error: tcsetattr().\n");
		ft_exit(NULL, e);
	}
}

void		ft_term_restore(t_env *e)
{
	tputs(ft_tgetstr("ei"), 1, ft_pchar);
	if (tcsetattr(e->fd, TCSANOW, &e->save) == -1)
		ft_error("Fatal restore error: tcsetattr().\n", e);
}

int			ft_pchar(int nb)
{
	return (write(STDIN_FILENO, &nb, 1));
}
