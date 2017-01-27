/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 04:40:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:15:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_insert_str(char *str, int len)
{
	int			size;
	int			end;

	if (e.hist->cmd[e.pos.x])
	{
		size = ft_strlen(&e.hist->cmd[e.pos.x]);
		end = ft_strlen(e.hist->cmd);
		while (size--)
		{
			len--;
			e.hist->cmd[end + len] = e.hist->cmd[e.pos.x + size];
		}
	}
	ft_strncpy(&e.hist->cmd[e.pos.x], str, ft_strlen(str));
}
