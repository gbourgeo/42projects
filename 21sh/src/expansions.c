/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:25:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/14 19:28:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char			*expansions_check(t_env *e)
{
	t_hist		tmp;
	char		*home;
	size_t		len;

	tmp.cmd = ft_strnew(e->hist->cmd_size);
	tmp.cmd_size = e->hist->cmd_size;
	ft_strcpy(tmp.cmd, e->hist->cmd);
	while ((tmp.save = ft_strchr(tmp.cmd, '~')) != NULL)
	{
		len = ft_strlen(tmp.save);
		home = ft_getenv("HOME", e->env);
		while (len + ft_strlen(home) - 1 >= tmp.cmd_size)
		{
			tmp.cmd_size += CMD_SIZE;
			if (!(tmp.cmd = ft_realloc(tmp.cmd, tmp.cmd_size)))
				return (NULL);
		}
		ft_strncpy(tmp.save, tmp.save + 1, len);
		ft_insert_str(tmp.save, home, ft_strlen(home));
	}
	return (tmp.cmd);
}
