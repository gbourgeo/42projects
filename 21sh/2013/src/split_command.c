/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:35:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/03 09:40:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static long		quotes(char *cmd, long i)
{
	char		quote;

	quote = cmd[i++];
	while (cmd[i] != quote)
		i++;
	return (i + 1);
}

static long		pipes(char *cmd, long *i, int c)
{
	long		ret;
	char		pipe;

	ret = 0;
	pipe = cmd[*i];
	if (c)
	{
		if (*i != 0 && !ft_iswhitespace(cmd[*i - 1]))
			ret = 1;
		(*i)++;
		if (pipe == '|' || !cmd[*i] || !ft_iswhitespace(cmd[*i]))
			return (ret);
		if (cmd[*i] == pipe)
			(*i)++;
	}
	else
	{
		if (*i != 0 && (cmd[*i] != '|' || cmd[*i] != '<' || cmd[*i] != '>'))
			return (ret);
		if (*i == 0)
			(*i)++;
		if (pipe != '|' && cmd[*i] == pipe)
			(*i)++;
	}
	return (ret);
}

static size_t	count_lines(char *cmd, long i, long ret)
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
					ret += pipes(cmd, &i, 1);
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

static char		*get_line(char *cmd, long *len, t_env *e)
{
	long		i;
	char		*line;

	i = 0;
	while (cmd[i] && !ft_iswhitespace(cmd[i]))
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			i = quotes(cmd, i);
		else if (cmd[i] == '|' || cmd[i] == '<' || cmd[i] == '>')
		{
			pipes(cmd, &i, 0);
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
	long		i;
	long		j;

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
