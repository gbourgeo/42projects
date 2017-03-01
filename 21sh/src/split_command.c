/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:35:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/01 11:54:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static size_t	quotes(char *cmd, size_t i)
{
	char		quote;

	quote = cmd[i++];
	while (cmd[i] != quote)
		i++;
	return (i + 1);
}

static size_t	pipes(char *cmd, size_t i, size_t *ret)
{
	char		pipe;

	pipe = cmd[i++];
	if (i != 1 && !ft_iswhitespace(cmd[i - 2]))
		(*ret)++;
	if (!cmd[i] || ft_iswhitespace(cmd[i]))
		return (i);
	if (cmd[i - 1] == '|')
		return (i);
	if (cmd[i] == pipe)
		return (i + 1);
	return (i);
}

static size_t	count_lines(char *cmd, size_t i, size_t ret)
{
	while (cmd[i])
	{
		if (!ft_iswhitespace(cmd[i]))
		{
			ret++;
			while (cmd[i] && !ft_iswhitespace(cmd[i]))
			{
				if (cmd[i] == '\'' || cmd[i] == '"')
					i = quotes(cmd, i);
				else if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
				{
					i = pipes(cmd, i, &ret);
					break ;
				}
				else
					i++;
			}
		}
		else
			i++;
	}
	return (ret);
}

static char		*get_line(char *cmd, size_t *len, t_env *e)
{
	long		i;
	char		*line;

	i = 0;
	while (cmd[i] && !ft_iswhitespace(cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			i = quotes(cmd, i);
		else if (cmd[i] == '|')
		{
			if (i == 0)
				i++;
			break ;
		}
		else
			i++;
	}
	if (i == 0 || (line = ft_strnew(i + 1)) == NULL)
		return (NULL);
	*len += i;
	ft_strncpy(line, cmd, i);
	line = expansions_check(&line, e);
	return (line);
}

char			**split_command(char *cmd, t_env *e)
{
	size_t		line;
	char		**ret;
	size_t		i;
	size_t		j;

	line = count_lines(cmd, 0, 0);
	if ((ret = ft_tabnew(line + 1)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (ft_iswhitespace(cmd[i]))
			i++;
		if ((ret[j] = get_line(&cmd[i], &i, e)) == NULL)
			break ;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}
