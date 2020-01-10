/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_terminal_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:56:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/10 18:31:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <term.h>
#include <curses.h>
#include "cl_main.h"

int				cl_pchar(int nb)
{
	return (write(STDIN_FILENO, &nb, 1));
}

char			*cl_tgetstr(char *t)
{
	char			*tmp;

	if ((tmp = tgetstr(t, NULL)) == NULL)
	{
		ft_putstr_fd(t, STDERR_FILENO);
		ft_putendl_fd(" not available", STDERR_FILENO);
	}
	return (tmp);
}

static int		cl_stdin_init(t_client *cl)
{
	struct termios	term;
	char			*termtype;
	char			term_buffer[2048];
	int				success;

	if ((termtype = getenv("TERM")) == 0)
		return (ERR_TERM_NOT_DEFINED);
	if ((success = tgetent(term_buffer, termtype)) <= 0)
		return ((success < 0) ? ERR_TERM_DATABASE : ERR_TERM_NOT_FOUND);
	if ((cl->term.fd = open(ttyname(STDIN_FILENO), O_RDWR)) < 0)
		return (ERR_OPEN_TTY);
	if (tcgetattr(cl->term.fd, &cl->term.info))
		return (ERR_TCGETATTR);
	term = cl->term.info;
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if ((tcsetattr(cl->term.fd, TCSANOW, &term)) == -1)
		return (ERR_TCSETATTR);
	tputs(cl_tgetstr("im"), 1, cl_pchar);
	return (IS_OK);
}

int				cl_terminal_init(t_client *cl)
{
	if (!FT_CHECK(cl->options, cl_ncurses))
		return (cl_stdin_init(cl));
	return (cl_ncurses_init(cl));
}
