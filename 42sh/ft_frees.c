/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/12 22:56:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 04:19:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_free_history(t_hist *hist)
{
	if (hist->next != NULL)
		ft_free_history(hist->next);
	if (hist->command != NULL)
		free(hist->command);
	if (hist->save != NULL)
		free(hist->save);
	hist->prev = NULL;
	hist->next = NULL;
	free(hist);
}

void		ft_free_list(t_args **list)
{
	if (*list)
	{
		if ((*list)->next != NULL)
			ft_free_list(&(*list)->next);
		(*list)->type = 0;
		(*list)->pipe = 0;
		if ((*list)->args)
			ft_free(&(*list)->args);
		(*list)->next = NULL;
		free(*list);
		*list = NULL;
	}
}

void		ft_free(char ***str)
{
	int		i;

	i = 0;
	if (str && *str)
	{
		while ((*str)[i] != '\0')
		{
			free((*str)[i]);
			(*str)[i] = NULL;
			++i;
		}
		free((*str)[i]);
		(*str)[i] = NULL;
		free(*str);
		(*str) = NULL;
		str = NULL;
	}
}
