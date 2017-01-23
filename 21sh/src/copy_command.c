/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:12:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/23 23:01:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			copy_strcopy(char rewrite)
{
	int				len;

	len = (e.cpy > 0) ? e.pos - e.shft : e.shft - e.pos;
	if ((e.cpy == 0 && (len = ft_strlen(&e.hist->cmd[e.pos])) == 0) || len <= 0)
		return ;
	if (e.cpystr != NULL)
		free(e.cpystr);
	if (e.cpy > 0 && !(e.cpystr = ft_strndup(&e.hist->cmd[e.shft], len)))
		ft_exit_all("Malloc failed.");
	if (e.cpy <= 0 && !(e.cpystr = ft_strndup(&e.hist->cmd[e.pos], len)))
		ft_exit_all("Malloc failed.");
	write(e.fd, "\n", 1);
	ft_putnbr(e.cpy);
	write(e.fd, " ", 1);
	ft_putnbr(len);
	write(e.fd, " ", 1);
	ft_putendl_fd(e.cpystr, e.fd);
	if (rewrite)
	{
		if (e.cpy == 0)
			e.pos += len;
		rewrite_command();
	}
}

static void			cut_strcopy(void)
{
	int				len;

	len = (e.cpy > 0) ? e.pos - e.shft : e.shft - e.pos;
	if ((e.cpy == 0 && (len = ft_strlen(&e.hist->cmd[e.pos])) == 0) || len <= 0)
		return ;
	copy_strcopy(0);
	if (e.cpy == 0)
		ft_bzero(&e.hist->cmd[e.pos], len);
	else if (e.cpy > 0)
	{
		ft_strncpy(&e.hist->cmd[e.shft], &e.hist->cmd[e.pos], e.hist->cmd_size - e.shft);
		e.pos -= len;
	}
	else
		ft_strncpy(&e.hist->cmd[e.pos], &e.hist->cmd[e.shft], e.hist->cmd_size - e.pos);
	e.cut = 1;
	rewrite_command();
}

static void			paste_strcopy(void)
{
	int				cpy;
	int				len;

	cpy = ft_strlen(e.cpystr);
	if (cpy + ft_strlen(e.hist->cmd) >= e.hist->cmd_size)
	{
		e.hist->cmd_size += CMD_SIZE;
		if (!(e.hist->cmd = ft_realloc(e.hist->cmd, e.hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
	e.pos += cpy;
	len = ft_strlen(&e.hist->cmd[e.pos - cpy]);
	ft_strncpy(&e.hist->cmd[e.pos], &e.hist->cmd[e.pos - cpy], len);
	ft_strncpy(&e.hist->cmd[e.pos - cpy], e.cpystr, cpy);
	rewrite_command();
	if (e.cut)
	{
		free(e.cpystr);
		e.cpystr = NULL;
		e.cut = 0;
	}
}

void				copy_command(void)
{
	if (K_COPY)
		copy_strcopy(1);
	else if (K_CUT)
		cut_strcopy();
	else if (K_PASTE && e.cpystr)
		paste_strcopy();
}
