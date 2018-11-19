/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_new_capacities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 23:01:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/12 23:01:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_load_new_capacities(int ret)
{
	char	*term_name;

	if ((term_name = getenv("TERM")) == NULL)
		ft_error("No TERM path found. Use 'setenv TERM'\n");
	ret = tgetent(NULL, term_name);
	if (ret == -1)
		ft_error("Can't open Termcap's data base files.\n");
	else if (ret == 0)
		ft_error("Terminal not defined.\n");
}

void		ft_define_new_term_cap(int nb)
{
	t_info	*info;

	(void)nb;
	info = tgetinfo();
	if (tcgetattr(STDIN_FILENO, &info->new_term) != 0)
		ft_error("Fatal error: tcgetattr().\n");
	info->new_term.c_lflag &= ~(ICANON | ECHO);
	info->new_term.c_cc[VMIN] = 1;
	info->new_term.c_cc[VTIME] = 0;
	info->col = 0;
	info->len = 0;
	tputs(ft_tgetstr("ti"), 1, ft_pchar);
	tputs(ft_tgetstr("vi"), 1, ft_pchar);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &info->new_term)) == -1)
		ft_error("Fatal error: tcsetattr().\n");
}
