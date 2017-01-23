/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:47:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/23 20:24:27 by gbourgeo         ###   ########.fr       */
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
	int			i;

	i = 0;
	if (str != NULL)
	{
		table = *str;
		if (table != NULL)
		{
			while (table[i] != NULL)
			{
				free(table[i]);
				table[i] = NULL;
				i++;
			}
			free(table);
			*str = NULL;
		}
	}
}
