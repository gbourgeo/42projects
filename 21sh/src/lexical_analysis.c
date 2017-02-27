/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 07:11:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 07:27:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*ft_new_command(char *command)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (command[i])
	{
		if (ft_strchr("<>|&;", command[i]) != NULL)
		{
			if (i > 0 && command[i - 1] != ' ')
				len++;
			while (ft_strchr("<>|&;", command[i]) != NULL)
				i++;
			if (command[i] && command[i] != ' ')
				len++;
		}
		else
			i++;
	}
	len += i;
	return ((char*)malloc(sizeof(char) * len + 1));
}

char		*lexical_analysis(char *command)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!command || (new = ft_new_command(command)) == NULL)
		return (NULL);
	while (command[i] != '\0')
	{
		if (ft_strchr("<>|&;", command[i]) != NULL)
		{
			if (i > 0 && command[i - 1] != ' ')
				new[j++] = ' ';
			while (ft_strchr("<>|&;", command[i]) != NULL)
				new[j++] = command[i++];
			if (command[i] && command[i] != ' ')
				new[j++] = ' ';
		}
		else
			new[j++] = command[i++];
	}
	new[j] = '\0';
	return (new);
}
