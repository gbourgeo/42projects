/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 22:32:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 18:50:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static t_hist	*ft_hist_new(void)
{
	t_hist		*new;

	if ((new = (t_hist*)malloc(sizeof(t_hist))) == NULL)
		return (NULL);
	new->prev = NULL;
	new->command = ft_strnew(CMD_SIZE + 1);
	new->save = NULL;
	new->next = NULL;
	return (new);
}

static void		ft_clean_history(t_hist *hist)
{
	while (hist)
	{
		if (ft_strcmp(hist->command, hist->save))
		{
			ft_strclr(hist->command);
			ft_strcpy(hist->command, hist->save);
		}
		hist = hist->next;
	}
}

t_hist			*ft_add_to_hist(t_hist *history)
{
	t_hist	*new;
	char	*cmd;

	if (history->prev)
	{
		cmd = history->command;
		while (history->prev)
			history = history->prev;
		free(history->command);
		history->command = NULL;
		if ((history->command = ft_strnew(CMD_SIZE *
			((ft_strlen(cmd) / CMD_SIZE) + 1) + 1)) == NULL)
			return (history);
		ft_strcpy(history->command, cmd);
	}
	if ((new = ft_hist_new()) == NULL)
		return (history);
	history->save = ft_strdup(history->command);
	new->next = history;
	history->prev = new;
	ft_clean_history(history);
	return (new);
}

void			ft_print_history(t_hist *history)
{
	t_hist	*tmp;

	tmp = history;
	while (tmp)
	{
		ft_putendl(tmp->command);
		tmp = tmp->next;
	}
}

int				ft_aff_history(t_env *e, int direct)
{
	tputs(ft_tgetstr("rc"), 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	if (direct)
		e->history = e->history->next;
	else
		e->history = e->history->prev;
	ft_putstr(e->history->command);
	return (0);
}
