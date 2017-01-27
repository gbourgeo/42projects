/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:12:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:14:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			copy_strcopy(char rewrite)
{
	int				len;

	len = (e.cpy.cpy > 0) ? e.pos.x - e.cpy.shft : e.cpy.shft - e.pos.x;
	if ((!e.cpy.cpy && (len = ft_strlen(&e.hist->cmd[e.pos.x])) == 0) || len <= 0)
		return ;
	if (e.cpy.str != NULL)
		free(e.cpy.str);
	if (e.cpy.cpy > 0 &&
		!(e.cpy.str = ft_strndup(&e.hist->cmd[e.cpy.shft], len)))
		ft_exit_all("Malloc failed.");
	if (e.cpy.cpy <= 0 && !(e.cpy.str = ft_strndup(&e.hist->cmd[e.pos.x], len)))
		ft_exit_all("Malloc failed.");
	if (rewrite)
	{
		if (e.cpy.cpy == 0)
			e.pos.x += len;
		rewrite_command();
	}
}

static void			cut_strcopy(void)
{
	int				len;

	len = (e.cpy.cpy > 0) ? e.pos.x - e.cpy.shft : e.cpy.shft - e.pos.x;
	if ((!e.cpy.cpy && (len = ft_strlen(&e.hist->cmd[e.pos.x])) == 0) || len <= 0)
		return ;
	copy_strcopy(0);
	if (e.cpy.cpy == 0)
		ft_bzero(&e.hist->cmd[e.pos.x], len);
	else if (e.cpy.cpy > 0)
	{
		ft_strncpy(&e.hist->cmd[e.cpy.shft], &e.hist->cmd[e.pos.x], \
					e.hist->cmd_size - e.cpy.shft);
		e.pos.x -= len;
	}
	else
		ft_strncpy(&e.hist->cmd[e.pos.x], &e.hist->cmd[e.cpy.shft], \
					e.hist->cmd_size - e.pos.x);
	e.cpy.cut = 1;
	rewrite_command();
}

static void			paste_strcopy(void)
{
	int				cpy;

	cpy = ft_strlen(e.cpy.str);
	if (cpy + ft_strlen(e.hist->cmd) >= e.hist->cmd_size)
	{
		e.hist->cmd_size += CMD_SIZE;
		if (!(e.hist->cmd = ft_realloc(e.hist->cmd, e.hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
	ft_insert_str(e.cpy.str, cpy);
	e.pos.x += cpy;
	rewrite_command();
	if (e.cpy.cut)
	{
		free(e.cpy.str);
		e.cpy.str = NULL;
		e.cpy.cut = 0;
	}
}

void				copy_command(void)
{
	if (K_COPY)
		copy_strcopy(1);
	else if (K_CUT)
		cut_strcopy();
	else if (K_PASTE && e.cpy.str)
		paste_strcopy();
}
