/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/08 16:48:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/15 12:13:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_sigtstp_handler(int nb);
static void		ft_sigcont_handler(int nb);

void			ft_signals(void)
{
	signal(SIGHUP, &ft_exit);
	signal(SIGINT, &ft_exit);
	signal(SIGQUIT, &ft_exit);
	signal(SIGILL, &ft_exit);
	signal(SIGABRT, &ft_exit);
	signal(SIGFPE, &ft_exit);
	signal(SIGSEGV, &ft_exit);
	signal(SIGPIPE, &ft_exit);
	signal(SIGTERM, &ft_exit);
	signal(SIGUSR1, &ft_exit);
	signal(SIGUSR2, &ft_exit);
	signal(SIGCHLD, &ft_exit);
	signal(SIGCONT, &ft_sigcont_handler);
	signal(SIGSTOP, &ft_exit);
	signal(SIGTSTP, &ft_sigtstp_handler);
	signal(SIGWINCH, &ft_print_args);
}

static void		ft_sigtstp_handler(int nb)
{
	t_info	*info;
	char	susp[2];

	info = tgetinfo();
	susp[0] = info->new_term.c_cc[VSUSP];
	susp[1] = 0;
	if (isatty(1))
	{
		ft_term_restore(nb);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, susp);
	}
}

static void		ft_sigcont_handler(int nb)
{
	ft_load_new_capacities(nb);
	ft_define_new_term_cap(nb);
	signal(SIGTSTP, ft_sigtstp_handler);
	ft_print_args(nb);
}
