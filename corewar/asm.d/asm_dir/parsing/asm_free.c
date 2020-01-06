/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:43:41 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/23 01:44:53 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		free_token(t_token *tok)
{
	if (tok)
	{
		if (tok->lab)
			free(tok->lab);
		if (tok->err)
			free(tok->err);
		free_token(tok->next);
		free(tok);
	}
}

void			free_aolist(t_aolist *aolist)
{
	if (aolist)
	{
		if (aolist->comment)
			free(aolist->comment);
		free_token(aolist->tok);
		free_aolist(aolist->next);
		free(aolist);
	}
}
