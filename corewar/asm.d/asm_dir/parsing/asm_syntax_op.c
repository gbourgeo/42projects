/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:00:52 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/01 22:22:24 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

int		asm_syntax_op(t_env *e, t_aolist *head, t_token *curr)
{
	if (!curr)
		return (0);
	if (curr && curr->val == 0)
		return (syntax_error(e, E_SYNTAX, curr->lab, head->line));
	if (curr && curr->next && g_op_tab[head->id].reg_nb > curr->next->arg_n)
		return (syntax_error(e, E_PARAM, curr->lab, head->line));
	return (0);
}
