/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:25:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/19 23:32:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		quotes(char quote, t_env *e)
{
	if (e->quote == 0)
		e->quote = quote;
	else if (e->quote == quote)
		e->quote = 0;
	return (1);
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
	tmp->cmd_len -= 1;
	ft_insert_str(&tmp->cmd[i], home, len);
	tmp->cmd_len += len;
	return (i + len);
}

static char		*find_dollar(char *cmd, t_env *e)
{
	char		*ret;
	int			i;

	ret = NULL;
	i = 0;
	while (cmd[i])
	{
		if (e->quote && cmd[i] == e->quote)
			break ;
		if (cmd[i] == '\n' || cmd[i] == ' ')
			break ;
		i++;
	}
	if (i == 0)
		return (NULL);
	ret = ft_strnew(i + 1);
	if (ret == NULL)
		return (NULL);
	ft_strncpy(ret, cmd, i);
	return (ret);
}

static int		replace_dollar(char *cmd, size_t i, t_hist *tmp, t_env *e)
{
	char		*ret;
	size_t		len;

	if (!ft_strcmp(cmd, "path"))
	{
		if ((ret = ft_getenv("PATH", e->env)) == NULL)
			return (i);
		ret = ft_strdup(ret);
		len = ft_strlen(ret);
		while ((cmd = ft_strchr(ret, ':')) != NULL)
			*cmd = ' ';
		while (tmp->cmd_len + len >= tmp->cmd_size)
		{
			tmp->cmd_size += CMD_SIZE;
			if (!(tmp->cmd = ft_realloc(tmp->cmd, tmp->cmd_size)))
				return (-2);
		}
		ft_insert_str(&tmp->cmd[i], ret, len);
		tmp->cmd_len += len;
		i += len;
		free(ret);
		return (i);
	}

	if (*cmd == '?')
	{
		if ((ret = ft_itoa(e->ret)) == NULL)
			return (i);
		len = ft_strlen(ret) + ft_strlen(cmd + 1);
		while (tmp->cmd_len + len >= tmp->cmd_size)
		{
			tmp->cmd_size += CMD_SIZE;
			if (!(tmp->cmd = ft_realloc(tmp->cmd, tmp->cmd_size)))
				return (i);
		}
		len = ft_strlen(ret);
		ft_insert_str(&tmp->cmd[i], ret, len);
		tmp->cmd_len += len;
		i += len;
		len = ft_strlen(cmd + 1);
		ft_insert_str(&tmp->cmd[i], cmd + 1, len);
		tmp->cmd_len += len;
		free(ret);
		return (i);
	}

	if (*cmd == '$')
	{
		if ((ret = ft_itoa(getppid())) == NULL)
			return (i);
		len = ft_strlen(ret) + ft_strlen(cmd + 1);
		while (tmp->cmd_len + len >= tmp->cmd_size)
		{
			tmp->cmd_size += CMD_SIZE;
			if (!(tmp->cmd = ft_realloc(tmp->cmd, tmp->cmd_size)))
				return (i);
		}
		len = ft_strlen(ret);
		ft_insert_str(&tmp->cmd[i], ret, len);
		tmp->cmd_len += len;
		i += len;
		len = ft_strlen(cmd + 1);
		ft_insert_str(&tmp->cmd[i], cmd + 1, len);
		tmp->cmd_len += len;
		free(ret);
		return (i);
	}

	ret = ft_getenv(cmd, e->env);
	len = ft_strlen(ret);
	ft_insert_str(&tmp->cmd[i], ret, len);
	tmp->cmd_len += len;
	i += len;
	return (i);
}

static int		dollar(size_t i, t_hist *tmp, t_env *e)
{
	char		*dolls;
	size_t		len;

	dolls = find_dollar(&tmp->cmd[i + 1], e);
	if (dolls == NULL)
		return (i);
	len = ft_strlen(dolls) + 1;
	tmp->cmd_len -= len;
	ft_strncpy(&tmp->cmd[i], &tmp->cmd[i + len], tmp->cmd_size - i);
	i = replace_dollar(dolls, i, tmp, e);
	free(dolls);
	return (i);
}

char			*expansions_check(t_env *e)
{
	t_hist		tmp;
	size_t		i;

	tmp.cmd = ft_strnew(e->hist->cmd_size);
	ft_strcpy(tmp.cmd, e->hist->cmd);
	tmp.cmd_len = e->hist->cmd_len;
	tmp.cmd_size = e->hist->cmd_size;
	i = 0;
	while (tmp.cmd[i])
	{
		if (tmp.cmd[i] == '\'' || tmp.cmd[i] == '"')
			i += quotes(tmp.cmd[i], e);
		else if (tmp.cmd[i] == '~' && e->quote == 0)
		{
			if ((i = tilde(i, &tmp, e)) == -2)
				return (NULL);
		}
		else if (tmp.cmd[i] == '$' && e->quote != '\'')
		{
			if ((i = dollar(i, &tmp, e)) == -2)
				return (NULL);
		}
		else
			i++;
	}
	return (tmp.cmd);
}
