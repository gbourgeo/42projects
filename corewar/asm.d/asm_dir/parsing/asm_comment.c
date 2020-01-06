/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:49:40 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/22 21:03:59 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

int	asm_comment(t_aolist *head, char **line, char c)
{
	char	*str;
	char	*new;
	char	*tmp;
	size_t	len;

	new = ft_strchr(*line, c);
	len = new - *line;
	if (!(new = malloc(sizeof(char) * ft_strlen(new) + 1)))
		return (ERR_MALLOC);
	str = *line;
	ft_strcpy(new, &str[len]);
	head->comment = new;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (ERR_MALLOC);
	tmp = *line;
	ft_strncpy(str, tmp, len);
	str[len] = '\0';
	free(*line);
	*line = str;
	return (0);
}
