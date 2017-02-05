/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:47:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/04 22:18:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_free_hist(t_hist **hist)
{
	t_hist		*tmp;
	t_hist		*next;

	if (hist)
	{
		tmp = *hist;
		if (tmp)
		{
			while (tmp->prev)
				tmp = tmp->prev;
			while (tmp)
			{
				if (tmp->cmd)
					free(tmp->cmd);
				next = tmp->next;
				ft_memset(tmp, 0, sizeof(*tmp));
				if (tmp)
					free(tmp);
				tmp = next;
			}
		}
	}
}

void			ft_free(char ***str)
{
	char		**table;

	if (str != NULL && *str != NULL)
	{
		table = *str;
		while (*table != NULL)
		{
			free(*table);
			*table = NULL;
			table++;
		}
		free(*str);
		*str = NULL;
	}
}
