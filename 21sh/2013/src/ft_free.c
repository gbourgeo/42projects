/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:47:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/23 04:15:13 by gbourgeo         ###   ########.fr       */
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
		while (tmp)
		{
			if (tmp->cmd)
				free(tmp->cmd);
			if (tmp->save)
				free(tmp->save);
			next = tmp->next;
			ft_memset(tmp, 0, sizeof(*tmp));
			free(tmp);
			tmp = next;
		}
		*hist = NULL;
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
