/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:44:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/19 20:52:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_hist			*new_hist(void)
{
	t_hist		*new;

	if (e.hist == NULL || e.hist->next == NULL)
	{
		new = (t_hist *)malloc(sizeof(*new));
		if (new == NULL)
			return (NULL);
		new->prev = e.hist;
		new->command = (char *)malloc(sizeof(*new->command) * CMD_SIZE);
		if (new->command == NULL)
		{
			free(new);
			return (NULL);
		}
		ft_bzero(new->command, CMD_SIZE);
		new->cmd_size = CMD_SIZE;
		new->next = NULL;
		return (new);
	}
	while (e.hist->next)
		e.hist = e.hist->next;
	return (e.hist);
}


void			historic_command(void)
{
	if (K_UP && e.hist->prev)
	{
		e.hist = e.hist->prev;
		e.cpy = 0;
		e.pos = ft_strlen(e.hist->command);
		tputs(ft_tgetstr("rc"), 1, ft_pchar);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		write(e.fd, e.hist->command, e.pos);
	}
	else if (K_DOWN && e.hist->next)
	{
		e.hist = e.hist->next;
		e.cpy = 0;
		e.pos = ft_strlen(e.hist->command);
		tputs(ft_tgetstr("rc"), 1, ft_pchar);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		write(e.fd, e.hist->command, e.pos);
	}
}
