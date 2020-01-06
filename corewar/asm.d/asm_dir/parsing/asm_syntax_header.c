/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 00:59:21 by dbaffier          #+#    #+#             */
/*   Updated: 2019/11/02 22:20:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static int				asm_syntax_comment(t_token *ptr2,
		t_env *e, t_aolist *hd)
{
	if (!ptr2)
		return (syntax_error(e, ERR_COMMENT_H, NULL, hd->next->line));
	if (ft_strcmp(ptr2->lab, COMMENT_CMD_STRING))
		return (syntax_error(e, ERR_COMMENT_H, NULL, hd->next->line));
	if (ptr2)
	{
		if (!ptr2->next)
			return (syntax_error(e, ERR_COMNOTF, NULL, hd->next->line));
		if (!ptr2->next->lab || ft_strlen(ptr2->next->lab) > 2048)
		{
			if (hd->next)
				return (syntax_error(e, ERR_COMMENT_LEN, NULL, hd->next->line));
			else
				return (syntax_error(e, ERR_NAME_LEN, NULL, hd->line));
		}
	}
	else
		return (syntax_error(e, ERR_COMMENT_H, NULL, hd->next->line));
	return (0);
}

static int				asm_syntax_name(t_token *ptr, t_env *e, t_aolist *head)
{
	if (!ptr)
		return (syntax_error(e, ERR_NAME_H, NULL, head->line));
	if (ft_strcmp(ptr->lab, NAME_CMD_STRING))
		return (syntax_error(e, ERR_NAME_H, NULL, head->line));
	if (ptr)
	{
		if (!ptr->next)
			return (syntax_error(e, ERR_NAMENOTF, NULL, head->next->line));
		if (!ptr->next->lab || ft_strlen(ptr->next->lab) > 128)
		{
			if (head->next)
				return (syntax_error(e, ERR_NAME_LEN, NULL, head->next->line));
			else
				return (syntax_error(e, ERR_NAME_H, NULL, head->line));
		}
	}
	else
		return (syntax_error(e, ERR_NAME_H, NULL, head->line));
	return (0);
}

int						asm_syntax_header(t_env *e, t_aolist *head)
{
	t_token		*ptr;

	if (!head)
		return (syntax_error(e, ERR_NAME_H, NULL, 1));
	ptr = head->tok;
	if (!ft_strcmp(ptr->lab, NAME_CMD_STRING))
	{
		asm_syntax_name(ptr, e, head);
		asm_syntax_comment(head->next->tok, e, head);
	}
	else if (!ft_strcmp(ptr->lab, COMMENT_CMD_STRING))
	{
		asm_syntax_comment(ptr, e, head);
		asm_syntax_name(head->next->tok, e, head);
	}
	else
		return (syntax_error(e, ERR_NAME_H, NULL, head->line));
	return (0);
}
