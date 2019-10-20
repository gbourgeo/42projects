/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/02 04:14:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/20 22:10:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		tty_check(t_info *info);

int				main(int ac, const char **av)
{
	t_info		*info;

	info = tgetinfo();
	if (ac > 1)
	{
		tty_check(info);
		ft_initialize_list(av, info);
		ft_load_new_capacities(42);
		ft_define_new_term_cap(42);
		ft_signals();
		run();
	}
	ft_putstr_fd("Nothing to select. End of program...\n", 2);
	return (1);
}

static void		tty_check(t_info *info)
{
	if (!isatty(STDIN_FILENO))
		ft_error("Terminal not valid.\n");
	if (!ttyname(STDIN_FILENO))
		ft_error("You are not connected a terminal.\n");
//	if (ttyslot() < 1)
//		ft_error("No terminal found in database.\n");
	if ((info->fd = open(ttyname(0), O_RDWR)) == -1)
	{
		ft_putstr_fd("Failed to open: ", STDERR_FILENO);
		ft_putendl_fd(ttyname(0), STDERR_FILENO);
		ft_exit(EXIT_FAILURE);
	}
}

void			run(void)
{
	t_info	*info;
	char	buf[4];
	int		i;

	info = tgetinfo();
	while (1)
	{
		ft_print_args(1);
		i = 0;
		while (i < 4)
			buf[i++] = 0;
		if (read(STDIN_FILENO, &buf, 4) < 1)
			exit(EXIT_FAILURE);
		key_check(buf, info);
	}
}
