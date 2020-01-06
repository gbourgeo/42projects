/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:09:46 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/03 18:35:25 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

char		*str_s_e(char *line, int s, int e)
{
	size_t		i;
	char		*new;

	i = 0;
	if (!(new = malloc(sizeof(char) * (e - s) + 1)))
		return (NULL);
	while (line[s] && s <= e)
	{
		new[i] = line[s];
		s++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

void		ft_freetab(char ***table)
{
	size_t		i;

	i = 0;
	if (table)
		if (*table)
		{
			while ((*table)[i])
			{
				free((*table)[i]);
				(*table)[i] = NULL;
				i++;
			}
			free(*table);
			*table = (char **)0;
		}
}
