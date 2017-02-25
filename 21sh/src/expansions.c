/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:25:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 00:29:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		quotes(size_t i, char *cmd, t_env *e)
{
	if (e->quote == 0)
	{
		e->quote = cmd[i];
		ft_strcpy(cmd + i, cmd + i + 1);
	}
	else if (e->quote == cmd[i])
	{
		e->quote = 0;
		ft_strncpy(cmd + i, cmd + i + 1, ft_strlen(cmd + i));
	}
	return (i + 1);
}

static int		tilde(size_t i, char **cmd, t_env *e)
{
	char		*home;
	size_t		len;
	size_t		cmd_len;

	cmd_len = ft_strlen(*cmd) - 1;
	home = ft_getenv("HOME", e->env);
	len = ft_strlen(home);
	if ((*cmd = ft_realloc(*cmd, cmd_len + len)) == NULL)
		return (-2);
	ft_strcpy(*cmd + i, *cmd + i + 1);
	ft_insert_str(*cmd + i, home, len);
	return (i + len);
}

char			*expansions_check(char **cmd, t_env *e)
{
	char		*tmp;
	int			i;

	i = 0;
	e->quote = 0;
	tmp = *cmd;
	while (i >= 0 && tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '"')
			i = quotes(i, *cmd, e);
		else if (tmp[i] == '~' && e->quote == 0)
			i = tilde(i, cmd, e);
		else if (tmp[i] == '$' && e->quote != '\'')
			i = dollar(i, cmd, e);
		else
			i++;
		tmp = *cmd;
	}
	return (*cmd);
}
