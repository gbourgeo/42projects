/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_aolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:51:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/11/12 14:41:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

void	push_front(void *head, void *new, int type)
{
	t_token		*ptrr;
	t_aolist	*ptr;

	ptr = NULL;
	ptrr = NULL;
	if (type == 1)
	{
		ptrr = (t_token *)head;
		while (ptrr->next)
			ptrr = ptrr->next;
		ptrr->next = (t_token *)new;
	}
	else
	{
		ptr = (t_aolist *)head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = (t_aolist *)new;
	}
}

int		set_id(t_token *head)
{
	if (head == NULL)
		return (-1);
	if (head->type == LABEL)
		head = head->next;
	if (head && head->type != OP_CODE)
		return (-1);
	if (head)
		return (head->val - 1);
	return (-1);
}
