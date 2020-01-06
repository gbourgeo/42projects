/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:46:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/25 01:24:45 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static size_t	size_full(t_aolist *aolist)
{
	size_t		size;

	size = 0;
	while (aolist)
	{
		aolist->mem_addr = size;
		if ((aolist->tok && aolist->tok->type & DOT)
				|| (aolist->tok && aolist->tok->type & LABEL
				&& aolist->tok->next == NULL))
			;
		else
		{
			if (aolist->tok)
				size += aolist->size;
		}
		aolist = aolist->next;
	}
	return (size);
}

static int		syntax_bis(t_env *e, t_aolist *ao, t_aolist *head)
{
	t_token		*curr;

	curr = NULL;
	while (ao)
	{
		curr = ao->tok;
		if (curr && curr->type & LABEL)
		{
			curr = curr->next;
			asm_syntax_labelled(e, head);
		}
		asm_syntax_op(e, ao, curr);
		if (curr)
			asm_syntax_arg(e, ao, curr->next);
		ao = ao->next;
	}
	return (0);
}

int				syntax_analysis(t_env *e, t_aolist *aolist)
{
	t_aolist	*head;
	int			ret;

	while (aolist && aolist->tok == NULL)
		aolist = aolist->next;
	e->size = size_full(aolist);
	if ((ret = asm_syntax_header(e, aolist)) > 0)
		return (ret);
	if (aolist->next)
		aolist = aolist->next->next;
	head = aolist;
	if (aolist == NULL)
		return (syntax_error(e, E_OPC, NULL, 0));
	syntax_bis(e, aolist, head);
	return (0);
}
