/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:46:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/13 17:01:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				restore_term(void)
{
	tputs(ft_tgetstr("ei"), 1, ft_pchar);
	if ((tcsetattr(data.fd, TCSANOW, &data.old_term)) == -1)
		ft_putendl_fd("Fatal error: tcsetattr() returned.", 2);
}

void				redefine_term(void)
{
	struct termios  termios;

	if (tcgetattr(data.fd, &data.old_term) != 0)
		ft_exit_all("Fatal error: tcgetattr() returned.");
	ft_memcpy(&termios, &data.old_term, sizeof(termios));
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	if (tcsetattr(data.fd, TCSANOW, &termios) == -1)
		ft_exit_all("Fatal error: tcsetattr() returned.");
	tputs(ft_tgetstr("im"), 1, ft_pchar);
}

void				ft_tgoto(t_pos *pos)
{
	char			*str;

	str = tgoto(ft_tgetstr("cm"), pos->x, pos->y);
	if (str == NULL)
		return (ft_putendl_fd("tgoto() error.", 2));
	tputs(str, 1, ft_pchar);
}

char				*ft_tgetstr(char *str)
{
	char			*tmp;

	tmp = tgetstr(str, NULL);
	if (!tmp)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" not available", 2);
	}
	return (tmp);
}

int					ft_pchar(int nb)
{
	return (write(STDIN_FILENO, &nb, 1));
}
