/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:12:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 09:38:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			copy_strcopy(char rewrite, t_env *e)
{
	int				len;

	len = (e->cpy.cpy > 0) ? e->pos - e->cpy.shft : e->cpy.shft - e->pos;
	if ((!e->cpy.cpy && (len = ft_strlen(&e->hist->cmd[e->pos])) == 0) ||
		len <= 0)
		return ;
	if (e->cpy.str != NULL)
		free(e->cpy.str);
	if (e->cpy.cpy > 0 &&
		!(e->cpy.str = ft_strndup(&e->hist->cmd[e->cpy.shft], len)))
		ft_exit_all("Malloc failed.");
	if (e->cpy.cpy <= 0 &&
		!(e->cpy.str = ft_strndup(&e->hist->cmd[e->pos], len)))
		ft_exit_all("Malloc failed.");
	if (rewrite)
	{
		if (e->cpy.cpy == 0)
			ft_pos(len, e);
		rewrite_command(e);
	}
	e->cpy.cut = 0;
}

static void			check_quote(t_env *e)
{
	long			i;

	i = 0;
	while (e->cpy.str[i])
	{
		if (e->cpy.str[i] == '\'' || e->cpy.str[i] == '"')
		{
			if (e->quote == 0)
				e->quote = e->cpy.str[i];
			else if (e->quote == e->cpy.str[i])
				e->quote = 0;
		}
		i++;
	}
}

static void			cut_strcopy(t_env *e)
{
	int				len;

	len = (e->cpy.cpy > 0) ? e->pos - e->cpy.shft : e->cpy.shft - e->pos;
	if ((!e->cpy.cpy && (len = ft_strlen(&e->hist->cmd[e->pos])) == 0) ||
		len <= 0)
		return ;
	copy_strcopy(0, e);
	if (e->cpy.cpy == 0)
		ft_bzero(&e->hist->cmd[e->pos], len);
	else if (e->cpy.cpy > 0)
	{
		ft_strncpy(&e->hist->cmd[e->cpy.shft], &e->hist->cmd[e->pos], \
					e->hist->cmd_size - e->cpy.shft);
		ft_pos(-len, e);
	}
	else
		ft_strncpy(&e->hist->cmd[e->pos], &e->hist->cmd[e->cpy.shft], \
					e->hist->cmd_size - e->pos);
	e->hist->cmd_len -= len;
	e->cpy.cut = 1;
	check_quote(e);
	rewrite_command(e);
}

static void			paste_strcopy(t_env *e)
{
	if (e->cpy.str == NULL)
		return ;
	read_command(ft_strlen(e->cpy.str), e->cpy.str, e);
	if (e->cpy.cut)
	{
		free(e->cpy.str);
		e->cpy.str = NULL;
		e->cpy.cut = 0;
	}
}

void				copy_command(t_env *e)
{
	if (K_COPY(e))
		copy_strcopy(1, e);
	else if (K_CUT(e))
		cut_strcopy(e);
	else if (K_PASTE(e))
		paste_strcopy(e);
}
