/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:19:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 21:03:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void				ft_termcaps(char **env)
{
	char			*name;
	struct termios	term;

	if ((name = ft_getenv("TERM", env)) == NULL)
		ft_exit(0, "Unable to get TERM variable");
	if (tgetent(NULL, name) != 1)
		ft_exit(0, "termcaps: tgetent() returned.");
	if (tcgetattr(0, &e.term) == -1)
		ft_exit(1, "termcaps: tcgetattr()");
	ft_memcpy(&term, &e.term, sizeof(term));
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_exit(1, "termcaps: tcsetattr()");
	ft_termdo("cl");
	ft_putendl("Initialized TERMCAPS...");
}

void				ft_restore_term(void)
{
	int				i;

	i = -1;
	if (e.term.c_iflag != (tcflag_t)i && tcsetattr(0, 0, &e.term) == -1)
		perror("tcsetattr");
}

static int			ft_outc(int c)
{
	ft_putchar(c);
	return (0);
}

void				ft_termdo(char *doit)
{
	char			*res;

	if ((res = tgetstr(doit, NULL)) == NULL)
		return ;
	tputs(res, 0, ft_outc);
}
