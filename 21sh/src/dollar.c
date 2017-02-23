/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:23:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/23 01:07:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

static int		replace_dollar_path(char *dolls, size_t i, char **cmd, char *p)
{
	char		*path;
	size_t		len;
	size_t		cmd_len;

	if ((path = ft_strdup(p)) == NULL)
		return (i);
	len = ft_strlen(path);
	while ((dolls = ft_strchr(path, ':')) != NULL)
		*dolls = ' ';
	cmd_len = ft_strlen(*cmd);
	if ((*cmd = ft_realloc(*cmd, cmd_len + len)) == NULL)
		return (-2);
	ft_insert_str(*cmd + i, path, len);
	i += len;
	free(path);
	return (i);
}

static int		replace_doll_quest(char *dolls, size_t i, char **cmd, char *ret)
{
	size_t		len;
	size_t		cmd_len;

	if (ret == NULL)
		return (i);
	len = ft_strlen(ret) + ft_strlen(dolls + 1);
	cmd_len = ft_strlen(*cmd);
	if ((*cmd = ft_realloc(*cmd, cmd_len + len)) == NULL)
		return (-2);
	len = ft_strlen(ret);
	ft_insert_str(*cmd + i, ret, len);
	i += len;
	len = ft_strlen(dolls + 1);
	if (len)
		ft_insert_str(*cmd + i, dolls + 1, len);
	free(ret);
	return (i);
}

static int		replace_dollar(char *dolls, size_t i, char **cmd, t_env *e)
{
	char		*ret;
	size_t		len;
	size_t		cmd_len;

	if (!ft_strcmp(dolls, "path"))
		return (replace_dollar_path(dolls, i, cmd, ft_getenv("PATH", e->env)));
	if (*dolls == '?')
		return (replace_doll_quest(dolls, i, cmd, ft_itoa(e->ret)));
	if (*dolls == '$')
		return (replace_doll_quest(dolls, i, cmd, ft_itoa(getpid())));
	ret = ft_getenv(dolls, e->env);
	len = ft_strlen(ret);
	cmd_len = ft_strlen(*cmd);
	if (len)
	{
		if ((*cmd = ft_realloc(*cmd, cmd_len + len)) == NULL)
			return (-2);
		ft_insert_str(*cmd + i, ret, len);
		i += len;
	}
	return (i);
}

int				dollar(size_t i, char **cmd, t_env *e)
{
	char		*dolls;
	size_t		len;

	dolls = find_dollar(*cmd + i + 1, e);
	if (dolls == NULL)
		return (i + 1);
	len = ft_strlen(dolls) + 1;
	ft_strcpy(*cmd + i, *cmd + i + len);
	i = replace_dollar(dolls, i, cmd, e);
	free(dolls);
	return (i);
}
