/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:12:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/31 22:44:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			copy_strcopy(char rewrite)
{
	int				len;

	len = (e.cpy.cpy > 0) ? e.pos - e.cpy.shft : e.cpy.shft - e.pos;
	if ((!e.cpy.cpy && (len = ft_strlen(&e.hist->cmd[e.pos])) == 0) || len <= 0)
		return ;
	if (e.cpy.str != NULL)
		free(e.cpy.str);
	if (e.cpy.cpy > 0 &&
		!(e.cpy.str = ft_strndup(&e.hist->cmd[e.cpy.shft], len)))
		ft_exit_all("Malloc failed.");
	if (e.cpy.cpy <= 0 && !(e.cpy.str = ft_strndup(&e.hist->cmd[e.pos], len)))
		ft_exit_all("Malloc failed.");
	if (rewrite)
	{
		if (e.cpy.cpy == 0)
			ft_pos(len);
		rewrite_command();
	}
}

static void			cut_strcopy(void)
{
	int				len;

	len = (e.cpy.cpy > 0) ? e.pos - e.cpy.shft : e.cpy.shft - e.pos;
	if ((!e.cpy.cpy && (len = ft_strlen(&e.hist->cmd[e.pos])) == 0) || len <= 0)
		return ;
	copy_strcopy(0);
	if (e.cpy.cpy == 0)
		ft_bzero(&e.hist->cmd[e.pos], len);
	else if (e.cpy.cpy > 0)
	{
		ft_strncpy(&e.hist->cmd[e.cpy.shft], &e.hist->cmd[e.pos], \
					e.hist->cmd_size - e.cpy.shft);
		ft_pos(-len);
	}
	else
		ft_strncpy(&e.hist->cmd[e.pos], &e.hist->cmd[e.cpy.shft], \
					e.hist->cmd_size - e.pos);
	e.cpy.cut = 1;
	rewrite_command();
}

static void			paste_strcopy(void)
{
	read_command(e.cpy.str, ft_strlen(e.cpy.str));
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
