/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:05:46 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/21 00:48:18 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include "ft_printf.h"

static char		*dup_label(char *line, size_t *i)
{
	char		*new;
	size_t		s;
	size_t		e;

	s = *i;
	e = 0;
	while (line[*i] && line[*i] != ':')
		*i = *i + 1;
	if (!(new = malloc(sizeof(char) * (*i - s) + 1)))
		return (NULL);
	while (line[s] && s < *i)
	{
		new[e] = line[s];
		s++;
		e++;
	}
	new[e] = '\0';
	return (new);
}

int				create_label(t_token **head, char *val, size_t *i)
{
	t_token		*ptr;
	t_token		*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	if (!(new->lab = dup_label(val, i)))
		return (ERR_MALLOC);
	new->type |= LABEL;
	*i = *i + 1;
	if (*head == NULL)
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (0);
}

int				is_label(char *line, int start)
{
	while (line[start])
	{
		if (line[start] == ':' && line[start - 1] && line[start - 1] != '%')
			return (1);
		if (line[start] == '\t' || line[start] == ' ')
			return (0);
		start++;
	}
	return (0);
}
