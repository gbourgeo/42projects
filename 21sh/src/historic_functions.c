/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 04:11:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/15 04:31:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_hist				*hist_new(char *cmd, size_t len, t_hist *next)
{
	t_hist			*ret;

	ret = (t_hist *)malloc(sizeof(*ret));
	if (ret == NULL)
	{
		ft_putendl_fd("Error: malloc failed adding command in historic.", 2);
		return (NULL);
	}
	ret->prev = NULL;
	ret->cmd = (cmd == NULL) ? ft_strnew(CMD_SIZE) : ft_strdup(cmd);
	ret->cmd_len = len;
	ret->cmd_size = CMD_SIZE;
	while (len >= ret->cmd_size)
		ret->cmd_size += CMD_SIZE;
	ret->save = NULL;
	ret->next = next;
	if (next)
		next->prev = ret;
	return (ret);
}

void				hist_add(t_env *e)
{
	if ((!e->hist->next || ft_strcmp(e->hist->cmd, e->hist->next->cmd))
		&& *e->hist->cmd)
		e->hist = hist_new(NULL, 0, e->hist);
	else
	{
		ft_bzero(e->hist->cmd, e->hist->cmd_size);
		e->hist->cmd_len = 0;
	}
	hist_clean(e->hist);
	e->cmd = e->hist;
}

void				hist_clean(t_hist *hist)
{
	size_t			size;

	size = 0;
	while (hist)
	{
		if (size <= HIST_SIZE)
		{
			if (hist->save)
				free(hist->save);
			hist->save = NULL;
			size++;
			hist = hist->next;
		}
		else
		{
			hist->prev->next = NULL;
			ft_free_hist(&hist);
		}
	}
}
