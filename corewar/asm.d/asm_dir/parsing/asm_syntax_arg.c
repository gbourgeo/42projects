/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:36:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/22 20:56:50 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static int		str_is_number(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		register_check(t_env *e, t_aolist *head, t_token *curr, int pos)
{
	if (!(g_op_tab[head->id].types[pos] & T_REG))
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	if (curr->lab == NULL || curr->lab[0] == '\0')
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	if (!str_is_number(curr->lab))
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	if (ft_atoi(curr->lab) > 99 || ft_atoi(curr->lab) < 0)
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	curr->val = ft_atoi(curr->lab);
	head->arg[pos] = T_REG;
	head->arg_size[pos] = 1;
	return (0);
}

static int		direct_check(t_env *e, t_aolist *head, t_token *curr, int pos)
{
	if (curr->lab == NULL || curr->lab[0] == '\0')
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	if (!(g_op_tab[head->id].types[pos] & T_DIR))
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	if (curr->type & LAB)
		asm_syntax_label(e, head, curr);
	else
	{
		if (!str_is_number(curr->lab))
			return (syntax_error(e, E_PARAM, curr->err, head->line));
		curr->val = ft_atoi(curr->lab);
	}
	head->arg[pos] = T_DIR;
	head->arg_size[pos] = g_op_tab[head->id].direct_size ? 2 : 4;
	return (0);
}

static int		indirect_check(t_env *e, t_aolist *head, t_token *curr, int pos)
{
	if (curr->lab == NULL || curr->lab[0] == '\0')
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	if (!(g_op_tab[head->id].types[pos] & T_IND))
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	if (curr->type & LAB)
		asm_syntax_label(e, head, curr);
	else
	{
		if (!str_is_number(curr->lab))
			return (syntax_error(e, E_PARAM, curr->err, head->line));
		curr->val = ft_atoi(curr->lab);
	}
	head->arg[pos] = T_IND;
	head->arg_size[pos] = 2;
	return (0);
}

int				asm_syntax_arg(t_env *e, t_aolist *head, t_token *curr)
{
	int		i;

	if (!curr)
		return (0);
	if (curr->arg_n > 3 || curr->arg_n < 0)
		return (syntax_error(e, E_PARAM, curr->err, head->line));
	i = 0;
	while (curr)
	{
		if (curr->type & REGISTER)
			register_check(e, head, curr, i);
		else if (curr->type & DIRECT)
			direct_check(e, head, curr, i);
		else if (curr->type & UNDIRECT)
			indirect_check(e, head, curr, i);
		curr = curr->next;
		i++;
	}
	return (0);
}
