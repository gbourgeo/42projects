/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:35:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 16:18:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static size_t	count_lines(char *cmd, size_t i, size_t ret)
{
	char		*quote;

	while (cmd[i])
	{
		if (cmd[i] != ' ' && (cmd[i] < 9 || cmd[i] > 11))
		{
			ret++;
			while (cmd[i] != ' ' && (cmd[i] < 9 || cmd[i] > 11) && cmd[i])
			{
				if (cmd[i] == '\'' || cmd[i] == '"')
				{
					quote = &cmd[i++];
					while (cmd[i] && cmd[i] != *quote)
						i++;
				}
				i++;
			}
		}
		else
			i++;
	}
	return (ret);
}

static char		*copy_line(char *cmd, char *quote, size_t i, size_t j)
{
	char		*line;

	if ((line = (char *)malloc(sizeof(*line) * (i + 1))) == NULL)
		return (NULL);
	line[i--] = '\0';
	while (i + j > 0)
	{
		if (quote && cmd[i + j] == *quote)
			j--;
		else
		{
			line[i] = cmd[i + j];
			i--;
		}
	}
	if (quote == NULL || cmd[i + j] != *quote)
		line[i + j] = cmd[i + j];
	return (line);
}

static char		*get_line(char *cmd, size_t *len)
{
	size_t		i;
	size_t		j;
	char		*quote;

	i = 0;
	j = 0;
	quote = NULL;
	while (cmd[i + j] && cmd[i + j] != ' ' && (cmd[i + j] < 9 || cmd[i + j] > 11))
	{
		if (cmd[i + j] == '\'' || cmd[i + j] == '"')
		{
			quote = &cmd[i + j];
			j++;
			while (cmd[i + j] && cmd[i + j] != *quote)
				i++;
			j++;
		}
		else
			i++;
	}
	*len += i + j;
	return (copy_line(cmd, quote, i, j));
}

char			**split_command(char *cmd)
{
	size_t		line;
	char		**ret;
	size_t		i;
	size_t		j;

	if (cmd == NULL)
		return (NULL);
	line = count_lines(cmd, 0, 0);
	if ((ret = (char **)malloc(sizeof(*ret) * (line + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ' || (cmd[i] > 9 && cmd[i] < 11))
			i++;
		if ((ret[j++] = get_line(&cmd[i], &i)) == NULL)
			break ;
	}
	ret[j] = NULL;
	return (ret);
}
