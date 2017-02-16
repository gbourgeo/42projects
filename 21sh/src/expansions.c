/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:25:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/16 19:37:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		quotes(char quote, t_env *e)
{
	if (e->quote == 0)
		e->quote = quote;
	else if (e->quote == quote)
		e->quote = 0;
}

static int		tilde(size_t i, t_hist *tmp, t_env *e)
{
	char		*home;
	size_t		len;

	tmp->cmd_len = ft_strlen(tmp->cmd) - 1;
	home = ft_getenv("HOME", e->env);
	len = ft_strlen(home);
	while (tmp->cmd_len + len >= tmp->cmd_size)
	{
		tmp->cmd_size += CMD_SIZE;
		if (!(tmp->cmd = ft_realloc(tmp->cmd, tmp->cmd_size)))
			return (-2);
	}
	ft_strncpy(&tmp->cmd[i], &tmp->cmd[i + 1], tmp->cmd_size - i);
	ft_insert_str(&tmp->cmd[i], home, len);
	return (i + len - 1);
}

char			*expansions_check(t_env *e)
{
	t_hist		tmp;
	size_t		i;

	tmp.cmd = ft_strnew(e->hist->cmd_size);
	ft_strcpy(tmp.cmd, e->hist->cmd);
	tmp.cmd_size = e->hist->cmd_size;
	i = 0;
	while (tmp.cmd[i])
	{
		if (tmp.cmd[i] == '\'' || tmp.cmd[i] == '"')
			quotes(tmp.cmd[i], e);
		else if (tmp.cmd[i] == '~' && e->quote == 0)
		{
			if ((i = tilde(i, &tmp, e)) == -2)
				return (NULL);
		}
		i++;
	}
	return (tmp.cmd);
}
