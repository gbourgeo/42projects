/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 03:38:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/12 19:17:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*ft_goto(char *cap, int x, int y)
{
	char		*tmp;

	tmp = tgoto(cap, x, y);
	if (tmp == NULL)
	{
		ft_putstr_fd("Fatal error :tgoto() ", 2);
		ft_putstr_fd(cap, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

char	*ft_tgetstr(char *t)
{
	char		*tmp;

	tmp = tgetstr(t, NULL);
	if (tmp == NULL)
	{
		ft_putstr_fd("Function tgetstr(", 2);
		ft_putstr_fd(t, 2);
		ft_putstr_fd(") not available.\n", 2);
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

void	ft_term_restore(int nb)
{
	struct termios	termios;

	(void)nb;
	tputs(ft_tgetstr("te"), 1, ft_pchar);
	tputs(ft_tgetstr("ve"), 1, ft_pchar);
	if (tcgetattr(0, &termios) != 0)
		ft_error("Fatal restore error: tcgetattr().\n");
	termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &termios) == -1)
		ft_error("Fatal restore error: tcsetattr().\n");
}

int		ft_pchar(int nb)
{
	return (write(STDIN_FILENO, &nb, 1));
}
