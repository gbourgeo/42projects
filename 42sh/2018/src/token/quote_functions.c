/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:38:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/17 19:09:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "quote.h"

t_quote			*quote_add(t_quote **head, int type, size_t line)
{
	if (*head)
		(*head)->next = quote_add(&(*head)->next, type, line);
	else if ((*head = ft_memalloc(sizeof(**head))))
	{
		(*head)->type = type;
		(*head)->line = line;
		return (*head);
	}
	if (*head && !(*head)->next)
	{
		free(*head);
		*head = NULLQUOTE;
	}
	return (*head);
}

void			quote_remove(t_quote **head, int type)
{
	if (!*head)
		return ;
	if ((*head)->next)
		quote_remove(&(*head)->next, type);
	else if ((*head)->type == type)
	{
		free(*head);
		*head = NULLQUOTE;
	}
}

int				quote_type(t_quote *head)
{
	if (!head)
		return (NO_QUOTE);
	if (head->next)
		return (quote_type(head->next));
	return (head->type);
}

t_quote			*quote_get(t_quote *head)
{
	if (!head)
		return (NULLQUOTE);
	if (head->next)
		return (quote_get(head->next));
	return (head);
}
