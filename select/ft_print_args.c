/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 06:37:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/19 22:08:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		ft_check_argv_attributes(t_args *elem, int fd);
static void		ft_can_i_print_args(struct winsize *w);
static void		ft_check_position(struct winsize *w, t_info *info, t_args *tmp);
static void		ft_finger(int x, int y);

void			ft_print_args(int len)
{
	t_args			*tmp;
	t_info			*info;
	struct winsize	w;

	info = tgetinfo();
	tmp = info->elems;
	(void)len;
	ft_load_new_capacities(42);
	tputs(ft_tgetstr("ho"), 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	ioctl(0, TIOCGWINSZ, &w);
	while (tmp->next != info->elems)
	{
		tputs(ft_goto(ft_tgetstr("cm"), info->col, info->len), 1, ft_pchar);
		ft_check_argv_attributes(tmp, info->fd);
		info->len++;
		ft_check_position(&w, info, tmp);
		tmp = tmp->next;
	}
	tputs(ft_goto(ft_tgetstr("cm"), info->col, info->len), 1, ft_pchar);
	ft_check_argv_attributes(tmp, info->fd);
	ft_check_position(&w, info, tmp);
	info->len = 0;
	info->col = 0;
}

static void		ft_check_position(struct winsize *w, t_info *info, t_args *tmp)
{
	int				nb;

	nb = (info->lst_len % w->ws_row == 0) ? 0 : 1;
	if (w->ws_col < (info->lst_len / w->ws_row + nb) * (info->lst_col))
		ft_can_i_print_args(w);
	if (info->len == w->ws_row)
	{
		info->len = 0;
		tputs(ft_goto(ft_tgetstr("cm"), info->len, info->lst_col), 1, ft_pchar);
		info->col += info->lst_col + 2;
	}
	tmp->x = info->col;
	tmp->y = info->len;
}

static void		ft_check_argv_attributes(t_args *elem, int fd)
{
	if (elem->current == 1)
		tputs(ft_tgetstr("us"), 1, ft_pchar);
	if (elem->selected == 1)
		tputs(ft_tgetstr("so"), 1, ft_pchar);
	ft_color(elem->c, fd);
	ft_putstr_fd(elem->c, fd);
	if (elem->current == 1)
		tputs(ft_tgetstr("ue"), 1, ft_pchar);
	if (elem->selected == 1)
		tputs(ft_tgetstr("se"), 1, ft_pchar);
}

static void		ft_can_i_print_args(struct winsize *w)
{
	int			x;
	int			y;

	x = w->ws_col / 2;
	y = w->ws_row / 2;
	tputs(ft_tgetstr("ho"), 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	if (w->ws_row < 12 || w->ws_col < 24)
		ft_putstr_fd("Resize needed ┌П┐(◉_◉)┌П┐", 2);
	else
		ft_finger(x, y);
}

static void		ft_finger(int x, int y)
{
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y - 6), 1, ft_pchar);
	ft_putstr_fd("        __", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y - 5), 1, ft_pchar);
	ft_putstr_fd("       / /)", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y - 4), 1, ft_pchar);
	ft_putstr_fd("      /¯ /", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y - 3), 1, ft_pchar);
	ft_putstr_fd("   __/  /___", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y - 2), 1, ft_pchar);
	ft_putstr_fd("  /¯/¯ /¯/¯/\\", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y - 1), 1, ft_pchar);
	ft_putstr_fd(" / (  / / /  \\", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y - 0), 1, ft_pchar);
	ft_putstr_fd("( ' ' ' '  | |", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y + 1), 1, ft_pchar);
	ft_putstr_fd(" \\         [_/", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y + 2), 1, ft_pchar);
	ft_putstr_fd("  \\     _  /", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 8, y + 3), 1, ft_pchar);
	ft_putstr_fd("   |      |", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 11, y + 4), 1, ft_pchar);
	ft_putstr_fd("<  SIZE TOO SMALL  >", 2);
	tputs(ft_goto(ft_tgetstr("cm"), x - 7, y + 5), 1, ft_pchar);
	ft_putstr_fd("Motha Focka", 2);
}
