/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:35:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/23 04:38:27 by gbourgeo         ###   ########.fr       */
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
			while (cmd[i] && cmd[i] != ' ' && (cmd[i] < 9 || cmd[i] > 11))
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

static char		*get_line(char *cmd, size_t *len, t_env *e)
{
	size_t		i;
	char		*line;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && (cmd[i] < 9 || cmd[i] > 11))
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			e->quote = cmd[i++];
			while (cmd[i] != e->quote)
				i++;
		}
		i++;
	}
	if (i <= 0 || (line = ft_strnew(i + 1)) == NULL)
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
		while (cmd[i] == ' ' || (cmd[i] > 9 && cmd[i] < 11))
			i++;
		if ((ret[j] = get_line(&cmd[i], &i, e)) == NULL)
			break ;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}
