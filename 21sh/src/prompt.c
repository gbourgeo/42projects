/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 01:37:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/17 21:07:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		quote_prompt(t_env *e)
{
	if (e->quote == '\'')
		ft_putstr_fd("quote> ", e->fd);
	else
		ft_putstr_fd("dquote> ", e->fd);
	e->prpt = (e->quote == '\'') ? 7 : 8;
}

static void		normal_prompt(t_env *e)
{
	char		*user;
	char		*pwd;
	char		*home;
	char		*tild;

	user = ft_getenv("USER", e->env);
	pwd = ft_getenv("PWD", e->env);
	home = ft_getenv("HOME", e->env);
	tild = ft_strstr(pwd, home);
	e->prpt = 0;
	ft_putstr_fd("\033[33m", e->fd);
	ft_putstr_fd(user, e->fd);
	ft_putstr_fd("\033[31m ", e->fd);
	if (tild != NULL)
	{
		e->prpt = 1;
		write(e->fd, "~", 1);
		pwd = &pwd[ft_strlen(home)];
		ft_putstr_fd(pwd, e->fd);
	}
	else
		ft_putstr_fd(pwd, e->fd);
	ft_putstr_fd("\033[37m > \033[0m", e->fd);
	e->prpt += ft_strlen(user) + ft_strlen(pwd) + 4;
}

void			prompt(t_env *e)
{
	tputs(ft_tgetstr("cr"), 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	if (e->quote)
		quote_prompt(e);
	else
		normal_prompt(e);
	cursor_position(&e->origin);
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
	if (e->quote == 0)
	{
		e->pos = 0;
		e->hist->cmd_len = 0;
		e->q_pos = 0;
		e->q_hist = NULL;
	}
}
