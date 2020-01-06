/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grep_opcode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:25:39 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/21 20:13:59 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

static char		*dup_opcode(char *line, size_t *i)
{
	char		*new;
	size_t		s;
	size_t		e;

	s = *i;
	e = 0;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
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

static int		set_opcode(char *str)
{
	int		i;

	i = 0;
	while (g_op_tab[i].opcode != 0)
	{
		if (!ft_strcmp(g_op_tab[i].reg_name, str))
			return (g_op_tab[i].opcode);
		i++;
	}
	return (0);
}

int				grep_opcode(t_token **head, char *line, size_t *i)
{
	t_token		*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	if (!(new->lab = dup_opcode(line, i)))
		return (ERR_MALLOC);
	new->val = set_opcode(new->lab);
	new->type |= OP_CODE;
	if (!(new->next = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	if (grep_arg(new->next, line, i) > 0)
		return (ERR_MALLOC);
	if (*head == NULL)
		*head = new;
	else
		push_front(*head, new, 1);
	return (0);
}
