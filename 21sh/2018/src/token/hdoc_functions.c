/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:07:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/22 01:08:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "quote.h"

t_hdoc			*hdoc_add(t_hdoc **head, void *token, size_t line)
{
	if (*head)
		(*head)->next = hdoc_add(&(*head)->next, token, line);
	else if ((*head = ft_memalloc(sizeof(**head))))
	{
		(*head)->type = HEREDOCUMENT;
		(*head)->line = line;
		(*head)->token = token;
		return (*head);
	}
	if (*head && !(*head)->next)
	{
		free(*head);
		*head = NULLHDOC;
	}
	return (*head);
}

void			hdoc_remove(t_hdoc **head)
{
	t_hdoc		*next;

	if (!*head)
		return ;
	next = (*head)->next;
	free(*head);
	*head = next;
}
